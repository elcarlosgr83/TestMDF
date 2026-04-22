#include "mdflogger.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <QDebug>
#include <QFile>

#include "mdflibrary/MdfChannelObserver.h"
#include "mdflibrary/MdfReader.h"
#include "mdflibrary/MdfWriter.h"

using namespace MdfLibrary;

MDFLogger::MDFLogger(QObject *parent) : QObject(parent) {}

void MDFLogger::write(const QString &filePath) {
    qDebug() << "Writing MDF file to:" << filePath;

    QFile file(filePath);
    if (file.exists()) {
        if (!file.remove()) {
            qDebug() << "Error: could not remove existing file" << filePath;
            return;
        }
    }

    MdfWriter writer(MdfWriterType::MdfBusLogger, filePath.toStdString().c_str());
    writer.SetBusType(MdfBusType::CAN);
    writer.SetStorageType(MdfStorageType::VlsdStorage);
    if (!writer.CreateBusLogConfiguration()) {
        qDebug() << "Error: failed to create CAN bus log configuration";
        return;
    }

    auto fileObj = writer.GetFile();
    auto dataGroups = fileObj.GetDataGroups();
    if (dataGroups.empty()) {
        qDebug() << "Error: no DataGroups available after configuration";
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
        qDebug() << "Error: CAN_DataFrame group not found";
        return;
    }

    if (!writer.InitMeasurement()) {
        qDebug() << "Error: failed to initialize measurement";
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
        qDebug() << "Error: failed to finalize measurement";
        return;
    }

    qDebug() << "MDF file written successfully.";
}

void MDFLogger::read(const QString &filePath) {
    qDebug() << "Reading MDF file from:" << filePath;

    MdfReader reader(filePath.toStdString().c_str());
    if (!reader.Open()) {
        qDebug() << "Error: could not open file" << filePath;
        return;
    }
    reader.ReadEverythingButData();

    auto fileObj = reader.GetFile();
    auto dataGroups = fileObj.GetDataGroups();
    if (dataGroups.empty()) {
        qDebug() << "Error: no DataGroups in file.";
        return;
    }

    qDebug() << "Number of DataGroups:" << dataGroups.size();
    for (auto& dg : dataGroups) {
        auto cg_list = dg.GetChannelGroups();
        if (cg_list.empty()) continue;

        qDebug() << "Processing DataGroup with" << cg_list.size() << "ChannelGroups";
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
                    qDebug() << "Warning: unable to read data for CAN_DataFrame";
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

                        qDebug() << "Timestamp=" << timestamp_ns << "ns"
                                 << "SPN 513 (Engine Percent Torque)=" << torque << "%"
                                 << "SPN 190 (Engine Speed)=" << speed << "rpm";
                    }
                }
            }
        }
    }
    reader.Close();
}
