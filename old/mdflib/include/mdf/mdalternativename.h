/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <map>
#include <string>
#include <vector>

#include "mdf/mdstring.h"
#include "mdf/mdstandardattribute.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using MdStringList = std::vector<MdString>;

  /**
   * @brief MdAlternativeName class definition.
   */
  class MdAlternativeName : public MdStandardAttribute {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const override;

      /**
       * @brief DefaultName.
       * @param name name.
       */
      void DefaultName ( std::string name );
    /**
     * @brief DefaultName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& DefaultName () const;

      /**
       * @brief AddAlternativeName.
       * @param alternative_name alternative_name.
       */
      void AddAlternativeName ( MdString alternative_name );
      /**
       * @brief AddAlternativeName.
       * @param alternative_name alternative_name.
       */
      void AddAlternativeName ( std::string alternative_name );
      /**
       * @brief AddDisplayName.
       * @param display_name display_name.
       */
      void AddDisplayName ( MdString display_name );
      /**
       * @brief AddVendor.
       * @param vendor vendor.
       */
      void AddVendor ( MdString vendor );
      /**
       * @brief AddDescription.
       * @param description description.
       */
      void AddDescription ( MdString description );

    /**
     * @brief AlternativeNames.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] const MdStringList& AlternativeNames () const;
    /**
     * @brief AlternativeNames.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] MdStringList& AlternativeNames ();

    /**
     * @brief DisplayNames.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] const MdStringList& DisplayNames () const;
    /**
     * @brief DisplayNames.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] MdStringList& DisplayNames ();

    /**
     * @brief Vendors.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] const MdStringList& Vendors () const;
    /**
     * @brief Vendors.
     * @return [ [ nodiscard ] ] MdStringList&.
     */
    [ [ nodiscard ] ] MdStringList& Vendors ();

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
       * @param names_node names_node.
       */
      void ToXml ( IXmlNode& names_node ) const override;
      /**
       * @brief FromXml.
       * @param names_node names_node.
       */
      void FromXml ( const IXmlNode& names_node ) override;

    private:
      std::string default_name_;
      MdStringList name_list_;
      MdStringList display_list_;
      MdStringList vendor_list_;
      MdStringList description_list_;

  };

  }  // namespace mdf