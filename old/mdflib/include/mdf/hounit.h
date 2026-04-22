/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <string>
#include <map>

#include "mdf/honamedetails.h"

namespace mdf {

  /**
   * @brief HoUnit class definition.
   */
  class HoUnit;

  using HoUnitList = std::map<std::string, HoUnit>;

  /**
   * @brief HoUnit class definition.
   */
  class HoUnit : public HoNameDetails {
  public:
    /**
     * @brief Identity.
     * @param identity identity.
     */
    void Identity ( std::string identity );
    /**
     * @brief Identity.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Identity () const;

      /**
       * @brief DisplayName.
       * @param display_name display_name.
       */
      void DisplayName ( std::string display_name );
    /**
     * @brief DisplayName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& DisplayName () const;

      /**
       * @brief Factor.
       * @param factor factor.
       */
      void Factor ( double factor );
    /**
     * @brief Factor.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double Factor () const;

      /**
       * @brief Offset.
       * @param offset offset.
       */
      void Offset ( double offset );
    /**
     * @brief Offset.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double Offset () const;

      /**
       * @brief PhysicalDimensionRef.
       * @param phys_dim_ref phys_dim_ref.
       */
      void PhysicalDimensionRef ( std::string phys_dim_ref );
    /**
     * @brief PhysicalDimensionRef.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& PhysicalDimensionRef () const;

      /**
       * @brief ToXml.
       * @param units_node units_node.
       */
      void ToXml ( IXmlNode& units_node ) const override;
      /**
       * @brief FromXml.
       * @param unit_node unit_node.
       */
      void FromXml ( const IXmlNode& unit_node ) override;

    private:
      std::string identity_;

      std::string display_name_;
      double factor_ = 1.0;
      double offset_ = 0.0;
      std::string phys_dim_ref_;
  };

  }  // namespace mdf