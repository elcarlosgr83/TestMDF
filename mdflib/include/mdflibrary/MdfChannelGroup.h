/**
 * @file MdfChannelGroup.h
 * @brief Wrapper for MDF channel groups.
 *
 * A channel group collects multiple channels and exposes metadata such as
 * name, description, record ID, sample count and channel membership.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "MdfChannel.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfChannelGroup
   * @brief Channel group wrapper.
   */
  class MdfChannelGroup {
  private:
    mdf::IChannelGroup* group;

  public:
    /**
     * @brief Wrap an existing channel group handle.
     * @param group Low-level channel group pointer.
     */
    MdfChannelGroup ( mdf::IChannelGroup* group ) : group ( group ) {
      if ( group == nullptr )
      { throw std::runtime_error ( "MdfChannelGroup Init failed" ); }
    }
    /**
     * @brief Wrap a const channel group handle.
     * @param group Low-level const channel group pointer.
     */
    MdfChannelGroup ( const mdf::IChannelGroup* group )
      : MdfChannelGroup ( const_cast<mdf::IChannelGroup*> ( group ) ) {}
    ~MdfChannelGroup () { group = nullptr; }

    /**
     * @brief Returns the underlying channel group pointer.
     * @return Raw `mdf::IChannelGroup` pointer.
     */
    mdf::IChannelGroup* GetChannelGroup () const { return group; }

    /**
     * @brief Returns the channel group index.
     * @return Group index.
     */
    int64_t GetIndex () const { return MdfChannelGroupGetIndex ( group ); }

    /**
     * @brief Returns the group record ID.
     * @return Record ID.
     */
    uint64_t GetRecordId () const { return MdfChannelGroupGetRecordId ( group ); }

    /**
     * @brief Returns the group name.
     * @return Name string.
     */
    std::string GetName () const {
      std::string str ( MdfChannelGroupGetName ( group, nullptr ) + 1, '\0' );
      str.resize ( MdfChannelGroupGetName ( group, str.data () ) );
      return str;
    }

    /**
     * @brief Set the group name.
     * @param name Name string.
     */
    void SetName ( const char* name ) { MdfChannelGroupSetName ( group, name ); }

    /**
     * @brief Returns the group description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfChannelGroupGetDescription ( group, nullptr ) + 1, '\0' );
      str.resize ( MdfChannelGroupGetDescription ( group, str.data () ) );
      return str;
    }

    /**
     * @brief Set the group description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) {
      MdfChannelGroupSetDescription ( group, desc );
    }

    /**
     * @brief Returns the number of samples expected in the group.
     * @return Sample count.
     */
    uint64_t GetNofSamples () const { return MdfChannelGroupGetNofSamples ( group ); }

    /**
     * @brief Set the expected number of samples.
     * @param samples Sample count.
     */
    void SetNofSamples ( uint64_t samples ) {
      MdfChannelGroupSetNofSamples ( group, samples );
    }

    /**
     * @brief Returns the flags bitmask.
     * @return Flags value.
     */
    uint16_t GetFlags () const { return MdfChannelGroupGetFlags ( group ); }

    /**
     * @brief Set the flags bitmask.
     * @param flags Flags value.
     */
    void SetFlags ( uint16_t flags ) { MdfChannelGroupSetFlags ( group, flags ); }

    /**
     * @brief Returns the path separator for the group.
     * @return Path separator character.
     */
    wchar_t GetPathSeparator () const {
      return MdfChannelGroupGetPathSeparator ( group );
    }

    /**
     * @brief Set the path separator for the group.
     * @param sep Separator character.
     */
    void SetPathSeparator ( wchar_t sep ) {
      MdfChannelGroupSetPathSeparator ( group, sep );
    }

    /**
     * @brief Returns the group metadata.
     * @return `MdfMetaData` object.
     */
    const MdfMetaData GetMetaData () const {
      return MdfChannelGroupGetMetaData ( group );
    }

    /**
     * @brief Returns the list of channels in this group.
     * @return Channel wrappers.
     */
    std::vector<MdfChannel> GetChannels () const {
      size_t count = MdfChannelGroupGetChannels ( group, nullptr );

      if ( count <= 0 )
        return {};

      auto pChannels = new mdf::IChannel* [ count ];

      MdfChannelGroupGetChannels ( group, pChannels );

      std::vector<MdfChannel> channels;

      channels.reserve ( count );

      for ( size_t i = 0; i < count; i++ ) {
        channels.push_back ( pChannels [ i ] );
      }

      delete [] pChannels;
      return channels;
    }

    /**
     * @brief Returns source information associated with the group.
     * @return `MdfSourceInformation` wrapper.
     */
    const MdfSourceInformation GetSourceInformation () const {
      return MdfChannelGroupGetSourceInformation ( group );
    }

    /**
     * @brief Returns an X-channel from the group.
     * @param ref_channel Reference channel wrapper.
     * @return `MdfChannel` wrapper for X-channel.
     */
    const MdfChannel GetXChannel ( MdfChannel ref_channel ) {
      return MdfChannelGroupGetXChannel ( group, ref_channel.GetChannel () );
    }

    /**
     * @brief Create group metadata.
     * @return New `MdfMetaData` wrapper.
     */
    MdfMetaData CreateMetaData () { return MdfChannelGroupCreateMetaData ( group ); }

    /**
     * @brief Create a channel within this group.
     * @return New `MdfChannel` wrapper.
     */
    MdfChannel CreateChannel () { return MdfChannelGroupCreateChannel ( group ); }

    /**
     * @brief Create source information for this group.
     * @return New `MdfSourceInformation` wrapper.
     */
    MdfSourceInformation CreateSourceInformation () {
      return MdfChannelGroupCreateSourceInformation ( group );
    }
  };
}  // namespace MdfLibrary