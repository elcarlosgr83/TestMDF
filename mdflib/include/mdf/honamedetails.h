/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <string>

#include "mdf/mdstring.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief HoNameDetails class definition.
   */
  class HoNameDetails {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] virtual bool.
     */
    [ [ nodiscard ] ] virtual bool IsActive () const;

      /**
       * @brief ShortName.
       * @param short_name short_name.
       */
      void ShortName ( std::string short_name );
    /**
     * @brief ShortName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& ShortName () const;

      /**
       * @brief AddLongName.
       * @param long_name long_name.
       */
      void AddLongName ( MdString long_name );
    /**
     * @brief LongNames.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] const MdStringList& LongNames () const;
    /**
     * @brief LongNames.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] MdStringList& LongNames ();

      /**
       * @brief AddDescription.
       * @param description description.
       */
      void AddDescription ( MdString description );
    /**
     * @brief Descriptions.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] const MdStringList& Descriptions () const;
    /**
     * @brief Descriptions.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] MdStringList& Descriptions ();

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @return virtual void.
       */
      virtual void ToXml ( IXmlNode& root_node ) const;
      /**
       * @brief FromXml.
       * @param root_node root_node.
       * @return virtual void.
       */
      virtual void FromXml ( const IXmlNode& root_node );
    protected:
      std::string short_name_;
      MdStringList long_name_list_;
      MdStringList description_list_;
  };

  }  // namespace mdf