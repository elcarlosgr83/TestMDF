#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <memory>

#include "mdflibrary/MdfReader.h"
#include "mdflibrary/MdfWriter.h"
#include "mdflibrary/MdfChannelObserver.h"

using namespace MdfLibrary;

void write(const std::string &filePath) {
    std::cout << "Writing MDF file to:" << filePath << std::endl;

    MdfWriter writer(MdfWriterType::MdfBusLogger, filePath.c_str());
    writer.SetBusType(MdfBusType::CAN);
    writer.SetStorageType(MdfStorageType::VlsdStorage);
    if (!writer.CreateBusLogConfiguration()) {
        std::cout << "Error: failed to create CAN bus log configuration" << std::endl;
        return;
    }

    auto fileObj = writer.GetFile();
    auto dataGroups = fileObj.GetDataGroups();
    if (dataGroups.empty()) {
        std::cout << "Error: no DataGroups available after configuration" << std::endl;
        return;
    }

    std::unique_ptr<MdfChannelGroup> canFrameGroup;
    for (auto& dg : dataGroups) {
        auto channelGroups = dg.GetChannelGroups();
        for (auto& cg : channelGroups) {
            if (cg.GetName() == "CAN_DataFrame") {
                canFrameGroup = std::make_unique<MdfChannelGroup>(cg.GetChannelGroup());
                break;
            }
        }
        if (canFrameGroup != nullptr) break;
    }
    if (canFrameGroup == nullptr) {
        std::cout << "Error: CAN_DataFrame group not found" << std::endl;
        return;
    }

    if (!writer.InitMeasurement()) {
        std::cout << "Error: failed to initialize measurement" << std::endl;
        return;
    }

    // Manual DBC assumptions (Tests/valid.dbc):
    // BO_ 2297431040 EEC1
    // SG_ ECU_Engine_Torque : 16|8@1+ (1,-125) [-125|125]
    // SG_ ECU_Engine_Speed  : 24|16@1+ (0.125,0) [0|3000]
    constexpr uint32_t kEec1MessageId = 2297431040U;
    constexpr double kTorqueOffset = -125.0;
    constexpr double kTorqueFactor = 1.0;
    constexpr double kTorqueMin = -125.0;
    constexpr double kTorqueMax = 125.0;
    constexpr double kSpeedOffset = 0.0;
    constexpr double kSpeedFactor = 0.125;
    constexpr double kSpeedMin = 0.0;
    constexpr double kSpeedMax = 3000.0;

    const auto encodeTorqueRaw = [](double engineeringValue,
                                    double minValue,
                                    double maxValue,
                                    double offset,
                                    double factor) -> uint8_t {
        const double clamped = std::clamp(engineeringValue, minValue, maxValue);
        const double raw = (clamped - offset) / factor;
        return static_cast<uint8_t>(std::llround(raw));
    };

    const auto encodeSpeedRaw = [](double engineeringValue,
                                   double minValue,
                                   double maxValue,
                                   double offset,
                                   double factor) -> uint16_t {
        const double clamped = std::clamp(engineeringValue, minValue, maxValue);
        const double raw = (clamped - offset) / factor;
        return static_cast<uint16_t>(std::llround(raw));
    };

    const uint64_t measurementStartNs = 100000000ULL;
    const uint64_t sampleStepNs = 100000000ULL;
    writer.StartMeasurement(measurementStartNs);

    for (int i = 0; i < 3; ++i) {
        uint64_t t_ns = measurementStartNs + static_cast<uint64_t>(i + 1) * sampleStepNs;

        CanMessage msg;
        msg.SetMessageId(kEec1MessageId); // EEC1
        msg.SetExtendedId(true);

        std::vector<uint8_t> payload(8, 0);

        {
            const double torque_eng = -45 + i * 20;  // engineering value (%)
            const uint8_t torque_raw = encodeTorqueRaw(torque_eng, kTorqueMin, kTorqueMax, kTorqueOffset, kTorqueFactor);
            payload[2] = torque_raw;  // bitStart=16 → byte 2
        }

        {
            const double speed_eng = 800 + i * 200;  // engineering value (rpm)
            const uint16_t speed_raw = encodeSpeedRaw(speed_eng, kSpeedMin, kSpeedMax, kSpeedOffset, kSpeedFactor);
            payload[3] = speed_raw & 0xFF;     // bitStart=24 → byte 3
            payload[4] = (speed_raw >> 8) & 0xFF;
        }

        msg.SetDataBytes(payload);
        writer.SaveCanMessage(*canFrameGroup, t_ns, msg);
    }

    writer.StopMeasurement(measurementStartNs + 3 * sampleStepNs);
    if (!writer.FinalizeMeasurement()) {
        std::cout << "Error: failed to finalize measurement" << std::endl;
        return;
    }

    std::cout << "MDF file written successfully." << std::endl;
}

void read(const std::string &filePath) {
    std::cout << "Reading MDF file from:" << filePath << std::endl;

    MdfReader reader(filePath.c_str());
    if (!reader.Open()) {
        std::cout << "Error: could not open file" << filePath << std::endl;
        return;
    }
    reader.ReadEverythingButData();

    auto fileObj = reader.GetFile();
    auto dataGroups = fileObj.GetDataGroups();
    if (dataGroups.empty()) {
        std::cout << "Error: no DataGroups in file." << std::endl;
        return;
    }

    std::cout << "Number of DataGroups:" << dataGroups.size() << std::endl;
    for (auto& dg : dataGroups) {
        auto cg_list = dg.GetChannelGroups();
        if (cg_list.empty()) continue;

        std::cout << "Processing DataGroup with" << cg_list.size() << "ChannelGroups" << std::endl;
        for (auto& cg : cg_list) {
            if (cg.GetName() == "CAN_DataFrame") {
                auto topLevelChannels = cg.GetChannels();
                if (topLevelChannels.empty()) {
                    continue;
                }

                MdfChannel timeChannel = topLevelChannels.front();
                MdfChannel frameChannel = topLevelChannels.front();
                bool foundTime = false;
                bool foundFrame = false;

                for (auto& channel : topLevelChannels) {
                    const std::string channelName = channel.GetName();
                    if (channelName == "t") {
                        timeChannel = channel;
                        foundTime = true;
                    } else if (channelName == "CAN_DataFrame") {
                        frameChannel = channel;
                        foundFrame = true;
                    }
                }

                if (!foundTime || !foundFrame) {
                    continue;
                }

                auto composedChannels = frameChannel.GetChannelCompositions();
                if (composedChannels.empty()) {
                    continue;
                }

                MdfChannel idChannel = composedChannels.front();
                MdfChannel ideChannel = composedChannels.front();
                MdfChannel dataChannel = composedChannels.front();
                bool foundId = false;
                bool foundIde = false;
                bool foundData = false;

                for (auto& channel : composedChannels) {
                    const std::string channelName = channel.GetName();
                    if (channelName == "CAN_DataFrame.ID") {
                        idChannel = channel;
                        foundId = true;
                    } else if (channelName == "CAN_DataFrame.IDE") {
                        ideChannel = channel;
                        foundIde = true;
                    } else if (channelName == "CAN_DataFrame.DataBytes") {
                        dataChannel = channel;
                        foundData = true;
                    }
                }

                if (!foundId || !foundIde || !foundData) {
                    continue;
                }

                MdfChannelObserver idObserver(dg, cg, idChannel);
                MdfChannelObserver ideObserver(dg, cg, ideChannel);
                MdfChannelObserver dataObserver(dg, cg, dataChannel);
                MdfChannelObserver timeObserver(dg, cg, timeChannel);

                if (!reader.ReadData(dg)) {
                    std::cout << "Warning: unable to read data for CAN_DataFrame" << std::endl;
                    continue;
                }

                const int64_t maxSamples = std::min({
                    idObserver.GetNofSamples(),
                    ideObserver.GetNofSamples(),
                    dataObserver.GetNofSamples(),
                    timeObserver.GetNofSamples()
                });

                for (int64_t sample = 0; sample < maxSamples; ++sample) {
                    uint64_t rawId = 0;
                    uint64_t rawIde = 0;
                    std::vector<uint8_t> payload;
                    double relativeTimeSeconds = 0.0;

                    const bool idOk = idObserver.GetChannelValue(sample, rawId);
                    const bool ideOk = ideObserver.GetChannelValue(sample, rawIde);
                    const bool dataOk = dataObserver.GetChannelValue(sample, payload);
                    const bool timeOk = timeObserver.GetChannelValue(sample, relativeTimeSeconds);

                    if (!idOk || !ideOk || !dataOk || !timeOk) {
                        continue;
                    }

                    const uint32_t messageId = (rawIde != 0)
                                                   ? (static_cast<uint32_t>(rawId) | 0x80000000U)
                                                   : static_cast<uint32_t>(rawId);

                    if (messageId == 2297431040U && payload.size() >= 5) {
                        const uint64_t timestamp_ns = static_cast<uint64_t>(std::llround(relativeTimeSeconds * 1e9));
                        const uint8_t torque_raw = payload[2];
                        const double torque = static_cast<double>(torque_raw) - 125.0;
                        const uint16_t speed_raw = static_cast<uint16_t>(payload[3] | (payload[4] << 8));
                        const double speed = static_cast<double>(speed_raw) * 0.125;

                        std::cout << "Timestamp=" << timestamp_ns << "ns"
                                  << "SPN 513 (Engine Percent Torque)=" << torque << "%"
                                  << "SPN 190 (Engine Speed)=" << speed << "rpm" << std::endl;
                    }
                }
            }
        }
    }
    reader.Close();
}


// ----------------------
// Main
// ----------------------
int main() {
    const char* filePath = "ECU_engine.mf4";

    // Delete file if it already exists
    std::remove(filePath);

    write(filePath);
    read(filePath);
    return 0;
}

