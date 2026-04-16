#include <iostream>
#include <cstdio>

#include "mdflibrary/MdfReader.h"
#include "mdflibrary/MdfWriter.h"
#include "mdflibrary/MdfChannelObserver.h"

using namespace MdfLibrary;

// ----------------------
// BusLogger writer
// ----------------------
void writerBusLogger(const char* filePath) {
    MdfWriter writer(MdfWriterType::MdfBusLogger, filePath);
    writer.SetBusType(MdfBusType::CAN);
    writer.SetStorageType(MdfStorageType::VlsdStorage);
    writer.CreateBusLogConfiguration();

    auto file = writer.GetFile();
    auto dataGroups = file.GetDataGroups();

    MdfChannelGroup canFrameGroup = dataGroups.front().GetChannelGroups().front();
    bool found = false;
    for (auto& dg : dataGroups) {
        for (auto& cg : dg.GetChannelGroups()) {
            if (cg.GetName() == "CAN_DataFrame") {
                canFrameGroup = cg;
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (!found) return;

    writer.InitMeasurement();
    writer.StartMeasurement(100000000);

    for (int i = 0; i < 3; ++i) {
        uint64_t t_ns = (i+1) * 100000000;

        CanMessage msg;
        msg.SetMessageId(0x0CF00400);
        msg.SetExtendedId(true);
        msg.SetDlc(8);

        uint8_t torque_raw = 80 + i*20;
        uint16_t speed_raw = 6400 + i*1600;

        std::vector<uint8_t> payload(8, 0);
        payload[2] = torque_raw;
        payload[3] = speed_raw & 0xFF;
        payload[4] = (speed_raw >> 8) & 0xFF;
        msg.SetDataBytes(payload);

        writer.SaveCanMessage(canFrameGroup, t_ns, msg);
    }

    writer.StopMeasurement(300000000);
    writer.FinalizeMeasurement();
}

// ----------------------
// BusLogger reader
// ----------------------
void readerBusLogger(const char* filePath) {
    MdfReader reader(filePath);
    if (!reader.Open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << filePath << std::endl;
        return;
    }
    reader.ReadEverythingButData();

    auto file = reader.GetFile();
    auto header = file.GetHeader();

    uint64_t start_time_ns = header.GetStartTime();

    auto dataGroups = file.GetDataGroups();
    if (dataGroups.empty()) {
        std::cerr << "Error: no hay DataGroups en el archivo." << std::endl;
        return;
    }

    for (auto& dg : dataGroups) {
        auto cg_list = dg.GetChannelGroups();
        if (cg_list.empty()) continue;

        for (auto& cg : cg_list) {
            if (cg.GetName() == "CAN_DataFrame") {
                auto cn_list = cg.GetChannels();
                if (cn_list.empty()) continue;

                MdfChannel idChannel = cn_list.front();
                MdfChannel dataChannel = cn_list.front();
                MdfChannel timeChannel = cn_list.front();
                bool foundId = false, foundData = false, foundTime = false;

                for (auto& cn : cn_list) {
                    const std::string name = cn.GetName();
                    if (name == "CAN_DataFrame.ID") {
                        idChannel = cn; foundId = true;
                    } else if (name == "CAN_DataFrame.DataBytes") {
                        dataChannel = cn; foundData = true;
                    } else if (name == "t") {
                        timeChannel = cn; foundTime = true;
                    }
                }
                if (!foundId || !foundData || !foundTime) continue;

                MdfChannelObserver idObs(dg, cg, idChannel);
                MdfChannelObserver dataObs(dg, cg, dataChannel);
                MdfChannelObserver timeObs(dg, cg, timeChannel);

                reader.ReadData(dg);

                for (int64_t sample = 0; sample < idObs.GetNofSamples(); ++sample) {
                    double id_val = 0.0, ts_val = 0.0;
                    std::vector<uint8_t> payload;

                    bool id_ok = idObs.GetChannelValue(sample, id_val);
                    bool data_ok = dataObs.GetChannelValue(sample, payload);
                    bool ts_ok = timeObs.GetChannelValue(sample, ts_val);

                    if (id_ok && data_ok && ts_ok) {
                        uint32_t id = static_cast<uint32_t>(id_val);
                        uint64_t timestamp_ns = static_cast<uint64_t>(ts_val * 1e9) + start_time_ns;

                        if ((id & 0x1FFFFFFF) == 0x0CF00400 && payload.size() >= 5) {
                            // SPN 513: Engine Percent Torque
                            uint8_t torque_raw = payload[2];
                            double torque = torque_raw * 1.0 + (-125);

                            // SPN 190: Engine Speed
                            uint16_t speed_raw = payload[3] | (payload[4] << 8);
                            double speed = speed_raw * 0.125;

                            std::cout << "Timestamp=" << timestamp_ns << " ns"
                                      << " SPN 513 (Engine Percent Torque)=" << torque << " %"
                                      << " SPN 190 (Engine Speed)=" << speed << " rpm"
                                      << std::endl;
                        }
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

    writerBusLogger(filePath);
    readerBusLogger(filePath);
    return 0;
}

