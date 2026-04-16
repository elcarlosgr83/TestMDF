/**
 * @file CanMessage.h
 * @brief Wrapper for CAN messages in the MdfLibrary API.
 *
 * A CAN message contains standard CAN fields such as the message identifier,
 * payload, DLC, bus settings and protocol-specific flags. This wrapper makes
 * it easy to read and write CAN message values from C++ code while keeping a
 * reference to the underlying low-level `mdf::CanMessage` object.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <vector>

#include "MdfExport.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class CanMessage
   * @brief CAN message wrapper.
   *
   * Provides access to CAN message properties and payload data. When default
   * constructed, a new low-level message is created and managed by this object.
   */
  class CanMessage {
  private:
    bool isNew = false;
    mdf::CanMessage* can;

  public:
    /**
     * @brief Wrap an existing CAN message handle.
     * @param can Existing low-level CAN message pointer.
     */
    CanMessage ( mdf::CanMessage* can ) : can ( can ) {
      if ( can == nullptr ) {
        throw std::runtime_error ( "CanMessage Init failed" );
      }
    }

    /**
     * @brief Create a new CAN message.
     */
    CanMessage () : CanMessage ( CanMessageInit () ) { isNew = true; };

    /**
     * @brief Destroy the CAN message wrapper.
     *
     * Releases the underlying message only if it was created by this wrapper.
     */
    ~CanMessage () {
      if ( isNew ) {
        CanMessageUnInit ( can );
      }

      can = nullptr;
    };

    CanMessage ( const CanMessage& ) = delete;

    /**
     * @brief Move constructor.
     */
    CanMessage ( CanMessage&& can ) {
      if ( isNew ) {
        CanMessageUnInit ( this->can );
      }

      this->isNew = can.isNew;
      this->can = can.can;
      can.isNew = false;
      can.can = nullptr;
    }

    /**
     * @brief Returns the underlying low-level CAN message pointer.
     * @return Raw `mdf::CanMessage` pointer.
     */
    mdf::CanMessage* GetCanMessage () const { return can; }

    /**
     * @brief Returns the CAN message identifier.
     * @return Identifier of the CAN message.
     */
    uint32_t GetMessageId () const { return CanMessageGetMessageId ( can ); };

    /**
     * @brief Set the CAN message identifier.
     * @param msgId Message identifier to assign.
     */
    void SetMessageId ( uint32_t msgId ) { CanMessageSetMessageId ( can, msgId ); };

    /**
     * @brief Returns the raw CAN bus identifier.
     * @return CAN bus ID.
     */
    uint32_t GetCanId () const { return CanMessageGetCanId ( can ); };

    /**
     * @brief Enable or disable extended CAN identifier mode.
     * @param extendedId `true` to use extended ID format.
     */
    void SetExtendedId ( bool extendedId ) {
      CanMessageSetExtendedId ( can, extendedId );
    };

    /**
     * @brief Returns whether extended CAN identifiers are used.
     * @return `true` when extended ID is enabled.
     */
    bool GetExtendedId () const { return CanMessageGetExtendedId ( can ); };

    /**
     * @brief Returns the data length code (DLC).
     * @return Number of payload bytes.
     */
    uint8_t GetDlc () const { return CanMessageGetDlc ( can ); };

    /**
     * @brief Set the data length code.
     * @param dlc Number of payload bytes.
     */
    void SetDlc ( uint8_t dlc ) { CanMessageSetDlc ( can, dlc ); };

    /**
     * @brief Returns the current payload length.
     * @return Payload length in bytes.
     */
    uint32_t GetDataLength () const { return CanMessageGetDataLength ( can ); };

    /**
     * @brief Set the expected payload length.
     * @param dataLength Payload length in bytes.
     */
    void SetDataLength ( uint32_t dataLength ) {
      CanMessageSetDataLength ( can, dataLength );
    };

    /**
     * @brief Get the current payload bytes.
     * @return Payload bytes as a vector.
     */
    std::vector<uint8_t> GetDataBytes () const {
      size_t count = CanMessageGetDataBytes ( can, nullptr );

      if ( count <= 0 )
        return {};

      auto dataList = std::vector<uint8_t> ( count );

      CanMessageGetDataBytes ( can, dataList.data () );

      return dataList;
    };

    /**
     * @brief Set payload bytes from a vector.
     * @param dataList Payload bytes to store.
     */
    void SetDataBytes ( const std::vector<uint8_t>& dataList ) {
      CanMessageSetDataBytes ( can, dataList.data (), dataList.size () );
    };

    /**
     * @brief Set payload bytes from a raw byte array.
     * @param dataList Pointer to the payload buffer.
     * @param size Number of bytes in the buffer.
     */
    void SetDataBytes ( const uint8_t* dataList, const size_t size ) {
      CanMessageSetDataBytes ( can, dataList, size );
    };

    /**
     * @brief Returns the data index associated with the message.
     * @return Data index.
     */
    uint64_t GetDataIndex () const { return CanMessageGetDataIndex ( can ); };

    /**
     * @brief Set the data index for the message.
     * @param index Data index value.
     */
    void SetDataIndex ( const uint64_t index ) {
      CanMessageSetDataIndex ( can, index );
    };

    /**
     * @brief Returns the transmit direction flag.
     * @return `true` if the message is a transmit message.
     */
    bool GetDir () const { return CanMessageGetDir ( can ); };

    /**
     * @brief Set the transmit direction flag.
     * @param transmit `true` for message transmission direction.
     */
    void SetDir ( const bool transmit ) { CanMessageSetDir ( can, transmit ); };

    /**
     * @brief Returns the SRR flag state.
     * @return `true` if Substitute Remote Request is set.
     */
    bool GetSrr () const { return CanMessageGetSrr ( can ); };

    /**
     * @brief Set the SRR flag.
     * @param srr New SRR flag value.
     */
    void SetSrr ( const bool srr ) { CanMessageSetSrr ( can, srr ); };

    /**
     * @brief Returns the EDL flag state.
     * @return `true` if enhanced data length is enabled.
     */
    bool GetEdl () const { return CanMessageGetEdl ( can ); };

    /**
     * @brief Set the EDL flag.
     * @param edl New EDL flag value.
     */
    void SetEdl ( const bool edl ) { CanMessageSetEdl ( can, edl ); };

    /**
     * @brief Returns the BRS flag state.
     * @return `true` if bit rate switching is enabled.
     */
    bool GetBrs () const { return CanMessageGetBrs ( can ); };

    /**
     * @brief Set the BRS flag.
     * @param brs New BRS flag value.
     */
    void SetBrs ( const bool brs ) { CanMessageSetBrs ( can, brs ); };

    /**
     * @brief Returns the ESI flag state.
     * @return `true` if error state indicator is set.
     */
    bool GetEsi () const { return CanMessageGetEsi ( can ); };

    /**
     * @brief Set the ESI flag.
     * @param esi New ESI value.
     */
    void SetEsi ( const bool esi ) { CanMessageSetEsi ( can, esi ); };

    /**
     * @brief Returns the RTR flag state.
     * @return `true` when remote transmission request is enabled.
     */
    bool GetRtr () const { return CanMessageGetRtr ( can ); };

    /**
     * @brief Set the RTR flag.
     * @param rtr New RTR flag value.
     */
    void SetRtr ( const bool rtr ) { CanMessageSetRtr ( can, rtr ); };

    /**
     * @brief Returns the wake-up flag state.
     * @return `true` if wake-up is enabled.
     */
    bool GetWakeUp () const { return CanMessageGetWakeUp ( can ); };

    /**
     * @brief Set the wake-up flag.
     * @param wakeUp New wake-up flag value.
     */
    void SetWakeUp ( const bool wakeUp ) { CanMessageSetWakeUp ( can, wakeUp ); };

    /**
     * @brief Returns the single-wire mode flag.
     * @return `true` if single-wire mode is enabled.
     */
    bool GetSingleWire () const { return CanMessageGetSingleWire ( can ); };

    /**
     * @brief Set the single-wire mode flag.
     * @param singleWire New single-wire flag value.
     */
    void SetSingleWire ( const bool singleWire ) {
      CanMessageSetSingleWire ( can, singleWire );
    };

    /**
     * @brief Returns the bus channel number.
     * @return Bus channel value.
     */
    uint8_t GetBusChannel () const { return CanMessageGetBusChannel ( can ); };

    /**
     * @brief Set the bus channel number.
     * @param channel Bus channel index.
     */
    void SetBusChannel ( const uint8_t channel ) {
      CanMessageSetBusChannel ( can, channel );
    };

    /**
     * @brief Gets the bit position of the message.
     * @return Bit position.
     */
    uint8_t GetBitPosition () const { return CanMessageGetBitPosition ( can ); };

    /**
     * @brief Set the bit position.
     * @param position Bit position to assign.
     */
    void SetBitPosition ( const uint8_t position ) {
      CanMessageSetBitPosition ( can, position );
    };

    /**
     * @brief Returns the CAN error type.
     * @return Error type.
     */
    CanErrorType GetErrorType () const { return CanMessageGetErrorType ( can ); };

    /**
     * @brief Set the CAN error type.
     * @param type Error type to assign.
     */
    void SetErrorType ( const CanErrorType type ) {
      CanMessageSetErrorType ( can, type );
    };

    /**
     * @brief Reset the CAN message contents to a default state.
     */
    void Reset ();
  };
}  // namespace MdfLibrary