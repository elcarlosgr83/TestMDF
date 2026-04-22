#include <iostream>
#include <cstdio>
#include <optional>
#include <string>
#include <chrono>
#include <array>
#include <algorithm>
#include <cmath>
#include <cstdint>

#include "mdflibrary/MdfWriter.h"
#include "mdflibrary/CanMessage.h"

using namespace MdfLibrary;

namespace {

constexpr uint32_t kEec1MessageId = 2297431040U;  // BO_ 2297431040 EEC1

std::array<uint8_t, 8> EncodeEec1Payload ( double torque_pct, double speed_rpm ) {
    // DBC:
    // torque: start=16 len=8  @1+ (1, -125)  -> raw = torque + 125
    // speed : start=24 len=16 @1+ (0.125, 0) -> raw = speed / 0.125 = speed * 8
    int torque_raw = static_cast<int> ( std::llround ( ( torque_pct + 125.0 ) / 1.0 ) );
    int speed_raw = static_cast<int> ( std::llround ( speed_rpm / 0.125 ) );

    torque_raw = std::clamp ( torque_raw, 0, 250 );
    speed_raw = std::clamp ( speed_raw, 0, 24000 );

    std::array<uint8_t, 8> data{};
    data.fill ( 0xFF );

    // Intel little-endian placement from the DBC start bits.
    data [ 2 ] = static_cast<uint8_t> ( torque_raw & 0xFF );
    data [ 3 ] = static_cast<uint8_t> ( speed_raw & 0xFF );
    data [ 4 ] = static_cast<uint8_t> ( ( speed_raw >> 8 ) & 0xFF );

    return data;
}

void ConfigureWriter ( MdfWriter& writer ) {
    // Bus/storage must be configured before creating the internal CAN groups.
    // CreateBusLogConfiguration builds the channel groups and all member channels
    // (including the time master channel `t`) according to bus + storage type.
    writer.SetBusType ( MdfBusType::CAN );
    writer.SetStorageType ( MdfStorageType::FixedLengthStorage );
    writer.CreateBusLogConfiguration ();
}

void ConfigureFileHistory ( MdfWriter& writer ) {
    // File history is attached to the header and should exist before InitMeasurement.
    auto header = writer.GetHeader ();
    auto fileHistory = header.CreateFileHistory ();
    fileHistory.SetDescription ( "FixedLengthStorage - DataFrame" );
    fileHistory.SetToolName ( "VST" );
    fileHistory.SetToolVendor ( "Vermeer" );
    fileHistory.SetToolVersion ( "1.0.0" );
}

std::optional<MdfChannelGroup> TryResolveDataFrameGroup ( MdfWriter& writer ) {
    // Group is searched by suffix because generated names include network/bus prefixes.
    // Groups/channels already exist because CreateBusLogConfiguration() ran before InitMeasurement.
    auto header = writer.GetHeader ();
    auto data_group = header.GetLastDataGroup ();
    auto channel_groups = data_group.GetChannelGroups ();

    for ( const auto& candidate : channel_groups ) {
        if ( candidate.GetName ().find ( "_DataFrame" ) != std::string::npos ) {
            return candidate;
        }
    }

    return std::nullopt;
}

void SaveDataFrameSample ( MdfWriter& writer, const MdfChannelGroup& group,
                           uint64_t timestamp_ns, double torque_pct,
                           double speed_rpm ) {
    // EEC1 (J1939) sample with torque and speed encoded from physical values.
    CanMessage data_msg;
    data_msg.SetMessageId ( kEec1MessageId );
    data_msg.SetExtendedId ( true );
    data_msg.SetBusChannel ( 1 );
    data_msg.SetDataLength ( 8 );

    const auto data = EncodeEec1Payload ( torque_pct, speed_rpm );
    data_msg.SetDataBytes ( data.data (), data.size () );

    writer.SaveCanMessage ( group, timestamp_ns, data_msg );
}

}  // namespace

void writer(const char* filePath) {
    // Remove old output to avoid appending extra DG/FH chains from prior runs.
    std::remove ( filePath );

    MdfWriter writer ( MdfWriterType::MdfBusLogger, filePath );

    // Required order: bus config -> file history -> init -> resolve group -> start -> save -> stop -> finalize.
    // This sequence guarantees valid links and ensures the write cache accepts samples.
    ConfigureWriter ( writer );
    ConfigureFileHistory ( writer );

    // Materializes metadata and block layout in the file.
    writer.InitMeasurement ();

    auto data_frame_group = TryResolveDataFrameGroup ( writer );
    if ( !data_frame_group.has_value () ) {
        std::cout << "DataFrame channel group not found." << std::endl;
        return;
    }

    // Capture wall-clock time at execution as nanoseconds since Unix epoch.
    // StartMeasurement uses this as the origin: relative_t = (sample_ns - start_ns) / 1e9.
    // It is also written to the MDF4 HD block as the measurement start timestamp.
    const uint64_t start_ns = static_cast<uint64_t> (
        std::chrono::duration_cast<std::chrono::nanoseconds> (
            std::chrono::system_clock::now ().time_since_epoch () ).count () );
    constexpr auto kSamplingDuration = std::chrono::minutes ( 1 );
    constexpr auto kSamplePeriod = std::chrono::milliseconds ( 100 );

    // StartMeasurement moves writer state so queued samples are persisted.
    // It also defines the time origin used by the master channel `t`.
    writer.StartMeasurement ( start_ns );

    // Save one EEC1 frame every 100 ms for exactly 60 seconds of synthetic time.
    // API expectation: timestamps are absolute UTC ns (Unix epoch).
    constexpr uint64_t kNsPerSecond = 1'000'000'000ULL;
    const uint64_t period_ns = static_cast<uint64_t> (
        std::chrono::duration_cast<std::chrono::nanoseconds> ( kSamplePeriod ).count () );
    const uint64_t duration_ns = static_cast<uint64_t> (
        std::chrono::duration_cast<std::chrono::nanoseconds> ( kSamplingDuration ).count () );
    const uint64_t sample_count = ( duration_ns / period_ns ) + 1;

    uint64_t last_ts = start_ns;
    for ( uint64_t i = 0; i < sample_count; ++i ) {
        uint64_t ts = start_ns + ( i * period_ns );
        if ( ts <= last_ts ) {
            ts = last_ts + 1;
        }

        const double elapsed_sec = static_cast<double> ( ts - start_ns ) /
                                   static_cast<double> ( kNsPerSecond );
        const double torque_pct = 35.0 + std::sin ( elapsed_sec * 0.5 ) * 10.0;
        const double speed_rpm = 1500.0 + std::sin ( elapsed_sec * 0.25 ) * 200.0;
        SaveDataFrameSample ( writer, *data_frame_group, ts, torque_pct, speed_rpm );
        last_ts = ts;
    }

    const uint64_t stop_ns = last_ts + 1'000'000ULL;

    // Stop + Finalize flush queues and patch final block links/sizes.
    writer.StopMeasurement ( stop_ns );
    writer.FinalizeMeasurement ();
}

int main () {
    const char* filePath = "sample.mf4";
    writer(filePath);

    return 0;
}

