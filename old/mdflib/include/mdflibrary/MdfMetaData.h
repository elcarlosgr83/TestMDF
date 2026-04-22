/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "MdfETag.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @file MdfMetaData.h
   * @brief Wrapper for MDF metadata properties.
   *
   * The `MdfMetaData` wrapper exposes metadata properties and allows reading and
   * writing metadata as strings, floats, and property lists.
   *
   * @ingroup mdflibrary
   */
  class MdfMetaData {
  private:
    mdf::IMetaData* metaData;

  public:
    /**
     * @brief Wrap an existing metadata handle.
     * @param metaData Low-level metadata pointer.
     */
    MdfMetaData ( mdf::IMetaData* metaData ) : metaData ( metaData ) {
      if ( metaData == nullptr ) {
        throw std::runtime_error ( "MdfMetaData Init failed" );
      }
    }

    /**
     * @brief Wrap a const metadata handle.
     * @param metaData Low-level const metadata pointer.
     */
    MdfMetaData ( const mdf::IMetaData* metaData )
      : MdfMetaData ( const_cast<mdf::IMetaData*> ( metaData ) ) {}

    ~MdfMetaData () { metaData = nullptr; }

    /**
     * @brief Get a property string by key.
     * @param index Property key.
     * @return Value string.
     */
    std::string GetPropertyAsString ( const char* index ) {
      std::string str ( MdfMetaDataGetPropertyAsString ( metaData, index,
                        nullptr ) + 1, '\0' );
      str.resize ( MdfMetaDataGetPropertyAsString ( metaData, index, str.data () ) );
      return str;
    }

    /**
     * @brief Set a property string.
     * @param index Property key.
     * @param prop Property value.
     */
    void SetPropertyAsString ( const char* index, const char* prop ) {
      MdfMetaDataSetPropertyAsString ( metaData, index, prop );
    }

    /**
     * @brief Get a property value as float.
     * @param index Property key.
     * @return Floating point value.
     */
    double GetPropertyAsFloat ( const char* index ) {
      return MdfMetaDataGetPropertyAsFloat ( metaData, index );
    }

    /**
     * @brief Set a property value as float.
     * @param index Property key.
     * @param prop Floating point value.
     */
    void SetPropertyAsFloat ( const char* index, double prop ) {
      MdfMetaDataSetPropertyAsFloat ( metaData, index, prop );
    }

    /**
     * @brief Returns all metadata properties.
     * @return Vector of `MdfETag` wrappers.
     */
    std::vector<MdfETag> GetProperties () const {
      size_t count = MdfMetaDataGetProperties ( metaData, nullptr );

      if ( count <= 0 )
        return {};

      auto pTags = new mdf::ETag* [ count ];

      MdfMetaDataGetProperties ( metaData, pTags );

      std::vector<MdfETag> tags;

      for ( size_t i = 0; i < count; i++ ) {
        tags.push_back ( pTags [ i ] );
      }

      delete [] pTags;
      return tags;
    }

    /**
     * @brief Returns common metadata properties.
     * @return Vector of `MdfETag` wrappers.
     */
    std::vector<MdfETag> GetCommonProperties () const {
      size_t count = MdfMetaDataGetCommonProperties ( metaData, nullptr );

      if ( count <= 0 )
        return {};

      auto pTags = new mdf::ETag* [ count ];

      MdfMetaDataGetCommonProperties ( metaData, pTags );

      std::vector<MdfETag> tags;

      for ( size_t i = 0; i < count; i++ ) {
        tags.push_back ( pTags [ i ] );
      }

      delete [] pTags;
      return tags;
    }

    /**
     * @brief Set a list of common property tags.
     * @param pProperty Property tag wrappers.
     * @param count Number of tags.
     */
    void SetCommonProperties ( const std::vector<MdfETag> pProperty,
                               size_t count ) {
      auto pTags = new const mdf::ETag* [ count ];

      for ( size_t i = 0; i < count; i++ ) {
        pTags [ i ] = pProperty [ i ].GetETag ();
      }

      MdfMetaDataSetCommonProperties ( metaData, pTags, count );
      delete [] pTags;
    }

    /**
     * @brief Returns the XML snippet for metadata.
     * @return XML string.
     */
    std::string GetXmlSnippet () const {
      std::string str ( MdfMetaDataGetXmlSnippet ( metaData, nullptr ) + 1, '\0' );
      str.resize ( MdfMetaDataGetXmlSnippet ( metaData, str.data () ) );
      return str;
    }

    /**
     * @brief Set the XML snippet for metadata.
     * @param xml XML string.
     */
    void SetXmlSnippet ( const char* xml ) {
      MdfMetaDataSetXmlSnippet ( metaData, xml );
    }

    /**
     * @brief Add a common property tag.
     * @param tag Tag wrapper.
     */
    void AddCommonProperty ( const MdfETag &tag ) {
      MdfMetaDataAddCommonProperty ( metaData, tag.GetETag () );
    }
  };
}  // namespace MdfLibrary