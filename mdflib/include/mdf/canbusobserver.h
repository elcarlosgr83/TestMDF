/**
 * @file canbusobserver.h
 * @brief MDF header declarations for canbusobserver.
 */

/*
* Copyright 2025 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <string_view>
#include <string>

#include "mdf/canmessage.h"
#include "mdf/isampleobserver.h"

namespace mdf {

  /**
   * @brief CanBusObserver class definition.
   */
  class CanBusObserver : public ISampleObserver {
  public:
    /**
     * @brief CanBusObserver.
     */
    CanBusObserver () = delete;
    /**
     * @brief CanBusObserver.
     * @param data_group data_group.
     * @param channel_group channel_group.
     */
    CanBusObserver ( const IDataGroup& data_group,
                     const IChannelGroup& channel_group );

    /**
     * @brief Name.
     * @return std::string.
     */
    std::string Name () const;

    /**
     * @brief NofSamples.
     * @return uint64_t number of samples.
     */
    uint64_t NofSamples () const { return nof_samples_; }

    /**
     * @brief GetCanMessage.
     * @param sample sample.
     * @return CanMessage*.
     */
    CanMessage* GetCanMessage ( uint64_t sample );

    std::function<bool ( uint64_t sample, const CanMessage& msg ) > OnCanMessage;
  protected:
    /**
     * @brief OnSample.
     * @param sample sample.
     * @param record_id record_id.
     * @param record record.
     * @return bool.
     */
    bool OnSample ( uint64_t sample, uint64_t record_id,
                    const std::vector<uint8_t>& record ) override;
  private:
    /**
     * @brief CanSample struct definition.
     */
    struct CanSample {
      uint64_t sample = 0;
      std::vector<uint8_t> record;
      std::vector<uint8_t> vlsd_data;
      /**
       * @brief Reset.
       */
      void Reset () {
        sample = 0;
        /**
         * @brief record.clear.
         */
        record.clear ();
        /**
         * @brief record.shrink_to_fit.
         */
        record.shrink_to_fit ();
        /**
         * @brief vlsd_data.clear.
         */
        vlsd_data.clear ();
        /**
         * @brief vlsd_data.shrink_to_fit.
         */
        vlsd_data.shrink_to_fit ();
      }
    };

    int64_t current_sample_index_ = -1;
    uint64_t nof_samples_ = 0;
    CanSample last_sample_;
    std::vector<std::unique_ptr<CanMessage>> sample_buffer_;
    bool new_sample_ = false;
    std::string base_name_;

    MessageType message_type_ = MessageType::CAN_DataFrame;
    const IChannelGroup& channel_group_;
    const IChannel* time_channel_ = nullptr; ///< Time channel
    const IChannel* bus_channel_ = nullptr; ///< Bus channel number
    const IChannel* ide_channel_ = nullptr; ///< Extended ID bit
    const IChannel* id_channel_ = nullptr; ///< Msg/CAN ID
    const IChannel* dlc_channel_ = nullptr; ///< Data Length Code
    const IChannel* length_channel_ = nullptr; ///< Data Length
    const IChannel* data_channel_ = nullptr; ///< Data bytes
    /**
     * @brief Direction.
     * @param enumerate enumerate.
     * @return IChannel* dir_channel_ = nullptr; ///<.
     */
    const IChannel* dir_channel_ = nullptr; ///< Direction (bool/enumerate)
    /**
     * @brief CRC.
     * @return IChannel* crc_channel_ = nullptr; ///<.
     */
    const IChannel* crc_channel_ = nullptr; ///< CRC (<= 21 bit)
    const IChannel* srr_channel_ = nullptr; ///< SRR bit
    const IChannel* edl_channel_ = nullptr; ///< EDL bit
    const IChannel* brs_channel_ = nullptr; ///< BRS bit
    const IChannel* esi_channel_ = nullptr; ///< ESI bit
    const IChannel* r0_channel_ = nullptr; ///< R0 bit
    const IChannel* r1_channel_ = nullptr; ///< R1 bit
    const IChannel* wake_up_channel_ = nullptr; ///< Wake Up bit
    const IChannel* single_wire_channel_ = nullptr; ///< Single Wire bit
    /**
     * @brief duration.
     * @param ns ns.
     * @return IChannel* frame_duration_channel_ = nullptr; ///< Frame.
     */
    const IChannel* frame_duration_channel_ = nullptr; ///< Frame duration (ns)
    /**
     * @brief position.
     * @param msg msg.
     * @return IChannel* bit_position_channel_ = nullptr; ///< Bit.
     */
    const IChannel* bit_position_channel_ = nullptr; ///< Bit position (error msg)
    const IChannel* error_type_channel_ = nullptr; ///< Error Type enumeration

    /**
     * @brief FindVLsdRecord.
     * @param channel_group channel_group.
     */
    void FindVLsdRecord ( const IChannelGroup& channel_group );

    /**
     * @brief HandleCallback.
     * @param record_id record_id.
     * @param record record.
     */
    void HandleCallback ( uint64_t record_id,
                          const std::vector<uint8_t>& record );

    /**
     * @brief HandleSample.
     * @param record_id record_id.
     * @param record record.
     */
    void HandleSample ( uint64_t record_id,
                        const std::vector<uint8_t>& record );

    /**
     * @brief CheckSampleBufferSize.
     * @return bool.
     */
    bool CheckSampleBufferSize ();
    /**
     * @brief ClearSampleBuffer.
     */
    void ClearSampleBuffer ();
    /**
     * @brief FireCallback.
     * @return bool.
     */
    bool FireCallback ();
    /**
     * @brief GetChannel.
     * @param sub_name sub_name.
     * @return IChannel*.
     */
    const IChannel* GetChannel ( const std::string_view& sub_name ) const;
    /**
     * @brief ParseCanMessage.
     * @param msg msg.
     */
    void ParseCanMessage ( CanMessage& msg ) const;
  };

} // mdf