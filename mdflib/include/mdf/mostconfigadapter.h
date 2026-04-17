/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/iconfigadapter.h"

namespace mdf {

  /**
   * @brief MostConfigAdapter class definition.
   */
  class MostConfigAdapter : public IConfigAdapter {
  public:
    /**
     * @brief MostConfigAdapter.
     */
    MostConfigAdapter () = delete;
    /**
     * @brief MostConfigAdapter.
     * @param writer writer.
     * @return explicit.
     */
    explicit MostConfigAdapter ( const MdfWriter& writer );

    /**
     * @brief CreateConfig.
     * @param dg_block dg_block.
     */
    void CreateConfig ( IDataGroup& dg_block ) override;

  protected:

    /** \brief Creates the MOST_Message channel group.
     *
     * The MOST_Message channel group consists of 2 top-most channels, time
     * and the a message frame channel. The message frame channel have so-called
     * composite channel a.k.a as sub-channels and below is the channel group
     * layout.
     *
     * Note that the VLSD offset must be the last 8 bytes in the record. This
     * is an internal design requirement as this offset is updated when the sample
     * is written to th the file.
     * <table>
     * <caption id="multi_row">MOST_Message Layout</caption>
     * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
     * <tr><td>0-7</td><td>Time [s]</td></tr>
     * <tr><td>8</td><td>Bus Channel</td></tr>
     * <tr><td>9:0-1</td><td>Speed (enumerate)</td></tr>
     * <tr><td>9:2</td><td>Transfer Type (enumerate)</td></tr>
     * <tr><td>9:3</td><td>Direction (enumerate)</td></tr>
     * <tr><td>10-11</td><td>Source Address (16-bit)</td></tr>
     * <tr><td>12-13</td><td>Destination Address (16-bit)</td></tr>
     * <tr><td>14-15</td><td>Specified Number of Data Bytes (16-bit)</td></tr>
     * <tr><td>16-17</td><td>Received Number of Data Bytes (16-bit)</td></tr>
     * <tr><td>18-19</td><td>Number of Data Bytes (16-bit)</td></tr>
     * <tr><td>20-27</td><td>Offset to VLSD/SD (64-bit). Must be last</td></tr>
     * <tr><td colspan="2">Non-Mandatory Members</td></tr>
     * <tr><td>20-23</td><td>CRC checksum (32-bit)</td></tr>
     * <tr><td>24:0-2</td><td>Complete ACK (enumerate)</td></tr>
     * <tr><td>24:3-5</td><td>Pre-emptive ACK (enumerate)</td></tr>
     * <tr><td>24:6</td><td>Tx Failed Flag (boolean)</td></tr>
     * <tr><td>25:0-3</td><td>Tx ACK</td></tr>
     * <tr><td>25:4-7</td><td>Most Control Message Type (enumerate)</td></tr>
     * <tr><td>26</td><td>Packet Index</td></tr>
     * <tr><td>27-34</td><td>Offset to VLSD/SD (64-bit). Must be last</td></tr>
     * </table>
     * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostMessage.
     * @param data_group data_group.
     */
    void CreateMostMessage ( IDataGroup& data_group ) const;

    /** \brief Creates the MOST_EthernetPacket channel group.
    *
    * The MOST_EthernetPacket channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have so-called
    * composite channel a.k.a as sub-channels and below is the channel group
    * layout.
     *
     * Note that that the VLSD offset must be the last 8 byte in the record
     * buffer. This is an internal requirement.
    * <table>
    * <caption id="multi_row">MOST_EthernetPacket Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9:0-1</td><td>Speed (enumerate)</td></tr>
    * <tr><td>9:2</td><td>Transfer Type (enumerate)</td></tr>
    * <tr><td>9:3</td><td>Direction (enumerate)</td></tr>
    * <tr><td>10-15</td><td>Source Address (48-bit)</td></tr>
    * <tr><td>16-21</td><td>Destination Address (48-bit)</td></tr>
    * <tr><td>22-23</td><td>Specified Number of Data Bytes (16-bit)</td></tr>
    * <tr><td>24-25</td><td>Received Number of Data Bytes (16-bit)</td></tr>
    * <tr><td>26-27</td><td>Number of Data Bytes (16-bit)</td></tr>
    * <tr><td>28-35</td><td>Offset to VLSD/SD (64-bit)</td></tr>
    * <tr><td colspan="2">Non-Mandatory Members</td></tr>
    * <tr><td>28-31</td><td>CRC checksum (32-bit)</td></tr>
    * <tr><td>32:0-2</td><td>Complete ACK (enumerate)</td></tr>
    * <tr><td>32:3-5</td><td>Pre-emptive ACK (enumerate)</td></tr>
    * <tr><td>33:0-3</td><td>Tx ACK</td></tr>
    * <tr><td>34-41</td><td>Offset to VLSD/SD (64-bit)</td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostEthernetPacket.
     * @param data_group data_group.
     */
    void CreateMostEthernetPacket ( IDataGroup& data_group ) const;

    /** \brief Creates the MOST_Packet channel group.
    *
    * The MOST_Packet channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have so-called
    * composite channel a.k.a as sub-channels and below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_Packet Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9:0-1</td><td>Speed (enumerate)</td></tr>
    * <tr><td>9:2</td><td>Transfer Type (enumerate)</td></tr>
    * <tr><td>9:3</td><td>Direction (enumerate)</td></tr>
    * <tr><td>10-11</td><td>Source Address (16-bit)</td></tr>
    * <tr><td>12-13</td><td>Destination Address (16-bit)</td></tr>
    * <tr><td>14-15</td><td>Specified Number of Data Bytes (16-bit)</td></tr>
    * <tr><td>16-17</td><td>Received Number of Data Bytes (16-bit)</td></tr>
    * <tr><td>18-19</td><td>Number of Data Bytes (16-bit)</td></tr>
    * <tr><td>20-27</td><td>Offset to VLSD/SD (64-bit)</td></tr>
    * <tr><td colspan="2">Non-Mandatory Members</td></tr>
    * <tr><td>20-23</td><td>CRC checksum (32-bit)</td></tr>
    * <tr><td>24:0-2</td><td>Complete ACK (enumerate)</td></tr>
    * <tr><td>24:3-5</td><td>Pre-emptive ACK (enumerate)</td></tr>
    * <tr><td>25:0-3</td><td>Tx ACK</td></tr>
    * <tr><td>26</td><td>Packet Index</td></tr>
    * <tr><td>27-34</td><td>Offset to VLSD/SD (64-bit)</td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostPacket.
     * @param data_group data_group.
     */
    void CreateMostPacket ( IDataGroup& data_group ) const ;

    /** \brief Creates the MOST_SignalState channel group.
    *
    * The MOST_SignalState channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have
    * composite channels a.k.a as sub-channels. Below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_SignalState Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9</td><td>State (enumerate)</td></tr>
    * </table>
    * @param data_group Reference to the data group.
      */
    /**
     * @brief CreateMostSignalState.
     * @param data_group data_group.
     */
    void CreateMostSignalState ( IDataGroup& data_group ) const;

    /** \brief Creates the MOST_MaxPosInfo channel group.
    *
    * The MOST_MaxPosInfo channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have
    * composite channels a.k.a as sub-channels. Below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_MaxPosInfo Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9</td><td>DeviceCount</td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostMaxPosInfo.
     * @param data_group data_group.
     */
    void CreateMostMaxPosInfo ( IDataGroup& data_group ) const;

    /** \brief Creates the MOST_BoundDesc channel group.
    *
    * The MOST_BoundDesc channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have
    * composite channels a.k.a as sub-channels. Below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_BoundDesc Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9-10</td><td>SBC [bytes] (16-bits) </td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostBoundDesc.
     * @param data_group data_group.
     */
    void CreateMostBoundDesc ( IDataGroup& data_group ) const ;

    /** \brief Creates the MOST_AllocTable channel group.
    *
    * The MOST_AllocTable channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have
    * composite channels a.k.a as sub-channels. Below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_AllocTable Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9-10</td><td>Free Byte Count [bytes] (16-bits)</td></tr>
    * <tr><td>11</td><td>Table Layout (Enumerate)</td></tr>
    * <tr><td>12-13</td><td>Table Length [bytes] (16-bits)</td></tr>
    * <tr><td>14-21</td><td>Table Data VLSD Offset (64-bits)</td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostAllocTable.
     * @param data_group data_group.
     */
    void CreateMostAllocTable ( IDataGroup& data_group ) const ;

    /** \brief Creates the MOST_SysLockState channel group.
    *
    * The MOST_SysLockState channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have
    * composite channels a.k.a as sub-channels. Below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_SysLockState Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9</td><td>SysLockState (enumerate)</td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostSysLockState.
     * @param data_group data_group.
     */
    void CreateMostSysLockState ( IDataGroup& data_group ) const;

    /** \brief Creates the MOST_ShutdownFlag channel group.
    *
    * The MOST_ShutdownFlag channel group consists of 2 top-most channels, time
    * and the a message frame channel. The message frame channel have
    * composite channels a.k.a as sub-channels. Below is the channel group
    * layout.
    * <table>
    * <caption id="multi_row">MOST_ShutdownFlag Layout</caption>
    * <tr><th>Byte:Bit Offset</th><th>Channel Description</th></tr>
    * <tr><td>0-7</td><td>Time [s]</td></tr>
    * <tr><td>8</td><td>Bus Channel</td></tr>
    * <tr><td>9</td><td>Shutdown Flag (enumerate)</td></tr>
    * </table>
    * @param data_group Reference to the data group.
     */
    /**
     * @brief CreateMostShutdownFlag.
     * @param data_group data_group.
     */
    void CreateMostShutdownFlag ( IDataGroup& data_group ) const;

  private:
    /**
     * @brief CreateEthernetPacketChannel.
     * @param channel_group channel_group.
     */
    void CreateEthernetPacketChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreatePacketChannel.
     * @param channel_group channel_group.
     */
    void CreatePacketChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateMessageChannel.
     * @param channel_group channel_group.
     */
    void CreateMessageChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateSignalStateChannel.
     * @param channel_group channel_group.
     */
    void CreateSignalStateChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateMaxPosInfoChannel.
     * @param channel_group channel_group.
     */
    void CreateMaxPosInfoChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateBoundDescChannel.
     * @param channel_group channel_group.
     */
    void CreateBoundDescChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateAllocTableChannel.
     * @param channel_group channel_group.
     */
    void CreateAllocTableChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateSysLockStateChannel.
     * @param channel_group channel_group.
     */
    void CreateSysLockStateChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateShutdownFlagChannel.
     * @param channel_group channel_group.
     */
    void CreateShutdownFlagChannel ( IChannelGroup& channel_group ) const;
    /**
     * @brief CreateMandatoryMembers.
     * @param parent_frame parent_frame.
     */
    void CreateMandatoryMembers ( IChannel& parent_frame ) const;

    /**
     * @brief CreateSpeedChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateSpeedChannel ( IChannel& parent_channel,
                              uint32_t byte_offset ) const;
    /**
     * @brief CreateStateChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateStateChannel ( IChannel& parent_channel,
                              uint32_t byte_offset ) const;
    /**
     * @brief CreateDeviceCountChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateDeviceCountChannel ( IChannel& parent_channel,
                                    uint32_t byte_offset ) const;
    /**
     * @brief CreateSbcChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateSbcChannel ( IChannel& parent_channel,
                            uint32_t byte_offset ) const;
    /**
     * @brief CreateFreeBytesChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateFreeBytesChannel ( IChannel& parent_channel,
                                  uint32_t byte_offset ) const;
    /**
     * @brief CreateTableLayoutChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateTableLayoutChannel ( IChannel& parent_channel,
                                    uint32_t byte_offset ) const;
    /**
     * @brief CreateTableLengthChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateTableLengthChannel ( IChannel& parent_channel,
                                    uint32_t byte_offset ) const;
    /**
     * @brief CreateTableDataChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateTableDataChannel ( IChannel& parent_channel,
                                  uint32_t byte_offset ) const;
    /**
     * @brief CreateLockStateChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateLockStateChannel ( IChannel& parent_channel,
                                  uint32_t byte_offset ) const;
    /**
     * @brief CreateShutdownChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateShutdownChannel ( IChannel& parent_channel,
                                 uint32_t byte_offset ) const;
    /**
     * @brief CreateTransferTypeChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateTransferTypeChannel ( IChannel& parent_channel,
                                     uint32_t byte_offset ) const;
    /**
     * @brief CreateDirectionChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateDirectionChannel ( IChannel& parent_channel,
                                  uint32_t byte_offset ) const;
    /**
     * @brief CreateSourceChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     * @param nof_bits nof_bits.
     */
    void CreateSourceChannel ( IChannel& parent_channel,
                               uint32_t byte_offset, uint32_t nof_bits ) const;
    /**
     * @brief CreateDestinationChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     * @param nof_bits nof_bits.
     */
    void CreateDestinationChannel ( IChannel& parent_channel,
                                    uint32_t byte_offset, uint32_t nof_bits ) const;
    /**
     * @brief CreateSpecifiedBytesChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateSpecifiedBytesChannel ( IChannel& parent_channel,
                                       uint32_t byte_offset ) const;
    /**
     * @brief CreateReceivedBytesChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateReceivedBytesChannel ( IChannel& parent_channel,
                                      uint32_t byte_offset ) const;
    /**
     * @brief CreateDataLengthChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateDataLengthChannel ( IChannel& parent_channel,
                                   uint32_t byte_offset ) const;
    /**
     * @brief CreateDataBytesChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateDataBytesChannel ( IChannel& parent_channel,
                                  uint32_t byte_offset ) const;
    /**
     * @brief CreateTxFailedChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateTxFailedChannel ( IChannel& parent_channel,
                                 uint32_t byte_offset ) const;
    /**
     * @brief CreateCrcChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     * @param nof_bits nof_bits.
     */
    void CreateCrcChannel ( IChannel& parent_channel,
                            uint32_t byte_offset, uint32_t nof_bits ) const;
    /**
     * @brief CreateCompleteAckChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateCompleteAckChannel ( IChannel& parent_channel,
                                    uint32_t byte_offset ) const;
    /**
     * @brief CreatePreemptiveAckChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreatePreemptiveAckChannel ( IChannel& parent_channel,
                                      uint32_t byte_offset ) const;
    /**
     * @brief CreateTxAckChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreateTxAckChannel ( IChannel& parent_channel,
                              uint32_t byte_offset ) const;
    /**
     * @brief CreatePacketIndexChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreatePacketIndexChannel ( IChannel& parent_channel,
                                    uint32_t byte_offset ) const;
    /**
     * @brief CreatePacketTypeChannel.
     * @param parent_channel parent_channel.
     * @param byte_offset byte_offset.
     */
    void CreatePacketTypeChannel ( IChannel& parent_channel,
                                   uint32_t byte_offset ) const;
  };

}  // namespace mdf