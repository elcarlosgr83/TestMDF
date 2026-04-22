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
   * @file MdfFileHistory.h
   * @brief Wrapper for MDF file history entries.
   *
   * File history entries record timestamped tool usage and metadata updates.
   *
   * @ingroup mdflibrary
   */
  class MdfFileHistory {
  private:
    mdf::IFileHistory* history;

  public:
    /**
     * @brief Wrap an existing file history handle.
     * @param history Low-level file history pointer.
     */
    MdfFileHistory ( mdf::IFileHistory* history ) : history ( history ) {
      if ( history == nullptr )
      { throw std::runtime_error ( "MdfFileHistory Init failed" ); }
    }

    /**
     * @brief Wrap a const file history handle.
     * @param history Low-level const pointer.
     */
    MdfFileHistory ( const mdf::IFileHistory* history )
      : MdfFileHistory ( const_cast<mdf::IFileHistory*> ( history ) ) {}

    ~MdfFileHistory () { history = nullptr; }

    /**
     * @brief Returns the history index.
     * @return History index.
     */
    int64_t GetIndex () const { return MdfFileHistoryGetIndex ( history ); }

    /**
     * @brief Returns the history timestamp.
     * @return Time value.
     */
    uint64_t GetTime () const { return MdfFileHistoryGetTime ( history ); }

    /**
     * @brief Set the history timestamp.
     * @param time Timestamp value.
     */
    void SetTime ( uint64_t time ) { MdfFileHistorySetTime ( history, time ); }

    /**
     * @brief Returns the metadata wrapper.
     * @return `MdfMetaData` wrapper.
     */
    const MdfMetaData GetMetaData () const {
      return MdfFileHistoryGetMetaData ( history );
    }

    /**
     * @brief Returns the history description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfFileHistoryGetDescription ( history, nullptr ) + 1, '\0' );
      str.resize ( MdfFileHistoryGetDescription ( history, str.data () ) );
      return str;
    }

    /**
     * @brief Set the history description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) {
      MdfFileHistorySetDescription ( history, desc );
    }

    /**
     * @brief Returns the tool name.
     * @return Tool name string.
     */
    std::string GetToolName () const {
      std::string str ( MdfFileHistoryGetToolName ( history, nullptr ) + 1, '\0' );
      str.resize ( MdfFileHistoryGetToolName ( history, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tool name.
     * @param name Tool name string.
     */
    void SetToolName ( const char* name ) {
      MdfFileHistorySetToolName ( history, name );
    }

    /**
     * @brief Returns the tool vendor.
     * @return Vendor string.
     */
    std::string GetToolVendor () const {
      std::string str ( MdfFileHistoryGetToolVendor ( history, nullptr ) + 1, '\0' );
      str.resize ( MdfFileHistoryGetToolVendor ( history, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tool vendor.
     * @param vendor Vendor string.
     */
    void SetToolVendor ( const char* vendor ) {
      MdfFileHistorySetToolVendor ( history, vendor );
    }

    /**
     * @brief Returns the tool version.
     * @return Version string.
     */
    std::string GetToolVersion () const {
      std::string str ( MdfFileHistoryGetToolVersion ( history, nullptr ) + 1, '\0' );
      str.resize ( MdfFileHistoryGetToolVersion ( history, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tool version.
     * @param version Version string.
     */
    void SetToolVersion ( const char* version ) {
      MdfFileHistorySetToolVersion ( history, version );
    }

    /**
     * @brief Returns the user name.
     * @return User name string.
     */
    std::string GetUserName () const {
      std::string str ( MdfFileHistoryGetUserName ( history, nullptr ) + 1, '\0' );
      str.resize ( MdfFileHistoryGetUserName ( history, str.data () ) );
      return str;
    }

    /**
     * @brief Set the user name.
     * @param user User name string.
     */
    void SetUserName ( const char* user ) {
      MdfFileHistorySetUserName ( history, user );
    }
  };
}  // namespace MdfLibrary
