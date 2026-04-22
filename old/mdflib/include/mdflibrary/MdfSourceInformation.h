/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>
#include <string>

#include "MdfMetaData.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @file MdfSourceInformation.h
   * @brief Wrapper for source information objects.
   *
   * This wrapper exposes file source metadata such as name, path, type, bus and
   * associated metadata.
   *
   * @ingroup mdflibrary
   */
  class MdfSourceInformation {
  private:
    mdf::ISourceInformation* sourceInformation;

  public:
    /**
     * @brief Wrap an existing source information handle.
     * @param sourceInformation Low-level source information pointer.
     */
    MdfSourceInformation ( mdf::ISourceInformation* sourceInformation )
      : sourceInformation ( sourceInformation ) {
      if ( sourceInformation == nullptr )
      { throw std::runtime_error ( "MdfSourceInformation Init failed" ); }
    }

    /**
     * @brief Wrap a const source information handle.
     * @param sourceInformation Low-level const pointer.
     */
    MdfSourceInformation ( const mdf::ISourceInformation* sourceInformation )
      : MdfSourceInformation (
          const_cast<mdf::ISourceInformation*> ( sourceInformation ) ) {}

    ~MdfSourceInformation () { sourceInformation = nullptr; }

    /**
     * @brief Returns the source index.
     * @return Source index.
     */
    int64_t GetIndex () const {
      return MdfSourceInformationGetIndex ( sourceInformation );
    }

    /**
     * @brief Returns the source name.
     * @return Name string.
     */
    std::string GetName () const {
      std::string str ( MdfSourceInformationGetName ( sourceInformation,
                        nullptr ) + 1, '\0' );
      str.resize ( MdfSourceInformationGetName ( sourceInformation, str.data () ) );
      return str;
    }

    /**
     * @brief Set the source name.
     * @param name Name string.
     */
    void SetName ( const char* name ) {
      MdfSourceInformationSetName ( sourceInformation, name );
    }

    /**
     * @brief Returns the source description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfSourceInformationGetDescription ( sourceInformation,
                        nullptr ) + 1, '\0' );
      str.resize ( MdfSourceInformationGetDescription ( sourceInformation,
                   str.data () ) );
      return str;
    }

    /**
     * @brief Set the source description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) {
      MdfSourceInformationSetDescription ( sourceInformation, desc );
    }

    /**
     * @brief Returns the source path.
     * @return Path string.
     */
    std::string GetPath () const {
      std::string str ( MdfSourceInformationGetPath ( sourceInformation,
                        nullptr ) + 1, '\0' );
      str.resize ( MdfSourceInformationGetPath ( sourceInformation, str.data () ) );
      return str;
    }

    /**
     * @brief Set the source path.
     * @param path Path string.
     */
    void SetPath ( const char* path ) {
      MdfSourceInformationSetPath ( sourceInformation, path );
    }

    /**
     * @brief Returns the source type.
     * @return Source type enum.
     */
    SourceType GetType () const {
      return MdfSourceInformationGetType ( sourceInformation );
    }

    /**
     * @brief Set the source type.
     * @param type Source type.
     */
    void SetType ( SourceType type ) {
      MdfSourceInformationSetType ( sourceInformation, type );
    }

    /**
     * @brief Returns the bus type.
     * @return Bus type enum.
     */
    BusType GetBus () const {
      return MdfSourceInformationGetBus ( sourceInformation );
    }

    /**
     * @brief Set the bus type.
     * @param bus Bus type.
     */
    void SetBus ( BusType bus ) {
      MdfSourceInformationSetBus ( sourceInformation, bus );
    }

    /**
     * @brief Returns the source flags.
     * @return Flags value.
     */
    uint8_t GetFlags () const {
      return MdfSourceInformationGetFlags ( sourceInformation );
    }

    /**
     * @brief Set the source flags.
     * @param flags Flags value.
     */
    void SetFlags ( uint8_t flags ) {
      MdfSourceInformationSetFlags ( sourceInformation, flags );
    }

    /**
     * @brief Returns the metadata wrapper.
     * @return `MdfMetaData` wrapper.
     */
    const MdfMetaData GetMetaData () const {
      return MdfMetaData ( MdfSourceInformationGetMetaData ( sourceInformation ) );
    }

    /**
     * @brief Create source metadata.
     * @return `MdfMetaData` wrapper.
     */
    MdfMetaData CreateMetaData () {
      return MdfMetaData ( MdfSourceInformationCreateMetaData ( sourceInformation ) );
    }
  };
}  // namespace MdfLibrary