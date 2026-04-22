/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <vector>

#include "mdf/samplerecord.h"

namespace mdf {

  /**
   * @brief IDataGroup class definition.
   */
  class IDataGroup;
  /**
   * @brief IChannelGroup class definition.
   */
  class IChannelGroup;


  /**
   * @brief enum class MostMessageType enumeration.
   */
  enum class MostMessageType : uint8_t {
    Message,
    Packet,
    EthernetPacket,
    SignalState,
    MaxPosInfo,
    BoundDesc,
    AllocTable,
    SysLockState,
    ShutdownFlag
  };

  /**
   * @brief enum class MostSpeed enumeration.
   */
  enum class MostSpeed : uint8_t {
    Most25 = 0,
    Most50 = 1,
    Most150 = 2
  };

  /**
   * @brief enum class MostTransferType enumeration.
   */
  enum class MostTransferType : uint8_t {
    Spy = 0,
    Node = 1
  };

  /**
   * @brief enum class MostDirection enumeration.
   */
  enum class MostDirection : uint8_t {
    Rx = 0,
    Tx = 1
  };

  /**
   * @brief enum class MostCompleteAck enumeration.
   */
  enum class MostCompleteAck : uint8_t {
    NoResponse = 0,
    CrcError = 1,
    Ok = 4,
  };

  /**
   * @brief enum class MostPreemptiveAck enumeration.
   */
  enum class MostPreemptiveAck : uint8_t {
    NoResponse = 0,
    BufferFull = 1,
    Ok = 4,
  };

  /**
   * @brief enum class MostTxAck enumeration.
   */
  enum class MostTxAck : uint8_t {
    Ignored = 0x00,
    Ok = 0x01,
    FailedFormatError = 0x02,
    FailedNetworkOff = 0x04,
    FailedTimeout = 0x05,
    FailedWrongTarget = 0x08,
    OkOneSuccess = 0x09,
    FailedBadCrc = 0x0C,
    FailedReceiverBufferFull = 0x0E
  };

  /**
   * @brief enum class MostControlMessageType enumeration.
   */
  enum class MostControlMessageType : uint8_t {
    NormalMessage = 0x00,
    RemoteRead = 0x01,
    RemoteWrite = 0x02,
    ResourceAllocate = 0x03,
    ResourceDeallocate = 0x04,
    RemoteGetSource = 0x05,

  };

  /**
   * @brief enum class MostStateOfSignal enumeration.
   */
  enum class MostStateOfSignal : uint8_t {
    Unknown = 0,
    SignalOnLock = 1,
    SignalOff = 2,
    SignalOnNoLock = 3,
    StableLock = 16,
    CriticalUnlock = 32
  };

  /**
   * @brief enum class MostTableLayout enumeration.
   */
  enum class MostTableLayout : uint8_t {
    ChannelResourceAllocationTable = 0,
    LabelList = 1
  };

  /**
   * @brief IMostEvent class definition.
   */
  class IMostEvent {
  public:
    /**
     * @brief IMostEvent.
     */
    IMostEvent () = delete;
    /**
     * @brief ~IMostEvent.
     */
    virtual ~IMostEvent () = default;

    /**
     * @brief BusChannel.
     * @param bus_channel bus_channel.
     */
    void BusChannel ( uint8_t bus_channel ) {bus_channel_ = bus_channel;}
    [ [ nodiscard ] ] uint8_t BusChannel () const {return bus_channel_;}

    [ [ nodiscard ] ] MostMessageType MessageType () const { return message_type_;}

    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    virtual void ToRaw ( SampleRecord& sample ) const = 0;

    /**
     * @brief DataGroup.
     * @param data_group data_group.
     */
    void DataGroup ( const IDataGroup* data_group ) const { data_group_ = data_group; }
      /**
       * @brief ChannelGroup.
       * @param channel_group channel_group.
       */
      void ChannelGroup ( const IChannelGroup* channel_group ) const { channel_group_ = channel_group; }

    protected:
      /**
       * @brief IMostEvent.
       * @param type type.
       */
      explicit IMostEvent ( MostMessageType type );
      mutable const IDataGroup* data_group_ = nullptr;
    mutable const IChannelGroup* channel_group_ = nullptr;

  private:
    MostMessageType message_type_;
    uint8_t bus_channel_ = 0;
  };

  /**
   * @brief MostEthernetPacket class definition.
   */
  class MostEthernetPacket : public IMostEvent {
  public:
    /**
     * @brief MostEthernetPacket.
     */
    MostEthernetPacket ();

    /**
     * @brief Speed.
     * @param speed speed.
     */
    void Speed ( MostSpeed speed ) { speed_ = speed; }
    [ [ nodiscard ] ] MostSpeed Speed () const { return speed_; }

      /**
       * @brief TransferType.
       * @param type type.
       */
      void TransferType ( MostTransferType type ) { transfer_type_ = type; }
    [ [ nodiscard ] ] MostTransferType TransferType () const { return transfer_type_; }

      /**
       * @brief Direction.
       * @param direction direction.
       */
      void Direction ( MostDirection direction ) { direction_ = direction; }
    [ [ nodiscard ] ] MostDirection Direction () const { return direction_; }

      /**
       * @brief Source.
       * @param source source.
       */
      void Source ( uint64_t source ) { source_ = source; }
    [ [ nodiscard ] ] uint64_t Source () const { return source_; }

      /**
       * @brief Destination.
       * @param destination destination.
       */
      void Destination ( uint64_t destination ) { destination_ = destination; }
    [ [ nodiscard ] ] uint64_t Destination () const { return destination_; }

      /**
       * @brief SpecifiedNofBytes.
       * @param nof_bytes nof_bytes.
       */
      void SpecifiedNofBytes ( uint16_t nof_bytes ) { specified_nof_bytes_ = nof_bytes; }
    [ [ nodiscard ] ] uint16_t SpecifiedNofBytes () const { return specified_nof_bytes_; }

      /**
       * @brief ReceivedNofBytes.
       * @param nof_bytes nof_bytes.
       */
      void ReceivedNofBytes ( uint16_t nof_bytes ) { received_nof_bytes_ = nof_bytes; }
    [ [ nodiscard ] ] uint16_t ReceivedNofBytes () const { return received_nof_bytes_; }

    /**
     * @brief DataBytes.
     * @param bytes bytes.
     */
    void DataBytes ( std::vector<uint8_t> bytes );
    /**
     * @brief DataBytes.
     * @return [ [ nodiscard ] ] std::vector<uint8_t>&.
     */
    [ [ nodiscard ] ] const std::vector<uint8_t>& DataBytes () const;

    /**
     * @brief Crc.
     * @param crc crc.
     */
    void Crc ( uint32_t crc ) { crc_ = crc; }
    [ [ nodiscard ] ] uint32_t Crc () const { return crc_; }

    /**
     * @brief CompleteAck.
     * @param ack ack.
     */
    void CompleteAck ( MostCompleteAck ack ) { complete_ack_ = ack; }
    [ [ nodiscard ] ] MostCompleteAck CompleteAck () const { return complete_ack_; }

    /**
     * @brief PreemptiveAck.
     * @param ack ack.
     */
    void PreemptiveAck ( MostPreemptiveAck ack ) { preemptive_ack_ = ack; }
    [ [ nodiscard ] ] MostPreemptiveAck PreemptiveAck () const { return preemptive_ack_; }

    /**
     * @brief TxAck.
     * @param ack ack.
     */
    void TxAck ( uint8_t ack ) { tx_ack_ = ack; }
    [ [ nodiscard ] ] uint8_t TxAck () const { return tx_ack_; }

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

    /**
     * @brief MostEthernetPacket.
     * @param type type.
     */
    explicit MostEthernetPacket ( MostMessageType type );

  private:
    MostSpeed speed_ = MostSpeed::Most25;
    MostTransferType transfer_type_ = MostTransferType::Spy;
    MostDirection direction_ = MostDirection::Rx;
    uint64_t source_ = 0;
    uint64_t destination_ = 0;
    uint16_t specified_nof_bytes_ = 0;
    uint16_t received_nof_bytes_ = 0;
    std::vector<uint8_t> data_bytes_;

    uint32_t crc_ = 0;
    MostCompleteAck complete_ack_ = MostCompleteAck::Ok;
    MostPreemptiveAck preemptive_ack_ = MostPreemptiveAck::Ok;
    uint8_t tx_ack_ = 0;
  };

  /**
   * @brief MostPacket class definition.
   */
  class MostPacket : public MostEthernetPacket {
  public:
    /**
     * @brief MostPacket.
     */
    MostPacket ();

    /**
     * @brief PacketIndex.
     * @param packet_index packet_index.
     */
    void PacketIndex ( uint8_t packet_index ) { packet_index_ = packet_index; }
    [ [ nodiscard ] ] uint8_t PacketIndex () const { return packet_index_;}

  protected:
    /**
     * @brief MostPacket.
     * @param type type.
     */
    explicit MostPacket ( MostMessageType type );
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

  private:
    uint8_t packet_index_ = 0;
  };

  /**
   * @brief MostMessage class definition.
   */
  class MostMessage : public MostPacket {
  public:
    /**
     * @brief MostMessage.
     */
    MostMessage ();

      /**
       * @brief TxFailed.
       * @param failed failed.
       */
      void TxFailed ( bool failed ) { tx_failed_ = failed; }
    [ [ nodiscard ] ] bool TxFailed () const { return tx_failed_;}

      /**
       * @brief ControlMessageType.
       * @param type type.
       */
      void ControlMessageType ( MostControlMessageType type ) { control_message_type_ = type; }
    [ [ nodiscard ] ] MostControlMessageType ControlMessageType () const { return control_message_type_;}

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;
  private:
    bool tx_failed_ = false;
    MostControlMessageType control_message_type_ =
    MostControlMessageType::NormalMessage;
    };

    /**
     * @brief MostSignalState class definition.
     */
    class MostSignalState : public IMostEvent {
    public:
      /**
       * @brief MostSignalState.
       */
      MostSignalState ();

      /**
       * @brief SignalState.
       * @param state state.
       */
      void SignalState ( MostStateOfSignal state ) { state_ = state; }
    [ [ nodiscard ] ] MostStateOfSignal SignalState () const { return state_; }

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

  private:
    MostStateOfSignal state_ = MostStateOfSignal::Unknown;
    };

    /**
     * @brief MostMaxPosInfo class definition.
     */
    class MostMaxPosInfo : public IMostEvent {
    public:
      /**
       * @brief MostMaxPosInfo.
       */
      MostMaxPosInfo ();

      /**
       * @brief DeviceCount.
       * @param count count.
       */
      void DeviceCount ( uint8_t count ) { device_count_ = count; }
    [ [ nodiscard ] ] uint8_t DeviceCount () const { return device_count_; }

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

  private:
    uint8_t device_count_ = 0;
    };

    /**
     * @brief MostBoundDesc class definition.
     */
    class MostBoundDesc : public IMostEvent {
    public:
      /**
       * @brief MostBoundDesc.
       */
      MostBoundDesc ();

      /**
       * @brief BoundaryCount.
       * @param count count.
       */
      void BoundaryCount ( uint16_t count ) { boundary_count_ = count; }
    [ [ nodiscard ] ] uint16_t BoundaryCount () const { return boundary_count_; }

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

  private:
    uint16_t boundary_count_ = 0;
    };

    /**
     * @brief MostAllocTable class definition.
     */
    class MostAllocTable : public IMostEvent {
    public:
      /**
       * @brief MostAllocTable.
       */
      MostAllocTable ();

      /**
       * @brief FreeByteCount.
       * @param count count.
       */
      void FreeByteCount ( uint16_t count ) { free_byte_count_ = count; }
    [ [ nodiscard ] ] uint16_t FreeByteCount () const { return free_byte_count_; }

      /**
       * @brief TableLayout.
       * @param layout layout.
       */
      void TableLayout ( MostTableLayout layout ) { layout_ = layout; }
    [ [ nodiscard ] ] MostTableLayout TableLayout () const { return layout_; }

    /**
     * @brief TableData.
     * @param bytes bytes.
     */
    void TableData ( std::vector<uint8_t> bytes );
    /**
     * @brief TableData.
     * @return [ [ nodiscard ] ] std::vector<uint8_t>&.
     */
    [ [ nodiscard ] ] const std::vector<uint8_t>& TableData () const;

    protected:
      /**
       * @brief ToRaw.
       * @param sample sample.
       */
      void ToRaw ( SampleRecord& sample ) const override;

    private:
      uint16_t free_byte_count_ = 0;
      MostTableLayout layout_ = MostTableLayout::ChannelResourceAllocationTable;
      std::vector<uint8_t> table_data_;
  };

  /**
   * @brief MostSysLockState class definition.
   */
  class MostSysLockState : public IMostEvent {
  public:
    /**
     * @brief MostSysLockState.
     */
    MostSysLockState ();

    /**
     * @brief RingIsClosed.
     * @param closed closed.
     */
    void RingIsClosed ( bool closed ) { ring_is_closed_ = closed; }
    [ [ nodiscard ] ] bool RingIsClosed () const { return ring_is_closed_; }

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

  private:
    bool ring_is_closed_ = false;
  };

  /**
   * @brief MostShutdownFlag class definition.
   */
  class MostShutdownFlag : public IMostEvent {
  public:
    /**
     * @brief MostShutdownFlag.
     */
    MostShutdownFlag ();

      /**
       * @brief ShutdownFlag.
       * @param shutdown shutdown.
       */
      void ShutdownFlag ( bool shutdown ) { shutdown_flag_ = shutdown; }
    [ [ nodiscard ] ] bool ShutdownFlag () const { return shutdown_flag_; }

  protected:
    /**
     * @brief ToRaw.
     * @param sample sample.
     */
    void ToRaw ( SampleRecord& sample ) const override;

  private:
    bool shutdown_flag_ = false;
    };

  }  // namespace mdf