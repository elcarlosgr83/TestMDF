/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <string>

#include "mdf/honamedetails.h"

namespace mdf {

  /**
   * @brief HoPhysicalDimension class definition.
   */
  class HoPhysicalDimension;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /** \brief The list is sorted on the Identity attribute . */
  using HoPhysicalDimensionList = std::map<std::string, HoPhysicalDimension>;

  /**
   * @brief HoPhysicalDimension class definition.
   */
  class HoPhysicalDimension : public HoNameDetails {
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
       * @brief LengthExponent.
       * @param length_exp length_exp.
       */
      void LengthExponent ( double length_exp );
    /**
     * @brief LengthExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double LengthExponent () const;

      /**
       * @brief MassExponent.
       * @param mass_exp mass_exp.
       */
      void MassExponent ( double mass_exp );
    /**
     * @brief MassExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double MassExponent () const;

      /**
       * @brief TimeExponent.
       * @param time_exp time_exp.
       */
      void TimeExponent ( double time_exp );
    /**
     * @brief TimeExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double TimeExponent () const;

      /**
       * @brief CurrentExponent.
       * @param current_exp current_exp.
       */
      void CurrentExponent ( double current_exp );
    /**
     * @brief CurrentExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double CurrentExponent () const;

      /**
       * @brief TemperatureExponent.
       * @param temp_exp temp_exp.
       */
      void TemperatureExponent ( double temp_exp );
    /**
     * @brief TemperatureExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double TemperatureExponent () const;

      /**
       * @brief MolarExponent.
       * @param molar_exp molar_exp.
       */
      void MolarExponent ( double molar_exp );
    /**
     * @brief MolarExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double MolarExponent () const;

      /**
       * @brief LuminousExponent.
       * @param luminous_exp luminous_exp.
       */
      void LuminousExponent ( double luminous_exp );
    /**
     * @brief LuminousExponent.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double LuminousExponent () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       */
      void ToXml ( IXmlNode& root_node ) const override;
      /**
       * @brief FromXml.
       * @param dim_node dim_node.
       */
      void FromXml ( const IXmlNode& dim_node ) override;

    private:
      std::string identity_;
      double length_exp_ = 0.0;
      double mass_exp_ = 0.0;
      double time_exp_ = 0.0;
      double current_exp_ = 0.0;
      double temp_exp_ = 0.0;
      double molar_exp_ = 0.0;
      double luminous_exp_ = 0.0;
  };

  }  // namespace mdf