/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
/**
 * @file MdfChannel.h
 * @brief C++ wrapper for a single MDF channel.
 *
 * `MdfLibrary::MdfChannel` exposes channel metadata and conversion access for
 * MDF files.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "MdfChannelConversion.h"
#include "MdfSourceInformation.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfChannel
   * @brief Wrapper for a single MDF channel.
   *
   * Provides access to channel metadata, type and conversion information.
   */
  class MdfChannel {
  private:
    mdf::IChannel* channel;

  public:
    /**
     * @brief Wrap an existing channel handle.
     * @param channel Low-level channel pointer.
     */
    MdfChannel ( mdf::IChannel* channel ) : channel ( channel ) {
      if ( channel == nullptr ) {
        throw std::runtime_error ( "MdfChannel Init failed" );
      }
    }

    /**
     * @brief Wrap a const channel handle.
     * @param channel Low-level const channel pointer.
     */
    MdfChannel ( const mdf::IChannel* channel )
      : MdfChannel ( const_cast<mdf::IChannel*> ( channel ) ) {}

    ~MdfChannel () { channel = nullptr; }

    /**
     * @brief Returns the underlying channel pointer.
     * @return Raw `mdf::IChannel` pointer.
     */
    mdf::IChannel* GetChannel () const { return channel; }

    /**
     * @brief Returns the channel index.
     * @return Channel index.
     */
    int64_t GetIndex () const { return MdfChannelGetIndex ( channel ); }

    /**
     * @brief Returns the channel name.
     * @return Name string.
     */
    std::string GetName () const {
      std::string str ( MdfChannelGetName ( channel, nullptr ) + 1, '\0' );
      str.resize ( MdfChannelGetName ( channel, str.data () ) );
      return str;
    }

    /**
     * @brief Set the channel name.
     * @param name Channel name.
     */
    void SetName ( const char* name ) { MdfChannelSetName ( channel, name ); }

    /**
     * @brief Returns the display name.
     * @return Display name string.
     */
    std::string GetDisplayName () const {
      std::string str ( MdfChannelGetDisplayName ( channel, nullptr ) + 1, '\0' );
      str.resize ( MdfChannelGetDisplayName ( channel, str.data () ) );
      return str;
    }

    /**
     * @brief Set the display name.
     * @param name Display name.
     */
    void SetDisplayName ( const char* name ) {
      MdfChannelSetDisplayName ( channel, name );
    }

    /**
     * @brief Returns the channel description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfChannelGetDescription ( channel, nullptr ) + 1, '\0' );
      str.resize ( MdfChannelGetDescription ( channel, str.data () ) );
      return str;
    }

    /**
     * @brief Set the channel description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) {
      MdfChannelSetDescription ( channel, desc );
    }

    /**
     * @brief Returns whether a unit is used.
     * @return `true` when a unit is used.
     */
    bool IsUnitUsed () { return MdfChannelIsUnitUsed ( channel ); }

    /**
     * @brief Returns the channel unit.
     * @return Unit string.
     */
    std::string GetUnit () const {
      std::string str ( MdfChannelGetUnit ( channel, nullptr ) + 1, '\0' );
      str.resize ( MdfChannelGetUnit ( channel, str.data () ) );
      return str;
    }

    /**
     * @brief Set the channel unit.
     * @param unit Unit string.
     */
    void SetUnit ( const char* unit ) { MdfChannelSetUnit ( channel, unit ); }

    /**
     * @brief Returns the channel type.
     * @return Channel type enum.
     */
    ChannelType GetType () const { return MdfChannelGetType ( channel ); }

    /**
     * @brief Set the channel type.
     * @param type Channel type.
     */
    void SetType ( ChannelType type ) { MdfChannelSetType ( channel, type ); }

    /**
     * @brief Returns the channel synchronization type.
     * @return Sync type enum.
     */
    ChannelSyncType GetSync () const { return MdfChannelGetSync ( channel ); }

    /**
     * @brief Set the channel synchronization type.
     * @param type Sync type.
     */
    void SetSync ( ChannelSyncType type ) { MdfChannelSetSync ( channel, type ); }

    /**
     * @brief Returns the data type.
     * @return Data type enum.
     */
    ChannelDataType GetDataType () const { return MdfChannelGetDataType ( channel ); }

    /**
     * @brief Set the data type.
     * @param type Data type.
     */
    void SetDataType ( ChannelDataType type ) {
      MdfChannelSetDataType ( channel, type );
    }

    /**
     * @brief Returns the channel flags.
     * @return Flags bitmask.
     */
    uint32_t GetFlags () const { return MdfChannelGetFlags ( channel ); }

    /**
     * @brief Set the channel flags.
     * @param flags Flags bitmask.
     */
    void SetFlags ( uint32_t flags ) { MdfChannelSetFlags ( channel, flags ); }

    /**
     * @brief Returns the data bytes count.
     * @return Data byte count.
     */
    uint64_t GetDataBytes () const { return MdfChannelGetDataBytes ( channel ); }

    /**
     * @brief Set the data bytes count.
     * @param bytes Number of data bytes.
     */
    void SetDataBytes ( uint64_t bytes ) { MdfChannelSetDataBytes ( channel, bytes ); }

    /**
     * @brief Returns whether precision is used.
     * @return `true` when precision is used.
     */
    bool IsPrecisionUsed () { return MdfChannelIsPrecisionUsed ( channel ); }

    /**
     * @brief Returns the precision value.
     * @return Precision.
     */
    uint8_t GetPrecision () const { return MdfChannelGetPrecision ( channel ); }

    /**
     * @brief Returns whether range is used.
     * @return `true` when range is used.
     */
    bool IsRangeUsed () { return MdfChannelIsRangeUsed ( channel ); }

    /**
     * @brief Returns the minimum range value.
     * @return Minimum range.
     */
    double GetRangeMin () const { return MdfChannelGetRangeMin ( channel ); }

    /**
     * @brief Returns the maximum range value.
     * @return Maximum range.
     */
    double GetRangeMax () const { return MdfChannelGetRangeMax ( channel ); }

    /**
     * @brief Set the valid range for the channel.
     * @param min Minimum value.
     * @param max Maximum value.
     */
    void SetRange ( double min, double max ) {
      MdfChannelSetRange ( channel, min, max );
    }

    /**
     * @brief Returns whether limits are used.
     * @return `true` when limits are used.
     */
    bool IsLimitUsed () { return MdfChannelIsLimitUsed ( channel ); }

    /**
     * @brief Returns the minimum limit value.
     * @return Minimum limit.
     */
    double GetLimitMin () const { return MdfChannelGetLimitMin ( channel ); }

    /**
     * @brief Returns the maximum limit value.
     * @return Maximum limit.
     */
    double GetLimitMax () const { return MdfChannelGetLimitMax ( channel ); }

    /**
     * @brief Set the channel limits.
     * @param min Minimum limit.
     * @param max Maximum limit.
     */
    void SetLimit ( double min, double max ) {
      MdfChannelSetLimit ( channel, min, max );
    }

    /**
     * @brief Returns whether extended limits are used.
     * @return `true` when extended limits are used.
     */
    bool IsExtLimitUsed () { return MdfChannelIsExtLimitUsed ( channel ); }

    /**
     * @brief Returns the minimum extended limit.
     * @return Minimum extended limit.
     */
    double GetExtLimitMin () const { return MdfChannelGetExtLimitMin ( channel ); }

    /**
     * @brief Returns the maximum extended limit.
     * @return Maximum extended limit.
     */
    double GetExtLimitMax () const { return MdfChannelGetExtLimitMax ( channel ); }

    /**
     * @brief Set extended channel limits.
     * @param min Minimum extended limit.
     * @param max Maximum extended limit.
     */
    void SetExtLimit ( double min, double max ) {
      MdfChannelSetExtLimit ( channel, min, max );
    }

    /**
     * @brief Returns the sampling rate.
     * @return Sampling rate.
     */
    double GetSamplingRate () const { return MdfChannelGetSamplingRate ( channel ); }

    /**
     * @brief Returns the VLSD record ID.
     * @return Record ID.
     */
    uint64_t GetVlsdRecordId () const {
      return MdfChannelGetVlsdRecordId ( channel );
    }

    /**
     * @brief Set the VLSD record ID.
     * @param record_id Record identifier.
     */
    void SetVlsdRecordId ( uint64_t record_id ) {
      MdfChannelSetVlsdRecordId ( channel, record_id );
    }

    /**
     * @brief Returns the bit count.
     * @return Bit count.
     */
    uint32_t GetBitCount () const { return MdfChannelGetBitCount ( channel ); }

    /**
     * @brief Set the bit count.
     * @param bits Bit count.
     */
    void SetBitCount ( uint32_t bits ) { MdfChannelSetBitCount ( channel, bits ); }

    /**
     * @brief Returns the bit offset.
     * @return Bit offset.
     */
    uint16_t GetBitOffset () const { return MdfChannelGetBitOffset ( channel ); }

    /**
     * @brief Set the bit offset.
     * @param bits Bit offset.
     */
    void SetBitOffset ( uint16_t bits ) { MdfChannelSetBitOffset ( channel, bits ); }

    /**
     * @brief Returns the metadata wrapper.
     * @return `MdfMetaData` object.
     */
    const MdfMetaData GetMetaData () const {
      return MdfChannelGetMetaData ( channel );
    }

    /**
     * @brief Returns the source information wrapper.
     * @return `MdfSourceInformation` object.
     */
    const MdfSourceInformation GetSourceInformation () const {
      return MdfChannelGetSourceInformation ( channel );
    }

    /**
     * @brief Returns the channel conversion wrapper.
     * @return `MdfChannelConversion` object.
     */
    const MdfChannelConversion GetChannelConversion () const {
      return MdfChannelGetChannelConversion ( channel );
    }

    /**
     * @brief Returns the channel compositions.
     * @return Vector of composed channel wrappers.
     */
    std::vector<MdfChannel> GetChannelCompositions () {
      size_t count = MdfChannelGetChannelCompositions ( channel, nullptr );

      if ( count <= 0 )
        return {};

      auto pChannels = new mdf::IChannel* [ count ];

      MdfChannelGetChannelCompositions ( channel, pChannels );

      std::vector<MdfChannel> channelss;

      channelss.reserve ( count );

      for ( size_t i = 0; i < count; i++ ) {
        channelss.emplace_back ( pChannels [ i ] );
      }

      delete [] pChannels;
      return channelss;
    }

    /**
     * @brief Create metadata for the channel.
     * @return `MdfMetaData` wrapper.
     */
    MdfMetaData CreateMetaData () { return MdfChannelCreateMetaData ( channel ); }

    /**
     * @brief Create source information for the channel.
     * @return `MdfSourceInformation` wrapper.
     */
    MdfSourceInformation CreateSourceInformation () {
      return MdfChannelCreateSourceInformation ( channel );
    }

    /**
     * @brief Create channel conversion for the channel.
     * @return `MdfChannelConversion` wrapper.
     */
    MdfChannelConversion CreateChannelConversion () {
      return MdfChannelCreateChannelConversion ( channel );
    }

    /**
     * @brief Create a channel composition.
     * @return `MdfChannel` wrapper.
     */
    MdfChannel CreateChannelComposition () {
      return MdfChannelCreateChannelComposition ( channel );
    }

    /**
     * @brief Set a signed channel value.
     * @param value Signed integer value.
     * @param valid Whether the value is valid.
     */
    void SetChannelValue ( const int64_t value, bool valid = true ) {
      MdfChannelSetChannelValueAsSigned ( channel, value, valid );
    }

    /**
     * @brief Set an unsigned channel value.
     * @param value Unsigned integer value.
     * @param valid Whether the value is valid.
     */
    void SetChannelValue ( const uint64_t value, bool valid = true ) {
      MdfChannelSetChannelValueAsUnSigned ( channel, value, valid );
    }

    /**
     * @brief Set a floating point channel value.
     * @param value Floating-point value.
     * @param valid Whether the value is valid.
     */
    void SetChannelValue ( const double value, bool valid = true ) {
      MdfChannelSetChannelValueAsFloat ( channel, value, valid );
    }

    /**
     * @brief Set a string channel value.
     * @param value String value.
     * @param valid Whether the value is valid.
     */
    void SetChannelValue ( const char* value, bool valid = true ) {
      MdfChannelSetChannelValueAsString ( channel, value, valid );
    }

    /**
     * @brief Set an array-valued channel value.
     * @param value Array pointer.
     * @param size Number of array bytes.
     * @param valid Whether the value is valid.
     */
    void SetChannelValue ( const uint8_t* value, size_t size, bool valid = true ) {
      MdfChannelSetChannelValueAsArray ( channel, value, size, valid );
    }
  };
}  // namespace MdfLibrary
