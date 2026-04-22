#include <filesystem>
#include <fstream>
#include <array>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include "mdflibrary/MdfWriter.h"
#include "mdflibrary/MdfReader.h"
#include "mdflibrary/MdfChannelObserver.h"

namespace {

std::optional<MdfLibrary::MdfChannelGroup> FindChannelGroupBySuffix (
    const MdfLibrary::MdfHeader& header, const std::string& suffix ) {
    for ( const auto& data_group : header.GetDataGroups () ) {
        for ( const auto& channel_group : data_group.GetChannelGroups () ) {
            const auto group_name = channel_group.GetName ();

            if ( group_name.size () >= suffix.size () &&
                 group_name.compare ( group_name.size () - suffix.size (),
                                      suffix.size (), suffix ) == 0 ) {
                return channel_group;
            }
        }
    }

    return std::nullopt;
}

std::optional<MdfLibrary::MdfChannel> FindChannelByName (
    const MdfLibrary::MdfChannelGroup& group, const std::string& name ) {
    for ( const auto& channel : group.GetChannels () ) {
        if ( channel.GetName () == name ) {
            return channel;
        }
    }

    return std::nullopt;
}

}  // namespace

namespace {

struct StorageExpectation {
        MdfLibrary::MdfStorageType storage = MdfLibrary::MdfStorageType::FixedLengthStorage;
        const char* name = "";
        MdfLibrary::ChannelType data_bytes_type = MdfLibrary::ChannelType::VariableLength;
        bool expect_vlsd_record_id = false;
        size_t expected_channel_groups = 0;
};

constexpr std::array<StorageExpectation, 3> kStorageExpectations {{
        { MdfLibrary::MdfStorageType::FixedLengthStorage,
            "FixedLengthStorage",
            MdfLibrary::ChannelType::VariableLength,
            true,
            6 },
        { MdfLibrary::MdfStorageType::VlsdStorage,
            "VlsdStorage",
            MdfLibrary::ChannelType::VariableLength,
            true,
            6 },
        { MdfLibrary::MdfStorageType::MlsdStorage,
            "MlsdStorage",
            MdfLibrary::ChannelType::MaxLength,
            false,
            4 },
}};

MdfLibrary::CanMessage CreateTestCanMessage () {
        MdfLibrary::CanMessage message;
        message.SetMessageId ( 0x123 );
        message.SetExtendedId ( false );
        message.SetDataLength ( 8 );
        const uint8_t bytes[] = { 0x01, 0x02, 0x03, 0x04,
                                                            0x05, 0x06, 0x07, 0x08 };
        message.SetDataBytes ( bytes, 8 );
        return message;
}

class MdfWriterStorageMatrixTest
        : public ::testing::TestWithParam<StorageExpectation> {
};

}  // namespace

TEST(MdfWriterTest, CanCreateAndWriteMf4File) {
    const std::string filePath = "test_write_mf4.mf4";

    std::filesystem::remove(filePath);

    {
        MdfLibrary::MdfWriter writer(MdfLibrary::MdfWriterType::MdfBusLogger, filePath.c_str());
        writer.SetBusType(MdfLibrary::MdfBusType::CAN);
        writer.SetStorageType(MdfLibrary::MdfStorageType::VlsdStorage);

        EXPECT_TRUE(writer.CreateBusLogConfiguration());
        EXPECT_TRUE(writer.InitMeasurement());

        const uint64_t measurementStartNs = 100000000ULL;
        writer.StartMeasurement(measurementStartNs);
        writer.StopMeasurement(measurementStartNs + 100000000ULL);

        EXPECT_TRUE(writer.FinalizeMeasurement());
    }

    EXPECT_TRUE(std::filesystem::exists(filePath));
    EXPECT_GT(std::filesystem::file_size(filePath), 0);

    std::filesystem::remove(filePath);
}

TEST_P(MdfWriterStorageMatrixTest, CanFrameMatrixPerStorageType) {
    const auto config = GetParam ();
    const std::string filePath = std::string ( "test_can_matrix_" )
                               + config.name + ".mf4";

    std::filesystem::remove ( filePath );

    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::MdfBusLogger,
                                       filePath.c_str () );
        writer.SetBusType ( MdfLibrary::MdfBusType::CAN );
        writer.SetStorageType ( config.storage );

        ASSERT_TRUE ( writer.CreateBusLogConfiguration () );
        ASSERT_TRUE ( writer.InitMeasurement () );

        const uint64_t start_ns = 100000000ULL;
        writer.StartMeasurement ( start_ns );

        auto data_frame_group = FindChannelGroupBySuffix ( writer.GetHeader (),
                                                           "_DataFrame" );
        auto remote_frame_group = FindChannelGroupBySuffix ( writer.GetHeader (),
                                                             "_RemoteFrame" );
        auto error_frame_group = FindChannelGroupBySuffix ( writer.GetHeader (),
                                                            "_ErrorFrame" );
        auto overload_frame_group = FindChannelGroupBySuffix ( writer.GetHeader (),
                                                               "_OverloadFrame" );

        ASSERT_TRUE ( data_frame_group.has_value () );
        ASSERT_TRUE ( remote_frame_group.has_value () );
        ASSERT_TRUE ( error_frame_group.has_value () );
        ASSERT_TRUE ( overload_frame_group.has_value () );

        MdfLibrary::CanMessage message = CreateTestCanMessage ();
        writer.SaveCanMessage ( *data_frame_group, start_ns + 1, message );
        writer.SaveCanMessage ( *remote_frame_group, start_ns + 2, message );
        writer.SaveCanMessage ( *error_frame_group, start_ns + 3, message );
        writer.SaveCanMessage ( *overload_frame_group, start_ns + 4, message );

        writer.StopMeasurement ( start_ns + 2000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( filePath.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    auto data_groups = reader.GetHeader ().GetDataGroups ();
    ASSERT_FALSE ( data_groups.empty () );

    const auto all_groups = reader.GetHeader ().GetLastDataGroup ().GetChannelGroups ();
    EXPECT_EQ ( all_groups.size (), config.expected_channel_groups );

    auto data_frame_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                                       "_DataFrame" );
    auto remote_frame_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                                         "_RemoteFrame" );
    auto error_frame_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                                        "_ErrorFrame" );
    auto overload_frame_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                                           "_OverloadFrame" );

    ASSERT_TRUE ( data_frame_group.has_value () );
    ASSERT_TRUE ( remote_frame_group.has_value () );
    ASSERT_TRUE ( error_frame_group.has_value () );
    ASSERT_TRUE ( overload_frame_group.has_value () );

    EXPECT_EQ ( data_frame_group->GetNofSamples (), 1U );
    EXPECT_EQ ( remote_frame_group->GetNofSamples (), 1U );
    EXPECT_EQ ( error_frame_group->GetNofSamples (), 1U );
    EXPECT_EQ ( overload_frame_group->GetNofSamples (), 1U );

    auto data_bytes = FindChannelByName ( *data_frame_group,
                                          "CAN_DataFrame.DataBytes" );
    ASSERT_TRUE ( data_bytes.has_value () );
    EXPECT_EQ ( data_bytes->GetType (), config.data_bytes_type );

    if ( config.expect_vlsd_record_id ) {
        EXPECT_NE ( data_bytes->GetVlsdRecordId (), 0U );
    } else {
        EXPECT_EQ ( data_bytes->GetVlsdRecordId (), 0U );
    }

    EXPECT_EQ ( data_bytes->GetDataType (), MdfLibrary::ChannelDataType::ByteArray );

    auto error_data_bytes = FindChannelByName ( *error_frame_group,
                                                "CAN_ErrorFrame.DataBytes" );
    ASSERT_TRUE ( error_data_bytes.has_value () );
    EXPECT_EQ ( error_data_bytes->GetType (), config.data_bytes_type );

    if ( config.expect_vlsd_record_id ) {
        EXPECT_NE ( error_data_bytes->GetVlsdRecordId (), 0U );
    } else {
        EXPECT_EQ ( error_data_bytes->GetVlsdRecordId (), 0U );
    }

    EXPECT_EQ ( error_data_bytes->GetDataType (),
                MdfLibrary::ChannelDataType::ByteArray );

    auto remote_data_bytes = FindChannelByName ( *remote_frame_group,
                                                 "CAN_RemoteFrame.DataBytes" );
    EXPECT_FALSE ( remote_data_bytes.has_value () );

    auto overload_data_bytes = FindChannelByName ( *overload_frame_group,
                                                   "CAN_OverloadFrame.DataBytes" );
    EXPECT_FALSE ( overload_data_bytes.has_value () );

    reader.Close ();
    std::filesystem::remove ( filePath );
}

INSTANTIATE_TEST_SUITE_P (
    CanStorageMatrix,
    MdfWriterStorageMatrixTest,
    ::testing::ValuesIn ( kStorageExpectations ),
    [] ( const ::testing::TestParamInfo<StorageExpectation>& info ) {
        return info.param.name;
    } );

// ================================================================
// Block-level tests — one group per MDF4 block type (§4.x)
//
// Covered blocks: ID HD MD TX FH AT EV DG CG SI CN CC DT SD DZ
// Not covered via this API: CH CA SR RD DL HL (internal or not
// exposed by the mdflibrary C++ wrapper).
// ================================================================

/**
 * Fixture that auto-removes the test file in TearDown and provides
 * WriteBasicFile() to create a minimal Mdf4Basic file containing one
 * Master (time) channel + one uint16 measurement channel with N samples
 * (raw value == sample index). Pass compress=true to force DZ blocks.
 */
class MdfBlockTest : public ::testing::Test {
protected:
    std::string file_path_;

    void TearDown () override {
        if ( !file_path_.empty () )
            std::filesystem::remove ( file_path_ );
    }

    std::string MakePath ( const std::string& suffix ) {
        file_path_ = "test_block_" + suffix + ".mf4";
        std::filesystem::remove ( file_path_ );
        return file_path_;
    }

    void WriteBasicFile ( const std::string& path,
                          const std::string& ch_name,
                          uint64_t nof_samples,
                          bool compress = false ) {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        writer.SetCompressData ( compress );

        auto dg = writer.CreateDataGroup ();
        auto cg = dg.CreateChannelGroup ();
        cg.SetName ( "TestGroup" );

        auto master = cg.CreateChannel ();
        master.SetName ( "t" );
        master.SetType ( MdfLibrary::ChannelType::Master );
        master.SetSync ( MdfLibrary::ChannelSyncType::Time );
        master.SetDataType ( MdfLibrary::ChannelDataType::UnsignedIntegerLe );
        master.SetDataBytes ( 8 );

        auto ch = cg.CreateChannel ();
        ch.SetName ( ch_name.c_str () );
        ch.SetType ( MdfLibrary::ChannelType::FixedLength );
        ch.SetDataType ( MdfLibrary::ChannelDataType::UnsignedIntegerLe );
        ch.SetDataBytes ( 2 );

        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        for ( uint64_t i = 0; i < nof_samples; ++i ) {
            master.SetChannelValue ( static_cast<uint64_t> ( i * 1000000ULL ) );
            ch.SetChannelValue ( static_cast<uint64_t> ( i ) );
            writer.SaveSample ( cg, i * 1000000ULL );
        }
        writer.StopMeasurement ( nof_samples * 1000000ULL );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }
};

// --- ID block (file identification) --------------------------------
// Validates MDF4 format flag, main/minor version and finalized state.
TEST_F ( MdfBlockTest, IdBlock_ValidMdf4VersionAndFinalizedState ) {
    const auto path = MakePath ( "id" );
    ASSERT_NO_FATAL_FAILURE ( WriteBasicFile ( path, "Value", 1 ) );

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadHeader () );

    auto file = reader.GetFile ();
    EXPECT_TRUE ( file.GetIsMdf4 () );
    EXPECT_EQ ( file.GetMainVersion (), 4 );
    EXPECT_GE ( file.GetMinorVersion (), 0 );

    uint16_t std_flags = 0, custom_flags = 0;
    EXPECT_TRUE ( file.GetFinalized ( std_flags, custom_flags ) );
    reader.Close ();
}

// --- HD block (header) ---------------------------------------------
// Validates author, project, subject, description and department
// metadata survive a full write–read roundtrip.
TEST_F ( MdfBlockTest, HdBlock_MetadataFieldsRoundTrip ) {
    const auto path = MakePath ( "hd" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto header = writer.GetHeader ();
        header.SetAuthor ( "Test Author" );
        header.SetProject ( "TestProject" );
        header.SetSubject ( "UnitTest" );
        header.SetDescription ( "HD block test" );
        header.SetDepartment ( "Engineering" );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadHeader () );

    const auto header = reader.GetHeader ();
    EXPECT_EQ ( header.GetAuthor (),      "Test Author" );
    EXPECT_EQ ( header.GetProject (),     "TestProject" );
    EXPECT_EQ ( header.GetSubject (),     "UnitTest" );
    EXPECT_EQ ( header.GetDescription (), "HD block test" );
    EXPECT_EQ ( header.GetDepartment (),  "Engineering" );
    reader.Close ();
}

// --- MD block (metadata / XML snippet) ----------------------------
// Validates that an XML snippet written to the header MD block is
// non-empty after readback.
TEST_F ( MdfBlockTest, MdBlock_XmlSnippetRoundTrip ) {
    const auto path = MakePath ( "md_xml" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto md = writer.GetHeader ().CreateMetaData ();
        md.SetXmlSnippet ( "<root><value>42</value></root>" );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );
    EXPECT_FALSE ( reader.GetHeader ().GetMetaData ().GetXmlSnippet ().empty () );
    reader.Close ();
}

// --- MD block (ETag common properties) ----------------------------
// Validates that a typed ETag common property is stored and retrieved
// correctly (uses an MD block for the structured XML property bag).
TEST_F ( MdfBlockTest, MdBlock_ETagCommonPropertyRoundTrip ) {
    const auto path = MakePath ( "md_etag" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto md = writer.GetHeader ().CreateMetaData ();
        md.SetPropertyAsString ( "SensorId", "sensor_42" );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );
    auto etag_header = reader.GetHeader ();
    auto etag_md     = etag_header.GetMetaData ();
    const auto val   = etag_md.GetPropertyAsString ( "SensorId" );
    EXPECT_EQ ( val, "sensor_42" );
    reader.Close ();
}

// --- TX block (plain text) ----------------------------------------
// TX blocks store unstructured strings (names, units, descriptions).
// Validates that channel unit and description text survive roundtrip.
TEST_F ( MdfBlockTest, TxBlock_ChannelUnitAndDescriptionRoundTrip ) {
    const auto path = MakePath ( "tx" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto dg = writer.CreateDataGroup ();
        auto cg = dg.CreateChannelGroup ();
        cg.SetName ( "TxTestGroup" );
        cg.SetDescription ( "CG description text" );

        auto ch = cg.CreateChannel ();
        ch.SetName ( "Voltage" );
        ch.SetType ( MdfLibrary::ChannelType::FixedLength );
        ch.SetDataType ( MdfLibrary::ChannelDataType::FloatLe );
        ch.SetDataBytes ( 4 );
        ch.SetUnit ( "mV" );
        ch.SetDescription ( "Battery voltage" );

        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    bool found = false;
    const auto header = reader.GetHeader ();
    for ( const auto& dg : header.GetDataGroups () ) {
        for ( const auto& cg : dg.GetChannelGroups () ) {
            if ( cg.GetName () != "TxTestGroup" )
                continue;
            EXPECT_EQ ( cg.GetDescription (), "CG description text" );
            auto voltage = FindChannelByName ( cg, "Voltage" );
            ASSERT_TRUE ( voltage.has_value () );
            EXPECT_EQ ( voltage->GetUnit (),        "mV" );
            EXPECT_EQ ( voltage->GetDescription (), "Battery voltage" );
            found = true;
        }
    }
    EXPECT_TRUE ( found ) << "TxTestGroup not found";
    reader.Close ();
}

// --- FH block (file history) --------------------------------------
// Validates tool name, vendor, version, user name and description
// roundtrip via the FH block.
TEST_F ( MdfBlockTest, FhBlock_ToolInfoRoundTrip ) {
    const auto path = MakePath ( "fh" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto fh = writer.GetHeader ().CreateFileHistory ();
        fh.SetTime ( 1000000ULL );
        fh.SetToolName ( "MdfTestTool" );
        fh.SetToolVendor ( "TestVendor" );
        fh.SetToolVersion ( "2.0.0" );
        fh.SetUserName ( "tester" );
        fh.SetDescription ( "Initial write" );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    const auto histories = reader.GetHeader ().GetFileHistorys ();
    ASSERT_FALSE ( histories.empty () );

    bool found = false;
    for ( const auto& fh : histories ) {
        if ( fh.GetToolName () != "MdfTestTool" )
            continue;
        EXPECT_EQ ( fh.GetToolVendor (),   "TestVendor" );
        EXPECT_EQ ( fh.GetToolVersion (),  "2.0.0" );
        EXPECT_EQ ( fh.GetUserName (),     "tester" );
        EXPECT_EQ ( fh.GetDescription (), "Initial write" );
        found = true;
        break;
    }
    EXPECT_TRUE ( found ) << "FH block with tool name 'MdfTestTool' not found";
    reader.Close ();
}

// --- AT block (attachment) ----------------------------------------
// Validates that a small embedded file is stored and retrieved with the
// correct filename and embedded/compressed flags.
TEST_F ( MdfBlockTest, AtBlock_EmbeddedFileRoundTrip ) {
    const auto path        = MakePath ( "at" );
    const std::string attach_name = "test_at_payload.txt";
    {
        std::ofstream f ( attach_name );
        f << "mdflib attachment test payload";
    }

    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto at = writer.GetHeader ().CreateAttachment ();
        at.SetFileName ( attach_name.c_str () );
        at.SetFileType ( "text/plain" );
        at.SetEmbedded ( true );
        at.SetCompressed ( false );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }
    std::filesystem::remove ( attach_name );

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    const auto attachments = reader.GetHeader ().GetAttachments ();
    ASSERT_FALSE ( attachments.empty () );

    bool found = false;
    for ( const auto& at : attachments ) {
        if ( at.GetFileName ().find ( "test_at_payload" ) == std::string::npos )
            continue;
        EXPECT_TRUE  ( at.GetEmbedded () );
        EXPECT_FALSE ( at.GetCompressed () );
        found = true;
        break;
    }
    EXPECT_TRUE ( found ) << "AT block for embedded file not found";
    reader.Close ();
}

// --- EV block (event) ---------------------------------------------
// Validates event name, type, cause and sync value roundtrip.
TEST_F ( MdfBlockTest, EvBlock_TriggerEventRoundTrip ) {
    const auto path = MakePath ( "ev" );
    constexpr int64_t kSyncValue = 500000000LL;
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto ev = writer.GetHeader ().CreateEvent ();
        ev.SetName ( "StartTrigger" );
        ev.SetType ( MdfLibrary::EventType::Trigger );
        ev.SetCause ( MdfLibrary::EventCause::CauseUser );
        ev.SetSync ( MdfLibrary::SyncType::SyncTime );
        ev.SetSyncValue ( kSyncValue );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    const auto events = reader.GetHeader ().GetEvents ();
    ASSERT_FALSE ( events.empty () );

    bool found = false;
    for ( const auto& ev : events ) {
        if ( ev.GetName () != "StartTrigger" )
            continue;
        EXPECT_EQ ( ev.GetType (),      MdfLibrary::EventType::Trigger );
        EXPECT_EQ ( ev.GetCause (),     MdfLibrary::EventCause::CauseUser );
        EXPECT_EQ ( ev.GetSyncValue (), kSyncValue );
        found = true;
        break;
    }
    EXPECT_TRUE ( found ) << "EV block 'StartTrigger' not found";
    reader.Close ();
}

// --- DG block (data group) ----------------------------------------
// A CAN bus-logger DG is unsorted (multiple CGs share one data stream),
// so record_id_size must be > 0 and the DG must contain channel groups.
TEST_F ( MdfBlockTest, DgBlock_UnsortedBusLoggerHasNonZeroRecordIdSize ) {
    const auto path = MakePath ( "dg" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::MdfBusLogger,
                                       path.c_str () );
        writer.SetBusType ( MdfLibrary::MdfBusType::CAN );
        writer.SetStorageType ( MdfLibrary::MdfStorageType::VlsdStorage );
        ASSERT_TRUE ( writer.CreateBusLogConfiguration () );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    const auto data_groups = reader.GetHeader ().GetDataGroups ();
    ASSERT_FALSE ( data_groups.empty () );
    EXPECT_GT ( data_groups.front ().GetRecordIdSize (), 0U )
        << "Unsorted DG must have record_id_size > 0";
    EXPECT_FALSE ( data_groups.front ().GetChannelGroups ().empty () );
    reader.Close ();
}

// --- CG block (channel group) -------------------------------------
// In an unsorted DG every CG has a non-zero record_id. Validates
// record_id, nof_samples count after writing one frame, and name.
TEST_F ( MdfBlockTest, CgBlock_RecordIdNofSamplesAndNameRoundTrip ) {
    const auto path = MakePath ( "cg" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::MdfBusLogger,
                                       path.c_str () );
        writer.SetBusType ( MdfLibrary::MdfBusType::CAN );
        writer.SetStorageType ( MdfLibrary::MdfStorageType::VlsdStorage );
        ASSERT_TRUE ( writer.CreateBusLogConfiguration () );
        ASSERT_TRUE ( writer.InitMeasurement () );

        constexpr uint64_t kStartNs = 100000000ULL;
        writer.StartMeasurement ( kStartNs );

        auto df_group = FindChannelGroupBySuffix ( writer.GetHeader (),
                                                   "_DataFrame" );
        ASSERT_TRUE ( df_group.has_value () );
        writer.SaveCanMessage ( *df_group, kStartNs + 1,
                                CreateTestCanMessage () );

        writer.StopMeasurement ( kStartNs + 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    auto df_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                               "_DataFrame" );
    ASSERT_TRUE ( df_group.has_value () );
    EXPECT_NE ( df_group->GetRecordId (), 0U )
        << "CG in unsorted DG must have non-zero record_id";
    EXPECT_EQ ( df_group->GetNofSamples (), 1U );
    EXPECT_FALSE ( df_group->GetName ().empty () );
    reader.Close ();
}

// --- SI block (source information) --------------------------------
// Creates a CG with an SI block (name, path, SourceType::Bus,
// BusType::Can) and validates the values survive roundtrip.
TEST_F ( MdfBlockTest, SiBlock_SourceNameTypePathAndBusTypeRoundTrip ) {
    const auto path = MakePath ( "si" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto dg = writer.CreateDataGroup ();
        auto cg = dg.CreateChannelGroup ();
        cg.SetName ( "SiTestGroup" );

        auto si = cg.CreateSourceInformation ();
        si.SetName ( "CAN_BUS_1" );
        si.SetPath ( "/CAN/1" );
        si.SetType ( MdfLibrary::SourceType::Bus );
        si.SetBus  ( MdfLibrary::BusType::Can );

        auto master = cg.CreateChannel ();
        master.SetName ( "t" );
        master.SetType ( MdfLibrary::ChannelType::Master );
        master.SetSync ( MdfLibrary::ChannelSyncType::Time );
        master.SetDataType ( MdfLibrary::ChannelDataType::UnsignedIntegerLe );
        master.SetDataBytes ( 8 );

        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    bool found = false;
    const auto header = reader.GetHeader ();
    for ( const auto& dg : header.GetDataGroups () ) {
        for ( const auto& cg : dg.GetChannelGroups () ) {
            if ( cg.GetName () != "SiTestGroup" )
                continue;
            auto si = cg.GetSourceInformation ();
            EXPECT_EQ ( si.GetName (), "CAN_BUS_1" );
            EXPECT_EQ ( si.GetPath (), "/CAN/1" );
            EXPECT_EQ ( si.GetType (), MdfLibrary::SourceType::Bus );
            EXPECT_EQ ( si.GetBus  (), MdfLibrary::BusType::Can );
            found = true;
        }
    }
    EXPECT_TRUE ( found ) << "CG 'SiTestGroup' with SI block not found";
    reader.Close ();
}

// --- CN block (channel) -------------------------------------------
// Uses the CAN bus-logger configuration to check that the
// CAN_DataFrame.ID channel has the expected name, ChannelType,
// ChannelDataType and a non-zero bit count.
TEST_F ( MdfBlockTest, CnBlock_NameDataTypeAndBitCountRoundTrip ) {
    const auto path = MakePath ( "cn" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::MdfBusLogger,
                                       path.c_str () );
        writer.SetBusType ( MdfLibrary::MdfBusType::CAN );
        writer.SetStorageType ( MdfLibrary::MdfStorageType::VlsdStorage );
        ASSERT_TRUE ( writer.CreateBusLogConfiguration () );
        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        writer.StopMeasurement ( 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    auto df_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                               "_DataFrame" );
    ASSERT_TRUE ( df_group.has_value () );

    auto msg_id = FindChannelByName ( *df_group, "CAN_DataFrame.ID" );
    ASSERT_TRUE ( msg_id.has_value () );
    EXPECT_EQ ( msg_id->GetName (),     "CAN_DataFrame.ID" );
    EXPECT_EQ ( msg_id->GetType (),     MdfLibrary::ChannelType::FixedLength );
    EXPECT_EQ ( msg_id->GetDataType (), MdfLibrary::ChannelDataType::UnsignedIntegerLe );
    EXPECT_GT ( msg_id->GetBitCount (), 0U );
    reader.Close ();
}

// --- CC block (channel conversion) --------------------------------
// Creates a channel with a Linear CC (offset=0, scale=0.1) and
// validates the conversion type and parameters after roundtrip.
TEST_F ( MdfBlockTest, CcBlock_LinearConversionParametersRoundTrip ) {
    const auto path = MakePath ( "cc" );
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::Mdf4Basic,
                                       path.c_str () );
        auto dg = writer.CreateDataGroup ();
        auto cg = dg.CreateChannelGroup ();
        cg.SetName ( "CcTestGroup" );

        auto master = cg.CreateChannel ();
        master.SetName ( "t" );
        master.SetType ( MdfLibrary::ChannelType::Master );
        master.SetSync ( MdfLibrary::ChannelSyncType::Time );
        master.SetDataType ( MdfLibrary::ChannelDataType::UnsignedIntegerLe );
        master.SetDataBytes ( 8 );

        auto ch = cg.CreateChannel ();
        ch.SetName ( "Speed" );
        ch.SetType ( MdfLibrary::ChannelType::FixedLength );
        ch.SetDataType ( MdfLibrary::ChannelDataType::UnsignedIntegerLe );
        ch.SetDataBytes ( 2 );
        ch.SetUnit ( "km/h" );

        auto cc = ch.CreateChannelConversion ();
        cc.SetType ( MdfLibrary::ConversionType::Linear );
        cc.SetParameter ( 0, 0.0 );   // offset
        cc.SetParameter ( 1, 0.1 );   // scale

        ASSERT_TRUE ( writer.InitMeasurement () );
        writer.StartMeasurement ( 0 );
        master.SetChannelValue ( static_cast<uint64_t> ( 0 ) );
        ch.SetChannelValue ( static_cast<uint64_t> ( 1000 ) );
        writer.SaveSample ( cg, 0 );
        writer.StopMeasurement ( 1000000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    bool found = false;
    const auto header = reader.GetHeader ();
    for ( const auto& dg : header.GetDataGroups () ) {
        for ( const auto& cg : dg.GetChannelGroups () ) {
            auto speed = FindChannelByName ( cg, "Speed" );
            if ( !speed.has_value () )
                continue;
            EXPECT_EQ ( speed->GetUnit (), "km/h" );
            try {
                auto cc = speed->GetChannelConversion ();
                EXPECT_EQ ( cc.GetType (),      MdfLibrary::ConversionType::Linear );
                EXPECT_DOUBLE_EQ ( cc.GetParameter ( 0 ), 0.0 );
                EXPECT_NEAR ( cc.GetParameter ( 1 ), 0.1, 1e-10 );
                found = true;
            } catch ( const std::exception& e ) {
                ADD_FAILURE () << "CC block missing on Speed channel: " << e.what ();
            }
        }
    }
    EXPECT_TRUE ( found ) << "Speed channel with CC not found";
    reader.Close ();
}

// --- DT block (data block) ----------------------------------------
// Writes N samples using Mdf4Basic (stored in DT blocks) and verifies
// every sample is readable and correct via MdfChannelObserver.
TEST_F ( MdfBlockTest, DtBlock_SamplesReadableViaChannelObserver ) {
    const auto path = MakePath ( "dt" );
    constexpr uint64_t kNofSamples = 2;
    ASSERT_NO_FATAL_FAILURE ( WriteBasicFile ( path, "Value", kNofSamples ) );

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    auto dgs = reader.GetHeader ().GetDataGroups ();
    ASSERT_FALSE ( dgs.empty () );
    auto dg = dgs.front ();

    auto cgs = dg.GetChannelGroups ();
    ASSERT_FALSE ( cgs.empty () );
    auto cg = cgs.front ();

    auto ch = FindChannelByName ( cg, "Value" );
    ASSERT_TRUE ( ch.has_value () );

    MdfLibrary::MdfChannelObserver obs ( dg, cg, *ch );
    ASSERT_TRUE ( reader.ReadData ( dg ) );

    EXPECT_EQ ( obs.GetNofSamples (), static_cast<int64_t> ( kNofSamples ) );
    for ( uint64_t i = 0; i < kNofSamples; ++i ) {
        uint64_t val = 0;
        EXPECT_TRUE ( obs.GetChannelValue ( i, val ) );
        EXPECT_EQ ( val, i );
    }
    reader.Close ();
}

// --- SD block (signal data — VLSD) --------------------------------
// Uses VlsdStorage so the DataBytes payload is written to SD blocks.
// Verifies the 8-byte payload is read back correctly via observer.
TEST_F ( MdfBlockTest, SdBlock_VlsdDataBytesReadableViaObserver ) {
    const auto path = MakePath ( "sd" );
    const uint8_t kPayload[] = { 0xDE, 0xAD, 0xBE, 0xEF,
                                  0x01, 0x02, 0x03, 0x04 };
    {
        MdfLibrary::MdfWriter writer ( MdfLibrary::MdfWriterType::MdfBusLogger,
                                       path.c_str () );
        writer.SetBusType ( MdfLibrary::MdfBusType::CAN );
        writer.SetStorageType ( MdfLibrary::MdfStorageType::VlsdStorage );
        ASSERT_TRUE ( writer.CreateBusLogConfiguration () );
        ASSERT_TRUE ( writer.InitMeasurement () );

        constexpr uint64_t kStartNs = 100000000ULL;
        writer.StartMeasurement ( kStartNs );

        auto df_group = FindChannelGroupBySuffix ( writer.GetHeader (),
                                                   "_DataFrame" );
        ASSERT_TRUE ( df_group.has_value () );

        MdfLibrary::CanMessage msg;
        msg.SetMessageId ( 0xABC );
        msg.SetExtendedId ( false );
        msg.SetDataLength ( 8 );
        msg.SetDataBytes ( kPayload, 8 );
        writer.SaveCanMessage ( *df_group, kStartNs + 1, msg );

        writer.StopMeasurement ( kStartNs + 1000 );
        ASSERT_TRUE ( writer.FinalizeMeasurement () );
    }

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    auto dgs = reader.GetHeader ().GetDataGroups ();
    ASSERT_FALSE ( dgs.empty () );
    auto dg = dgs.front ();

    auto df_group = FindChannelGroupBySuffix ( reader.GetHeader (),
                                               "_DataFrame" );
    ASSERT_TRUE ( df_group.has_value () );

    auto data_bytes_ch = FindChannelByName ( *df_group,
                                             "CAN_DataFrame.DataBytes" );
    ASSERT_TRUE ( data_bytes_ch.has_value () );
    EXPECT_EQ ( data_bytes_ch->GetType (),
                MdfLibrary::ChannelType::VariableLength );

    MdfLibrary::MdfChannelObserver obs ( dg, *df_group, *data_bytes_ch );
    ASSERT_TRUE ( reader.ReadData ( dg ) );

    ASSERT_EQ ( obs.GetNofSamples (), 1 );
    std::vector<uint8_t> read_bytes;
    EXPECT_TRUE ( obs.GetChannelValue ( 0, read_bytes ) );
    ASSERT_EQ ( read_bytes.size (), 8U );
    for ( size_t i = 0; i < 8; ++i ) {
        EXPECT_EQ ( read_bytes[i], kPayload[i] ) << "Byte mismatch at index " << i;
    }
    reader.Close ();
}

// --- DZ block (compressed data) -----------------------------------
// SetCompressData(true) causes the writer to replace DT/SD blocks with
// DZ (zipped) equivalents.  Verifies that N samples written with
// compression enabled are read back identically via observer.
TEST_F ( MdfBlockTest, DzBlock_CompressedSamplesReadableViaObserver ) {
    const auto path = MakePath ( "dz" );
    constexpr uint64_t kNofSamples = 2;
    ASSERT_NO_FATAL_FAILURE (
        WriteBasicFile ( path, "CompValue", kNofSamples, /*compress=*/true ) );

    MdfLibrary::MdfReader reader ( path.c_str () );
    ASSERT_TRUE ( reader.Open () );
    ASSERT_TRUE ( reader.ReadEverythingButData () );

    auto dgs = reader.GetHeader ().GetDataGroups ();
    ASSERT_FALSE ( dgs.empty () );
    auto dg = dgs.front ();

    auto cgs = dg.GetChannelGroups ();
    ASSERT_FALSE ( cgs.empty () );
    auto cg = cgs.front ();

    auto ch = FindChannelByName ( cg, "CompValue" );
    ASSERT_TRUE ( ch.has_value () );

    MdfLibrary::MdfChannelObserver obs ( dg, cg, *ch );
    ASSERT_TRUE ( reader.ReadData ( dg ) );

    EXPECT_EQ ( obs.GetNofSamples (), static_cast<int64_t> ( kNofSamples ) );
    for ( uint64_t i = 0; i < kNofSamples; ++i ) {
        uint64_t val = 0;
        EXPECT_TRUE ( obs.GetChannelValue ( i, val ) );
        EXPECT_EQ ( val, i );
    }
    reader.Close ();
}
