#include <iostream>
#include <cstdio>
#include <optional>
#include <string>

#include "mdflibrary/MdfWriter.h"
#include "mdflibrary/CanMessage.h"

using namespace MdfLibrary;

namespace {

struct CanChannelGroups {
    // Optional is used because wrappers do not have a default constructor.

    // DataFrame: regular application payload traffic.
    std::optional<MdfChannelGroup> data_frame;
    // RemoteFrame: request for a DataFrame with the same CAN ID.
    std::optional<MdfChannelGroup> remote_frame;
    // ErrorFrame: CAN protocol-level error events (CRC/bit/ACK/form/stuff).
    std::optional<MdfChannelGroup> error_frame;
    // OverloadFrame: bus timing extension when a node needs extra delay.
    std::optional<MdfChannelGroup> overload_frame;
};

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
    fileHistory.SetDescription ( "FixedLengthStorage - All Frame Types" );
    fileHistory.SetToolName ( "VST" );
    fileHistory.SetToolVendor ( "Vermeer" );
    fileHistory.SetToolVersion ( "1.0.0" );
}

bool TryResolveCanChannelGroups ( MdfWriter& writer, CanChannelGroups& groups ) {
    // Groups are searched by suffix because generated names include network/bus prefixes.
    // At this point groups/channels already exist because CreateBusLogConfiguration()
    // ran before InitMeasurement.
    auto header = writer.GetHeader ();
    auto data_group = header.GetLastDataGroup ();
    auto channel_groups = data_group.GetChannelGroups ();
    if ( channel_groups.empty () ) {
        return false;
    }

    for ( const auto& candidate : channel_groups ) {
        const std::string name = candidate.GetName ();

        if ( name.find ( "_DataFrame" ) != std::string::npos ) {
            groups.data_frame = candidate;
        } else if ( name.find ( "_RemoteFrame" ) != std::string::npos ) {
            groups.remote_frame = candidate;
        } else if ( name.find ( "_ErrorFrame" ) != std::string::npos ) {
            groups.error_frame = candidate;
        } else if ( name.find ( "_OverloadFrame" ) != std::string::npos ) {
            groups.overload_frame = candidate;
        }
    }

    return groups.data_frame.has_value ()
        && groups.remote_frame.has_value ()
        && groups.error_frame.has_value ()
        && groups.overload_frame.has_value ();
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

void SaveRemoteFrameSample ( MdfWriter& writer, const MdfChannelGroup& group,
                             uint64_t timestamp_ns ) {
    // Remote frame requests data; no payload bytes are required.
    CanMessage remote_msg;
    remote_msg.SetMessageId ( 0x456 );
    remote_msg.SetDlc ( 8 );
    remote_msg.SetDataLength ( 8 );
    remote_msg.SetDir ( false );
    writer.SaveCanMessage ( group, timestamp_ns, remote_msg );
}

void SaveErrorFrameSample ( MdfWriter& writer, const MdfChannelGroup& group,
                            uint64_t timestamp_ns ) {
    // Error frame carries diagnostic flags plus payload bytes for this test.
    CanMessage error_msg;
    error_msg.SetMessageId ( 0x321 );
    error_msg.SetDataLength ( 8 );
    uint8_t err_data[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    error_msg.SetDataBytes ( err_data, 8 );
    error_msg.SetErrorType ( CanErrorType::BIT_ERROR );
    error_msg.SetBitPosition ( 13 );
    writer.SaveCanMessage ( group, timestamp_ns, error_msg );
}

void SaveOverloadFrameSample ( MdfWriter& writer, const MdfChannelGroup& group,
                               uint64_t timestamp_ns ) {
    // Overload frame is minimal: bus channel + direction bits.
    CanMessage overload_msg;
    overload_msg.SetBusChannel ( 1 );
    overload_msg.SetDir ( false );
    writer.SaveCanMessage ( group, timestamp_ns, overload_msg );
}

void SaveAllCanFrameSamples ( MdfWriter& writer, const CanChannelGroups& groups,
                              uint64_t start_ns ) {
    SaveDataFrameSample ( writer, *groups.data_frame, start_ns );
    SaveRemoteFrameSample ( writer, *groups.remote_frame, start_ns + 500ULL );
    SaveErrorFrameSample ( writer, *groups.error_frame, start_ns + 1000ULL );
    SaveOverloadFrameSample ( writer, *groups.overload_frame, start_ns + 1500ULL );
}
}  // namespace

void writer(const char* filePath) {
    // Remove old output to avoid appending extra DG/FH chains from prior runs.
    std::remove ( filePath );

    MdfWriter writer ( MdfWriterType::MdfBusLogger, filePath );

    // Required order: bus config -> file history -> init -> resolve groups -> start -> save -> stop -> finalize.
    // This sequence guarantees valid links and ensures the write cache accepts samples.
    ConfigureWriter ( writer );
    ConfigureFileHistory ( writer );

    // Materializes metadata and block layout in the file.
    writer.InitMeasurement ();

    CanChannelGroups groups;
    if ( !TryResolveCanChannelGroups ( writer, groups ) ) {
        // Fail early if the expected CAN frame groups were not created.

        std::cout << "Fail early if the expected CAN frame groups were not created." << std::endl;
        return;
    }

    constexpr uint64_t start_ns = 1'000'000'000ULL;
    constexpr uint64_t stop_ns  = 2'000'000'000ULL;
    // SaveCanMessage receives timestamps in ns. During write, the master time
    // channel stores them as relative seconds: (sample_time - start_time) / 1e9.
    // Keep start/stop/event times in the same time base.

    // StartMeasurement moves writer state so queued samples are persisted.
    // It also defines the time origin used by the master channel `t`.
    writer.StartMeasurement ( start_ns );
    SaveAllCanFrameSamples ( writer, groups, start_ns );

    // Stop + Finalize flush queues and patch final block links/sizes.
    writer.StopMeasurement ( stop_ns );
    writer.FinalizeMeasurement ();
}

int main () {
    const char* filePath = "sample.mf4";
    writer(filePath);

    return 0;
}

