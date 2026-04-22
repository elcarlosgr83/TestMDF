/**
 * @file LinMessage.h
 * @brief Wrapper for LIN messages in the MdfLibrary API.
 *
 * The `LinMessage` wrapper exposes LIN-specific message fields such as the
 * LIN identifier, checksum, start-of-frame timestamp, baudrates and payload.
 * It encapsulates the underlying `mdf::LinMessage` object and provides a
 * safe C++ API.
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
   * @class LinMessage
   * @brief LIN message wrapper.
   */
  class LinMessage {
  private:
    bool isNew = false;
    mdf::LinMessage* lin;

  public:
    /**
     * @brief Wrap an existing LIN message handle.
     * @param lin Existing low-level LIN message pointer.
     */
    LinMessage ( mdf::LinMessage* lin ) : lin ( lin ) {
      if ( lin == nullptr ) {
        throw std::runtime_error ( "LinMessage Init failed" );
      }
    }

    /**
     * @brief Create a new LIN message.
     */
    LinMessage () : LinMessage ( LinMessageInit () ) { isNew = true; };

    /**
     * @brief Destroy the LIN message wrapper.
     */
    ~LinMessage () {
      if ( isNew ) {
        LinMessageUnInit ( lin );
      }

      lin = nullptr;
    };

    LinMessage ( const LinMessage& ) = delete;

    /**
     * @brief Move constructor.
     */
    LinMessage ( LinMessage&& other ) {
      if ( isNew ) {
        LinMessageUnInit ( this->lin );
      }

      this->isNew = other.isNew;
      this->lin = other.lin;
      other.isNew = false;
      other.lin = nullptr;
    }

    /**
     * @brief Returns the raw LIN message handle.
     * @return Raw `mdf::LinMessage` pointer.
     */
    mdf::LinMessage* GetLinMessage () const { return lin; }

    /**
     * @brief Set the LIN message identifier.
     * @param id LIN identifier.
     */
    void SetLinId ( uint8_t id ) { LinMessageSetLinId ( lin, id ); };

    /**
     * @brief Returns the LIN identifier.
     * @return LIN ID.
     */
    uint8_t GetLinId () const { return LinMessageGetLinId ( lin ); };

    /**
     * @brief Set the bus channel for the LIN message.
     * @param channel Bus channel index.
     */
    void SetBusChannel ( uint8_t channel ) {
      LinMessageSetBusChannel ( lin, channel );
    };

    /**
     * @brief Returns the bus channel number.
     * @return Bus channel index.
     */
    uint8_t GetBusChannel () const { return LinMessageGetBusChannel ( lin ); };

    /**
     * @brief Set the message direction.
     * @param transmit `true` for transmit messages.
     */
    void SetDir ( bool transmit ) { LinMessageSetDir ( lin, transmit ); };

    /**
     * @brief Returns the message direction.
     * @return `true` if transmit direction.
     */
    bool GetDir () const { return LinMessageGetDir ( lin ); };

    /**
     * @brief Set the data length for the LIN message.
     * @param len Payload length in bytes.
     */
    void SetDataLength ( uint8_t len ) { LinMessageSetDataLength ( lin, len ); };

    /**
     * @brief Returns the payload length.
     * @return Number of data bytes.
     */
    uint8_t GetDataLength () const { return LinMessageGetDataLength ( lin ); };

    /**
     * @brief Set the received data byte count.
     * @param len Received byte count.
     */
    void SetReceivedDataByteCount ( uint8_t len ) {
      LinMessageSetReceivedDataByteCount ( lin, len );
    };

    /**
     * @brief Returns the received data byte count.
     * @return Received byte count.
     */
    uint8_t GetReceivedDataByteCount () const {
      return LinMessageGetReceivedDataByteCount ( lin );
    };

    /**
     * @brief Retrieve the raw payload bytes.
     * @return Payload bytes as a vector.
     */
    std::vector<uint8_t> GetDataBytes () const {
      size_t count = LinMessageGetDataBytes ( lin, nullptr );

      if ( count <= 0 )
        return {};

      auto data = std::vector<uint8_t> ( count );

      LinMessageGetDataBytes ( lin, data.data () );

      return data;
    };

    /**
     * @brief Set the payload bytes from a vector.
     * @param data Payload bytes.
     */
    void SetDataBytes ( const std::vector<uint8_t>& data ) {
      LinMessageSetDataBytes ( lin, data.data (), data.size () );
    };

    /**
     * @brief Set the payload bytes from a raw buffer.
     * @param data Pointer to payload data.
     * @param size Number of bytes.
     */
    void SetDataBytes ( const uint8_t* data, const size_t size ) {
      LinMessageSetDataBytes ( lin, data, size );
    };

    /**
     * @brief Set the CRC checksum.
     * @param crc Checksum value.
     */
    void SetChecksum ( uint8_t crc ) { LinMessageSetChecksum ( lin, crc ); };

    /**
     * @brief Returns the CRC checksum.
     * @return Checksum value.
     */
    uint8_t GetChecksum () const { return LinMessageGetChecksum ( lin ); };

    /**
     * @brief Set the checksum model.
     * @param model Checksum model identifier.
     */
    void SetChecksumModel ( int model ) { LinMessageSetChecksumModel ( lin, model ); };

    /**
     * @brief Returns the checksum model.
     * @return Checksum model identifier.
     */
    int GetChecksumModel () const { return LinMessageGetChecksumModel ( lin ); };

    /**
     * @brief Set the start-of-frame timestamp.
     * @param ns1970 Timestamp in nanoseconds since 1970.
     */
    void SetStartOfFrame ( uint64_t ns1970 ) {
      LinMessageSetStartOfFrame ( lin, ns1970 );
    };

    /**
     * @brief Returns the start-of-frame timestamp.
     * @return Timestamp in nanoseconds since 1970.
     */
    uint64_t GetStartOfFrame () const { return LinMessageGetStartOfFrame ( lin ); };

    /**
     * @brief Set the LIN baudrate.
     * @param baud Baudrate value.
     */
    void SetBaudrate ( float baud ) { LinMessageSetBaudrate ( lin, baud ); };

    /**
     * @brief Returns the LIN baudrate.
     * @return Baudrate value.
     */
    float GetBaudrate () const { return LinMessageGetBaudrate ( lin ); };

    /**
     * @brief Set the response baudrate.
     * @param baud Response baudrate.
     */
    void SetResponseBaudrate ( float baud ) {
      LinMessageSetResponseBaudrate ( lin, baud );
    };

    /**
     * @brief Returns the response baudrate.
     * @return Response baudrate.
     */
    float GetResponseBaudrate () const {
      return LinMessageGetResponseBaudrate ( lin );
    };

    /**
     * @brief Set the LIN break length.
     * @param len Break length in nanoseconds.
     */
    void SetBreakLength ( uint32_t len ) { LinMessageSetBreakLength ( lin, len ); };

    /**
     * @brief Returns the LIN break length.
     * @return Break length in nanoseconds.
     */
    uint32_t GetBreakLength () const { return LinMessageGetBreakLength ( lin ); };
  };
}  // namespace MdfLibrary
