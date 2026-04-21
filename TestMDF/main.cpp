#include <iostream>
#include <cstdio>
#include <optional>
#include <string>
#include <chrono>

#include "mdflibrary/MdfWriter.h"
#include "mdflibrary/CanMessage.h"

using namespace MdfLibrary;

namespace {

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
                           uint64_t timestamp_ns ) {
    // Regular CAN payload sample.
    CanMessage data_msg;
    data_msg.SetMessageId ( 0x123 );
    data_msg.SetDataLength ( 8 );
    uint8_t data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    data_msg.SetDataBytes ( data, 8 );
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
    const uint64_t stop_ns = start_ns + 1'000'000'000ULL;  // 1 second after start

    // StartMeasurement moves writer state so queued samples are persisted.
    // It also defines the time origin used by the master channel `t`.
    writer.StartMeasurement ( start_ns );
    SaveDataFrameSample ( writer, *data_frame_group, start_ns );

    // Stop + Finalize flush queues and patch final block links/sizes.
    writer.StopMeasurement ( stop_ns );
    writer.FinalizeMeasurement ();
}

int main () {
    const char* filePath = "sample.mf4";
    writer(filePath);

    return 0;
}

