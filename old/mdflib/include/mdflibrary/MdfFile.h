/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
/**
 * @file MdfFile.h
 * @brief C++ wrapper for MDF file access.
 *
 * The `MdfLibrary::MdfFile` class provides a small, convenient wrapper around
 * the lower-level `mdf::MdfFile` API. It simplifies file metadata access and
 * strongly types the underlying MDF object handle.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include "MdfHeader.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfFile
   * @brief Wrapper for an MDF file handle.
   *
   * This class encapsulates the raw `mdf::MdfFile` pointer and exposes high-level
   * accessors for file name, version, attachments and data groups.
   */
  class MdfFile {
  private:
    mdf::MdfFile* file;

  public:
    MdfFile ( mdf::MdfFile* file ) : file ( file ) {
      if ( file == nullptr ) {
        throw std::runtime_error ( "MdfFile Init failed" );
      }
    }
    MdfFile ( const mdf::MdfFile* file )
      : MdfFile ( const_cast<mdf::MdfFile*> ( file ) ) {}
    ~MdfFile () { file = nullptr; }

    /**
     * @brief Returns the display name of the MDF file.
     * @return Short file name without path and extension.
     */
    std::string GetName () const {
      std::string str ( MdfFileGetName ( file, nullptr ) + 1, '\0' );
      str.resize ( MdfFileGetName ( file, str.data () ) );
      return str;
    }

    /**
     * @brief Sets the display name for the MDF file.
     * @param name Short file name to use for display.
     */
    void SetName ( const char* name ) { MdfFileSetName ( file, name ); }

    /**
     * @brief Returns the full file name including path.
     * @return File name with path and extension.
     */
    std::string GetFileName () const {
      std::string str ( MdfFileGetFileName ( file, nullptr ) + 1, '\0' );
      str.resize ( MdfFileGetFileName ( file, str.data () ) );
      return str;
    }

    /**
     * @brief Sets the full file name including path.
     * @param filename File name with path and extension.
     */
    void SetFileName ( const char* filename ) { MdfFileSetFileName ( file, filename ); }

    /**
     * @brief Returns the MDF version string.
     * @return Version string such as "4.11".
     */
    std::string GetVersion () const {
      std::string str ( MdfFileGetVersion ( file, nullptr ) + 1, '\0' );
      str.resize ( MdfFileGetVersion ( file, str.data () ) );
      return str;
    }

    /**
     * @brief Returns the major MDF version number.
     * @return Major version, for example 4.
     */
    int GetMainVersion () const { return MdfFileGetMainVersion ( file ); }

    /**
     * @brief Returns the minor MDF version number.
     * @return Minor version number.
     */
    int GetMinorVersion () const { return MdfFileGetMinorVersion ( file ); }

    /**
     * @brief Sets the minor MDF version number.
     * @param minor Minor version number.
     */
    void SetMinorVersion ( int minor ) { MdfFileSetMinorVersion ( file, minor ); }

    /**
     * @brief Returns the program identifier stored in the MDF file.
     * @return Program identifier string.
     */
    std::string GetProgramId () const {
      std::string str ( MdfFileGetProgramId ( file, nullptr ) + 1, '\0' );
      str.resize ( MdfFileGetProgramId ( file, str.data () ) );
      return str;
    }

    /**
     * @brief Sets the program identifier in the MDF file.
     * @param program_id Program identifier string.
     */
    void SetProgramId ( const char* program_id ) {
      MdfFileSetProgramId ( file, program_id );
    }
    bool GetFinalized ( uint16_t& standard_flags, uint16_t& custom_flags ) {
      return MdfFileGetFinalized ( file, standard_flags, custom_flags );
    }
    const MdfHeader GetHeader () const { return MdfFileGetHeader ( file ); }
    bool GetIsMdf4 () { return MdfFileGetIsMdf4 ( file ); }
    std::vector<MdfAttachment> GetAttachments () const {
      size_t count = MdfFileGetAttachments ( file, nullptr );

      if ( count <= 0 )
        return {};

      auto pAttachments = new const mdf::IAttachment* [ count ];

                                                      MdfFileGetAttachments ( file, pAttachments );

                                                      std::vector<MdfAttachment> attachments;

                                                      for ( size_t i = 0; i < count; i++ ) {
                                                        attachments.push_back ( pAttachments [ i ] );
                                                      }

                                                      delete [] pAttachments;
                                                      return attachments;
                                                    }
                                                    std::vector<MdfDataGroup> GetDataGroups () const {
                                                      size_t count = MdfFileGetDataGroups ( file, nullptr );

                                                      if ( count <= 0 )
                                                        return {};

      auto pDataGroups = new const mdf::IDataGroup* [ count ];

                                                    MdfFileGetDataGroups ( file, pDataGroups );

                                                    std::vector<MdfDataGroup> data_groups;

                                                    for ( size_t i = 0; i < count; i++ ) {
                                                      data_groups.push_back ( pDataGroups [ i ] );
                                                    }

                                                    delete [] pDataGroups;
                                                    return data_groups;
                                                  }
                                                  MdfAttachment CreateAttachment () { return MdfFileCreateAttachment ( file ); }
                                                  MdfDataGroup CreateDataGroup () { return MdfFileCreateDataGroup ( file ); }
                                                };
                                              }  // namespace MdfLibrary