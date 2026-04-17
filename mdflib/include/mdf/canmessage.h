/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <bitset>

#include "mdf/samplerecord.h"

namespace mdf {
  /** \brief Enumerate yhat defines type of CAN bus error. */
  enum class CanErrorType : uint8_t {
    UNKNOWN_ERROR = 0, ///< Unspecified error.
    BIT_ERROR = 1,     ///< CAN bit error.
    FORM_ERROR = 2,    ///< CAN format error.
    BIT_STUFFING_ERROR = 3, ///< Bit stuffing error.
    CRC_ERROR = 4, ///< Checksum error.
    ACK_ERROR = 5 ///< Acknowledgement error.
  };

  /** \brief Enumerate that defines type of CAN messages. */
  enum class MessageType : int {
    CAN_DataFrame = 0, ///< Normal CAN message
    CAN_RemoteFrame, ///< Remote frame message.
    CAN_ErrorFrame, ///< Error message.
    CAN_OverloadFrame, ///< Overload frame message.
  };

  /**
   * @brief IChannel class definition.
   */
  class IChannel;
  /**
   * @brief IChannelGroup class definition.
   */
  class IChannelGroup;
  /**
   * @brief IDataGroup class definition.
   */
  class IDataGroup;

  /** \brief Helper class when logging CAN and CAN FD messages.
   *
   * This class is used when doing bus logging of A CAN or CAN FD bus. The
   * MDF format for CAN logging is a type of standard. Channel naming is common
   * which simplifies the reading of the file.
   *
   * It is complex task to fix the bit stuffing that minimize number of bytes
   * stored but this class handle most of that complex handling.
   */

  class CanMessage {
  public:
    /**
     * @brief TypeOfMessage.
     * @param type type.
     */
    void TypeOfMessage ( MessageType type ) const { message_type_ = type; }
    [ [ nodiscard ] ] MessageType TypeOfMessage () const { return message_type_; };

    /** \brief DBC message ID. Note that bit 31 indicate extended ID.
     *
     * The message ID is the CAN ID + highest bit 31 set if the CAN ID
     * uses extended 29-bit ID. The message ID is actually used in a
     * DBC file and not sent on the CAN bus, well the extended bit is sent.
     * @param msg_id DBC Message ID
     */
    void MessageId ( uint32_t msg_id );

    /** \brief DBC message ID. Note that bit 31 indicate extended ID.
     *
     * The message ID is the CAN ID with the highest bit 31 set if the
     * CAN ID uses a 29-bit address.
     * @return DBC message ID.
     */
    /**
     * @brief MessageId.
     * @return [ [ nodiscard ] ] uint32_t.
     */
    [ [ nodiscard ] ] uint32_t MessageId () const;

      /** \brief 29/11 bit CAN message ID. Note that bit 31 is not used.
       *
       *  The CAN message ID identifies the message on a CAN bus. Note that
       *  there is a DBC message ID which is the CAN ID + highest bit 31 set
       *  if the CAN ID uses 29-bit addressing. This is a confusing naming
       *  that causes invalid handling of messages.
       * @return 29-bit CAN ID.
       */
    /**
     * @brief CanId.
     * @return [ [ nodiscard ] ] uint32_t.
     */
    [ [ nodiscard ] ] uint32_t CanId () const;

      /** \brief Set true if the CAN ID uses 20-bit addressing.
       *
       * @param extended True if CAN ID uses 29-bit addressing.
       */
      /**
       * @brief ExtendedId.
       * @param extended extended.
       */
      void ExtendedId ( bool extended );

      /** \brief Returns true if the CAN ID uses 29-bit addressing,
       *
       * @return True if CAN ID uses extended addressing.
       */
    /**
     * @brief ExtendedId.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool ExtendedId () const; ///< Returns the extended CAN ID.

      /** \brief Sets the CAN message data length code.
       *
       * Sets the data length code (DLC). The DLC is the same as data length for
       * CAN but not for CAN FD. Note that the DataBytes() function fix both data
       * length and the DLC code so this function is normally not used.
       * @param dlc Data length code.
       */
      /**
       * @brief Dlc.
       * @param dlc dlc.
       */
      void Dlc ( uint8_t dlc );

      /** \brief Returns the data length code (DLC).
       *
       * The DLC is equal to number of bytes for CAN messages but not for CAN FD
       * messages.
       *
       * @return Data length code for the message.
       */
    /**
     * @brief Dlc.
     * @return [ [ nodiscard ] ] uint8_t.
     */
    [ [ nodiscard ] ] uint8_t Dlc ()
      const; ///< Returns the CAN message length code.

      /** \brief Sets number of data bytes.
       *
       * The data length is not sent on the bus. Instead is it calculated from
       * the DLC code. Note that the DataBytes() function fix both data
       * length and the DLC code so this function is normally not used.
       * @param data_length Number of payload data bytes.
       */
      /**
       * @brief DataLength.
       * @param data_length data_length.
       */
      void DataLength ( uint8_t data_length );
    /**
     * @brief DataLength.
     * @return [ [ nodiscard ] ] uint8_t.
     */
    [ [ nodiscard ] ] uint8_t DataLength ()
      const; ///< Returns number of data bytes.

      /** \brief Sets the payload data bytes.
       *
       * This function sets the payload data bytes in the message. Note that this
       * function also set the data length and DLC code.
       * @param data
       */
      /**
       * @brief DataBytes.
       * @param data data.
       */
      void DataBytes ( std::vector<uint8_t> data );

      /** \brief Returns a reference to the payload data bytes. */
    [ [ nodiscard ] ] const std::vector<uint8_t>& DataBytes () const;

      /** \brief If set true, the message was transmitted. */
      void Dir ( bool transmit );
      /** \brief Returns true if the message was transmitted. */
    [ [ nodiscard ] ] bool Dir () const;

      /**
       * @brief Srr.
       * @param srr srr.
       */
      void Srr ( bool srr ); ///< Sets the SRR bit.
    /**
     * @brief Srr.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Srr () const; ///< Returns the SRR bit

      /**
       * @brief Edl.
       * @param FD FD.
       */
      void Edl ( bool edl ); ///< Extended (CAN FD) data length.
    /**
     * @brief Edl.
     * @param FD FD.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Edl () const; ///< Extended (CAN FD) data length.

      /**
       * @brief Brs.
       * @param brs brs.
       */
      void Brs ( bool brs ); ///< Bit rate switch (CAN FD).
    /**
     * @brief Brs.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Brs () const; ///< Bit rate switch (CAN FD).

      /**
       * @brief Esi.
       * @param FD FD.
       */
      void Esi ( bool esi ); ///< Error state indicator (CAN FD).
    /**
     * @brief Esi.
     * @param FD FD.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Esi () const; ///< Error state indicator (CAN FD).

      /**
       * @brief Rtr.
       * @param frame frame.
       */
      void Rtr ( bool rtr ); ///< Sets the RTR bit (remote frame).
    /**
     * @brief Rtr.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Rtr () const; ///< Returns the RTR bit.

      /**
       * @brief WakeUp.
       * @param wake_up wake_up.
       */
      void WakeUp ( bool wake_up ); ///< Indicate a CAN bus wake up status
    /**
     * @brief WakeUp.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool WakeUp () const; ///< Indicate a CAN bus wake up message

      /**
       * @brief SingleWire.
       * @param single_wire single_wire.
       */
      void SingleWire ( bool single_wire ); ///< Indicate a single wire CAN bus
    /**
     * @brief SingleWire.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool SingleWire () const; ///< Indicate a single wire CAN bus

      /**
       * @brief R0.
       * @param flag flag.
       */
      void R0 ( bool flag ); ///< Optional R0 flag.
    /**
     * @brief R0.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool R0 () const; ///< Optional R0 flag

      /**
       * @brief R1.
       * @param flag flag.
       */
      void R1 ( bool flag ); ///< Optional R1 flag.
    /**
     * @brief R1.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool R1 () const; ///< Optional R1 flag

      /**
       * @brief BusChannel.
       * @param channel channel.
       */
      void BusChannel ( uint8_t channel ); ///< Bus channel.
    /**
     * @brief BusChannel.
     * @return [ [ nodiscard ] ] uint8_t.
     */
    [ [ nodiscard ] ] uint8_t BusChannel () const; ///< Bus channel.

      /**
       * @brief BitPosition.
       * @param frame frame.
       */
      void BitPosition ( uint16_t position ); ///< Error bit position (error frame).
    /**
     * @brief BitPosition.
     * @return [ [ nodiscard ] ] uint16_t.
     */
    [ [ nodiscard ] ] uint16_t BitPosition () const; ///< Error bit position.

      /**
       * @brief ErrorType.
       * @param error_type error_type.
       */
      void ErrorType ( CanErrorType error_type ); ///< Type of error.
    /**
     * @brief ErrorType.
     * @return [ [ nodiscard ] ] CanErrorType.
     */
    [ [ nodiscard ] ] CanErrorType ErrorType () const; ///< Type of error.

      /**
       * @brief FrameDuration.
       * @param duration duration.
       */
      void FrameDuration ( uint32_t duration ); ///< Frame duration in nano-seconds.
    /**
     * @brief FrameDuration.
     * @return [ [ nodiscard ] ] uint32_t.
     */
    [ [ nodiscard ] ] uint32_t FrameDuration ()
      const; ///< Frame duration in nano-seconds.

      /**
       * @brief Crc.
       * @param crc crc.
       */
      void Crc ( uint32_t crc ); ///< CRC checksum
    /**
     * @brief Crc.
     * @return [ [ nodiscard ] ] uint32_t.
     */
    [ [ nodiscard ] ] uint32_t Crc () const; ///< Frame duration in nano-seconds.

      /**
       * @brief Timestamp.
       * @param s s.
       */
      void Timestamp ( double timestamp ); ///< Relative Timestamp (s)
    /**
     * @brief Timestamp.
     * @param s s.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double Timestamp () const; ///< Relative timestamp (s).

      /**
       * @brief DlcToLength.
       * @param dlc dlc.
       * @return static size_t.
       */
      static size_t DlcToLength ( uint8_t dlc ); ///< Return the data length by DLC.

      /**
       * @brief Reset.
       */
      void Reset (); ///< Reset all flags an payload data buffers.

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

      /** \brief Creates an MDF sample record. Used primarily internally. */
      void ToRaw ( MessageType msg_type, SampleRecord& sample,
      size_t max_data_length, bool save_index ) const;
    private:
      double timestamp_ = 0.0;
      uint8_t bus_channel_ = 0;
      uint32_t message_id_ = 0; ///< Message ID with bit 31 set if extended ID.
      uint8_t dlc_ = 0; ///< Data length code.
      std::bitset<16> flags_;   ///< All CAN flags.
      std::vector<uint8_t> data_bytes_; ///< Payload data.
      uint16_t bit_position_ = 0; ///< Error bit position.
      CanErrorType error_type_ = CanErrorType::UNKNOWN_ERROR; ///< Error type.
      uint32_t frame_duration_ = 0;
      uint32_t crc_ = 0; ///< CRC message checksum.

      mutable MessageType message_type_ = MessageType::CAN_DataFrame;
      mutable const IDataGroup* data_group_ = nullptr;
      mutable const IChannelGroup* channel_group_ = nullptr;
  };

  }  // namespace mdf