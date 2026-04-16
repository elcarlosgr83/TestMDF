/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
/**
 * @file MdfDataGroup.h
 * @brief C++ wrapper for MDF data groups.
 *
 * `MdfLibrary::MdfDataGroup` provides access to data groups and their channel
 * groups inside an MDF file.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "MdfChannelGroup.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfDataGroup
   * @brief Wrapper for MDF data groups.
   *
   * A data group contains channel groups and metadata used during measurement.
   */
  class MdfDataGroup {
  private:
    mdf::IDataGroup* group;

  public:
    /**
     * @brief Wrap an existing data group handle.
     * @param group Low-level data group pointer.
     */
    MdfDataGroup ( mdf::IDataGroup* group ) : group ( group ) {
      if ( group == nullptr ) {
        throw std::runtime_error ( "MdfDataGroup Init failed" );
      }
    }

    /**
     * @brief Wrap a const data group handle.
     * @param group Low-level const data group pointer.
     */
    MdfDataGroup ( const mdf::IDataGroup* group )
      : MdfDataGroup ( const_cast<mdf::IDataGroup*> ( group ) ) {}

    ~MdfDataGroup () { group = nullptr; }

    /**
     * @brief Returns the underlying data group pointer.
     * @return Raw `mdf::IDataGroup` pointer.
     */
    mdf::IDataGroup* GetDataGroup () const { return group; }

    /**
     * @brief Returns the data group index.
     * @return Data group index.
     */
    int64_t GetIndex () const { return MdfDataGroupGetIndex ( group ); }

    /**
     * @brief Returns the data group description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfDataGroupGetDescription ( group, nullptr ) + 1, '\0' );
      str.resize ( MdfDataGroupGetDescription ( group, str.data () ) );
      return str;
    }

    /**
     * @brief Returns the record ID size.
     * @return Record ID size in bytes.
     */
    uint8_t GetRecordIdSize () const { return MdfDataGroupGetRecordIdSize ( group ); }

    /**
     * @brief Returns the metadata wrapper.
     * @return `MdfMetaData` object.
     */
    const MdfMetaData GetMetaData () const {
      return MdfDataGroupGetMetaData ( group );
    }

    /**
     * @brief Find a channel group by name.
     * @param name Group name.
     * @return `MdfChannelGroup` wrapper.
     */
    MdfChannelGroup GetChannelGroup ( const std::string name ) const {
      return MdfDataGroupGetChannelGroupByName ( group, name.c_str () );
    }

    /**
     * @brief Find a channel group by record ID.
     * @param record_id Record ID.
     * @return `MdfChannelGroup` wrapper.
     */
    MdfChannelGroup GetChannelGroup ( uint64_t record_id ) const {
      return MdfDataGroupGetChannelGroupByRecordId ( group, record_id );
    }

    /**
     * @brief Returns all channel groups in this data group.
     * @return Vector of channel group wrappers.
     */
    std::vector<MdfChannelGroup> GetChannelGroups () const {
      size_t count = MdfDataGroupGetChannelGroups ( group, nullptr );

      if ( count <= 0 )
        return {};

      auto pGroups = new mdf::IChannelGroup* [ count ];

      MdfDataGroupGetChannelGroups ( group, pGroups );

      std::vector<MdfChannelGroup> groups;

      for ( size_t i = 0; i < count; i++ )
      { groups.push_back ( MdfChannelGroup ( pGroups [ i ] ) ); }

      delete [] pGroups;
      return groups;
    }

    /**
     * @brief Returns whether the data group has been read.
     * @return `true` if the group is read.
     */
    bool IsRead () { return MdfDataGroupIsRead ( group ); }

    /**
     * @brief Create metadata for the data group.
     * @return `MdfMetaData` wrapper.
     */
    MdfMetaData CreateMetaData () { return MdfDataGroupCreateMetaData ( group ); }

    /**
     * @brief Create a new channel group.
     * @return `MdfChannelGroup` wrapper.
     */
    MdfChannelGroup CreateChannelGroup () {
      return MdfDataGroupCreateChannelGroup ( group );
    }

    /**
     * @brief Find the parent channel group of a channel.
     * @param channel Channel wrapper.
     * @return Parent `MdfChannelGroup` wrapper.
     */
    const MdfChannelGroup FindParentChannelGroup ( MdfChannel channel ) {
      return MdfDataGroupFindParentChannelGroup ( group, channel.GetChannel () );
    }
  };
}  // namespace MdfLibrary