/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <algorithm>

#include "mdf/samplerecord.h"

namespace mdf {

  /**
   * @brief MdfWriter class definition.
   */
  class MdfWriter;
  /**
   * @brief IDataGroup class definition.
   */
  class IDataGroup;
  /**
   * @brief IChannelGroup class definition.
   */
  class IChannelGroup;

  /**
   * @brief enum class EthMessageType enumeration.
   */
  enum class EthMessageType : int {
    ETH_Frame,
    ETH_ChecksumError,
    ETH_LengthError,
    ETH_ReceiveError
  };

  /**
   * @brief enum class EthErrorType enumeration.
   */
  enum class EthErrorType : int {
    Unknown = 0,
    CollisionError = 1
  };

  /**
   * @brief EthMessage class definition.
   */
  class EthMessage {
  public:
    /**
     * @brief EthMessage.
     */
    EthMessage () = default;

    /**
     * @brief deprecated.
     * @return [ [.
     */
    [ [ deprecated ( "Use the default EthMessage() constructor instead." ) ] ]
      /**
       * @brief EthMessage.
       * @param writer writer.
       * @return explicit.
       */
      explicit EthMessage ( const MdfWriter& writer );

    /**
     * @brief MessageType.
     * @param type type.
     */
    void MessageType ( EthMessageType type ) const { message_type_ = type; }
    [ [ nodiscard ] ] EthMessageType MessageType () const { return message_type_; };

    /**
     * @brief BusChannel.
     * @param channel channel.
     */
    void BusChannel ( uint8_t channel ) {bus_channel_ = channel;};
    [ [ nodiscard ] ] uint8_t BusChannel () const {return bus_channel_;};

    /**
     * @brief Dir.
     * @param transmit transmit.
     */
    void Dir ( bool transmit ) { dir_ = transmit;};
    [ [ nodiscard ] ] bool Dir () const {return dir_;};

    /**
     * @brief ErrorType.
     * @param type type.
     */
    void ErrorType ( EthErrorType type ) {error_type_ = type;};
    [ [ nodiscard ] ] EthErrorType ErrorType () const {return error_type_;};

    /**
     * @brief Source.
     */
    void Source ( const uint8_t source [ 6 ] ) {
      /**
       * @brief std::copy_n.
       * @param source source.
       */
      std::copy_n ( source, source_.size (), source_.data () );
    }
      /**
       * @brief Source.
       * @param source source.
       */
      void Source ( const std::array<uint8_t, 6>& source ) { source_ = source; }
    [ [ nodiscard ] ] const std::array<uint8_t, 6>& Source () const { return source_;}

    /**
     * @brief Destination.
     */
    void Destination ( const uint8_t destination [ 6 ] ) {
      /**
       * @brief std::copy_n.
       * @param destination destination.
       */
      std::copy_n ( destination, destination_.size (), destination_.data () );
      }
      /**
       * @brief Destination.
       * @param destination destination.
       */
      void Destination ( const std::array<uint8_t, 6>& destination ) {
        destination_ = destination;
    }
    /**
     * @brief Destination.
     * @return [ [ nodiscard ] ] std::array<uint8_t, 6>&.
     */
    [ [ nodiscard ] ] const std::array<uint8_t, 6>& Destination () const {
        return destination_;
    }

      /**
       * @brief EthType.
       * @param type type.
       */
      void EthType ( uint16_t type ) { eth_type_ = type; }
    [ [ nodiscard ] ] uint16_t EthType () const { return eth_type_; }

    /**
     * @brief ReceivedDataByteCount.
     * @param nof_bytes nof_bytes.
     */
    void ReceivedDataByteCount ( uint16_t nof_bytes ) {
      received_data_byte_count_ = nof_bytes;
      }
    /**
     * @brief ReceivedDataByteCount.
     * @return [ [ nodiscard ] ] uint16_t.
     */
    [ [ nodiscard ] ] uint16_t ReceivedDataByteCount () const {
        return received_data_byte_count_;
    }

    /**
     * @brief DataLength.
     * @param nof_bytes nof_bytes.
     */
    void DataLength ( uint16_t nof_bytes ) {
      data_length_ = nof_bytes;
      }

    /**
     * @brief DataLength.
     * @return [ [ nodiscard ] ] uint16_t.
     */
    [ [ nodiscard ] ] uint16_t DataLength () const {
        return data_length_;
    }

    /**
     * @brief DataBytes.
     * @param data data.
     */
    void DataBytes ( const std::vector<uint8_t>& data );

    /**
     * @brief DataBytes.
     * @return [ [ nodiscard ] ] std::vector<uint8_t>&.
     */
    [ [ nodiscard ] ] const std::vector<uint8_t>& DataBytes () const {
        return data_bytes_;
    }

    /**
     * @brief Crc.
     * @param crc crc.
     */
    void Crc ( uint32_t crc ) {
      crc_ = crc;
    }

    /**
     * @brief Crc.
     * @return [ [ nodiscard ] ] uint32_t.
     */
    [ [ nodiscard ] ] uint32_t Crc () const {
        return crc_;
    }

    /**
     * @brief ExpectedCrc.
     * @param crc crc.
     */
    void ExpectedCrc ( uint32_t crc ) {
      expected_crc_ = crc;
    }

    /**
     * @brief ExpectedCrc.
     * @return [ [ nodiscard ] ] uint32_t.
     */
    [ [ nodiscard ] ] uint32_t ExpectedCrc () const {
        return expected_crc_;
    }
    /**
     * @brief PaddingByteCount.
     * @param nof_bytes nof_bytes.
     */
    void PaddingByteCount ( uint16_t nof_bytes ) {
      padding_byte_count_ = nof_bytes;
    }

    /**
     * @brief PaddingByteCount.
     * @return [ [ nodiscard ] ] uint16_t.
     */
    [ [ nodiscard ] ] uint16_t PaddingByteCount () const {
        return padding_byte_count_;
    }

    /**
     * @brief Reset.
     */
    void Reset ();

    /**
     * @brief ToRaw.
     * @param msg_type msg_type.
     * @param sample sample.
     */
    void ToRaw ( EthMessageType msg_type, SampleRecord& sample ) const;

    /**
     * @brief DataGroup.
     * @param data_group data_group.
     */
    void DataGroup ( const IDataGroup* data_group ) const {
      data_group_ = data_group;
    }

    /**
     * @brief ChannelGroup.
     * @param channel_group channel_group.
     */
    void ChannelGroup ( const IChannelGroup* channel_group ) const {
      channel_group_ = channel_group;
      }

    private:
      uint8_t bus_channel_ = 0;
      bool dir_ = false;
    EthErrorType error_type_ = EthErrorType::Unknown;
    std::array<uint8_t, 6> source_ = {};
    std::array<uint8_t, 6> destination_ = {};
    uint16_t eth_type_ = 0x0800; ///< IPv4 as default
    uint16_t received_data_byte_count_ = 0;
    uint16_t data_length_ = 0;
    std::vector<uint8_t> data_bytes_;
    uint32_t crc_ = 0;
    uint32_t expected_crc_ = 0;
    uint16_t padding_byte_count_ = 0;

    mutable EthMessageType message_type_ = EthMessageType::ETH_Frame;
    mutable const IDataGroup* data_group_ = nullptr;
    mutable const IChannelGroup* channel_group_ = nullptr;

    /**
     * @brief MakeDataFrame.
     * @param sample sample.
     */
    void MakeDataFrame ( SampleRecord& sample ) const;
    /**
     * @brief MakeChecksumError.
     * @param sample sample.
     */
    void MakeChecksumError ( SampleRecord& sample ) const;
    /**
     * @brief MakeLengthError.
     * @param sample sample.
     */
    void MakeLengthError ( SampleRecord& sample ) const;
    /**
     * @brief MakeReceiveError.
     * @param sample sample.
     */
    void MakeReceiveError ( SampleRecord& sample ) const;
  };

}  // namespace mdf