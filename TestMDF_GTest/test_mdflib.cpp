#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mdflibrary/MdfWriter.h"

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
