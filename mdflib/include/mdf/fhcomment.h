/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <string>
#include <string_view>
#include "mdf/mdcomment.h"
#include "mdf/mdstring.h"

namespace mdf {

  /**
   * @brief FhComment class definition.
   */
  class FhComment : public MdComment {
  public:
    /**
     * @brief FhComment.
     */
    FhComment ();
    /**
     * @brief FhComment.
     * @param comment comment.
     * @return explicit.
     */
    explicit FhComment ( std::string comment );

    /**
     * @brief ToolId.
     */
    void ToolId ( const std::string_view& tool_id ) { ToolId ( MdString ( tool_id ) ); }
    /**
     * @brief ToolId.
     * @param tool_id tool_id.
     */
    void ToolId ( MdString tool_id );
    /**
     * @brief ToolId.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& ToolId () const;

    /**
     * @brief ToolVendor.
     */
    void ToolVendor ( const std::string_view& tool_vendor ) { ToolVendor ( MdString ( tool_vendor ) ); }
    /**
     * @brief ToolVendor.
     * @param tool_vendor tool_vendor.
     */
    void ToolVendor ( MdString tool_vendor );
    /**
     * @brief ToolVendor.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& ToolVendor () const;

    /**
     * @brief ToolVersion.
     */
    void ToolVersion ( const std::string_view& tool_version ) { ToolVersion ( MdString ( tool_version ) ); }
    /**
     * @brief ToolVersion.
     * @param tool_version tool_version.
     */
    void ToolVersion ( MdString tool_version );
    /**
     * @brief ToolVersion.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& ToolVersion () const;

    /**
     * @brief UserName.
     */
    void UserName ( const std::string_view& user_name ) { UserName ( MdString ( user_name ) ); }
    /**
     * @brief UserName.
     * @param user_name user_name.
     */
    void UserName ( MdString user_name );
    /**
     * @brief UserName.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& UserName () const;

    /**
     * @brief ToXml.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ToXml () const override;
      /**
       * @brief FromXml.
       * @param xml_snippet xml_snippet.
       */
      void FromXml ( const std::string& xml_snippet ) override;
    private:
      MdString tool_id_;
      MdString tool_vendor_;
      MdString tool_version_;
      MdString user_name_;
  };

  }  // namespace mdf