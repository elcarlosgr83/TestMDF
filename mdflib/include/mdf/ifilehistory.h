/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <string>

#include "imdftimestamp.h"
#include "itimestamp.h"
#include "mdf/iblock.h"
#include "mdf/imetadata.h"
#include "mdf/fhcomment.h"

namespace mdf {

  /** \class IFileHistory ifilehistory.h "mdf/ifilehistory.h"
   * \brief Interface class against an MDF FH block.
   *
   * Interface against an MDF4 file history block. An MDF4 file must have at least
   * one history block that defines it creation. Each time the file is modified,
   * there should be a new history block appended.
   */

  class IFileHistory : public IBlock {
  public:
    /** \brief Sets the time when the history block was created.
     *
     * Sets the absolute start time for the measurement file. It is default
     * set by the application to now.
     * @param ns_since_1970 Nanoseconds since 1970.
     */
    /**
     * @brief Time.
     * @param ns_since_1970 ns_since_1970.
     * @return virtual void.
     */
    virtual void Time ( uint64_t ns_since_1970 ) = 0;

    /**
     * \brief Sets the time using an ITimestamp object.
     *
     * This function sets the time for the history block using an ITimestamp
     * object.
     * @param timestamp An ITimestamp object representing the time.
     */
    virtual void Time ( ITimestamp& timestamp ) = 0;

    /** \brief Returns the time for the history block.
     *
     * Sets the time the history block was created.
     * @return Nanoseconds since 1970.
     */
    /**
     * @brief Time.
     * @return [ [ nodiscard ] ] virtual uint64_t.
     */
    [ [ nodiscard ] ] virtual uint64_t Time () const = 0;

      /** \brief Returns the start timestamp of the measurement.
       *
       * This function returns the start timestamp of the measurement as a pointer
       * to an IMdfTimestamp object.
       * @return Pointer to an IMdfTimestamp object representing the start
       * timestamp.
       */
    /**
     * @brief StartTimestamp.
     * @return [ [ nodiscard ] ] virtual mdf::IMdfTimestamp*.
     */
    [ [ nodiscard ] ] virtual const mdf::IMdfTimestamp* StartTimestamp () const = 0;

      /** \brief Returns an interface against a MD4 block
       *
       * @return Pointer to an meta data block.
       */
    /**
     * @brief CreateMetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData () = 0;

      /** \brief Returns an constant interface against a MD4 block
       *
       * @return Pointer to an meta data block.
       */
    /**
     * @brief MetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual const IMetaData* MetaData () const = 0;

      /** \brief Sets the description for the history block.
       *
       * Sets the description of the history block. The value is stored
       * int the TX tag in the meta data block.
       * @param description Description of history block.
       */
      /**
       * @brief Description.
       * @param description description.
       */
      void Description ( const std::string& description ) {
        /**
         * @brief CreateMetaData.
         * @return auto* md4 =.
         */
        auto* md4 = CreateMetaData ();

        if ( md4 != nullptr ) {
          /**
           * @brief md4->StringProperty.
           * @param description description.
           */
          md4->StringProperty ( "TX", description );
      }
      }

      /** \brief Returns the description.
       *
       * Returns the description.
       * @return Description of the history block.
       */
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Description () const {
        /**
         * @brief MetaData.
         * @return auto* md4 =.
         */
        const auto* md4 = MetaData ();
        return md4 != nullptr ? md4->StringProperty ( "TX" ) : std::string ();
    }

    /** \brief Sets the tool name.
     *
     * Mandatory text that identify the tool name.
     * @param tool_name Name of the tool.
     */
    /**
     * @brief ToolName.
     * @param tool_name tool_name.
     */
    void ToolName ( const std::string& tool_name ) {
      /**
       * @brief CreateMetaData.
       * @return auto* md4 =.
       */
      auto* md4 = CreateMetaData ();

      if ( md4 != nullptr ) {
        /**
         * @brief md4->StringProperty.
         * @param tool_name tool_name.
         */
        md4->StringProperty ( "tool_id", tool_name );
        }
    }

    /** \brief Returns the tool name.
     *
     * @return Tool name.
     */
    /**
     * @brief ToolName.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ToolName () const {
        /**
         * @brief MetaData.
         * @return auto* md4 =.
         */
        const auto* md4 = MetaData ();
        return md4 != nullptr ? md4->StringProperty ( "tool_id" ) : std::string ();
    }

    /** \brief Sets the tool vendor.
     *
     * Mandatory text that identify the tool vendor.
     * @param tool_vendor Vendor name.
     */
    /**
     * @brief ToolVendor.
     * @param tool_vendor tool_vendor.
     */
    void ToolVendor ( const std::string& tool_vendor ) {
      /**
       * @brief CreateMetaData.
       * @return auto* md4 =.
       */
      auto* md4 = CreateMetaData ();

      if ( md4 != nullptr ) {
        /**
         * @brief md4->StringProperty.
         * @param tool_vendor tool_vendor.
         */
        md4->StringProperty ( "tool_vendor", tool_vendor );
      }
      }

      /** \brief Returns the tool vendor.
       *
       * @return Tool vendor.
       */
    /**
     * @brief ToolVendor.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ToolVendor () const {
        /**
         * @brief MetaData.
         * @return auto* md4 =.
         */
        const auto* md4 = MetaData ();
        return md4 != nullptr ? md4->StringProperty ( "tool_vendor" ) : std::string ();
    }

    /** \brief Sets the tool version.
     *
     * Mandatory text that identify the tool version.
     * @param tool_version Version string.
     */
    /**
     * @brief ToolVersion.
     * @param tool_version tool_version.
     */
    void ToolVersion ( const std::string& tool_version ) {
      /**
       * @brief CreateMetaData.
       * @return auto* md4 =.
       */
      auto* md4 = CreateMetaData ();

      if ( md4 != nullptr ) {
        /**
         * @brief md4->StringProperty.
         * @param tool_version tool_version.
         */
        md4->StringProperty ( "tool_version", tool_version );
        }
    }

    /** \brief Returns the tool version.
     *
     * @return Tool version.
     */
    /**
     * @brief ToolVersion.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ToolVersion () const {
        /**
         * @brief MetaData.
         * @return auto* md4 =.
         */
        const auto* md4 = MetaData ();
        return md4 != nullptr ? md4->StringProperty ( "tool_version" ) : std::string ();
    }

    /** \brief Sets the user name.
     *
     * Optional text that identify the user.
     * @param user User name.
     */
    /**
     * @brief UserName.
     * @param user user.
     */
    void UserName ( const std::string& user ) {
      /**
       * @brief CreateMetaData.
       * @return auto* md4 =.
       */
      auto* md4 = CreateMetaData ();

      if ( md4 != nullptr ) {
        /**
         * @brief md4->StringProperty.
         * @param user user.
         */
        md4->StringProperty ( "user_name", user );
      }
      }

      /** \brief Returns the user name.
       *
       * @return User name.
       */
    /**
     * @brief UserName.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string UserName () const {
        /**
         * @brief MetaData.
         * @return auto* md4 =.
         */
        const auto* md4 = MetaData ();
        return md4 != nullptr ? md4->StringProperty ( "user_name" ) : std::string ();
    }

    /** \brief Sets the file history comment.
     * @param fh_comment File history comment object.
     */
    /**
     * @brief SetFhComment.
     * @param fh_comment fh_comment.
     */
    void SetFhComment ( const FhComment& fh_comment );
    /** \brief Retrieves the file history comment.
     * @param fh_comment Receives the file history comment object.
     */
    /**
     * @brief GetFhComment.
     * @param fh_comment fh_comment.
     */
    void GetFhComment ( FhComment& fh_comment ) const;
    };

}  // namespace mdf