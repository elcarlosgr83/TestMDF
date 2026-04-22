/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <optional>
#include <vector>

#include "mdf/hoscaleconstraint.h"
#include "mdf/mdstring.h"

namespace mdf {

  /**
   * @brief HoCompuScale class definition.
   */
  class HoCompuScale;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using CoeffList = std::vector<double>;
  using HoCompuScaleList = std::vector<HoCompuScale>;

  /**
   * @brief HoCompuScale class definition.
   */
  class HoCompuScale : public HoScaleConstraint {
  public:
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
       * @brief ConstFloatValue.
       * @param value value.
       */
      void ConstFloatValue ( double value );
    /**
     * @brief ConstFloatValue.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double ConstFloatValue () const;

      /**
       * @brief ConstTextValue.
       * @param value value.
       */
      void ConstTextValue ( std::string value );
    /**
     * @brief ConstTextValue.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ConstTextValue () const;

      /**
       * @brief AddNumerator.
       * @param value value.
       */
      void AddNumerator ( double value );
    /**
     * @brief Numerators.
     * @return [ [ nodiscard ] ] CoeffList&.
     */
    [ [ nodiscard ] ] const CoeffList& Numerators () const;
    /**
     * @brief Numerators.
     * @return [ [ nodiscard ] ] CoeffList&.
     */
    [ [ nodiscard ] ] CoeffList& Numerators ();

      /**
       * @brief AddDenominator.
       * @param value value.
       */
      void AddDenominator ( double value );
    /**
     * @brief Denominators.
     * @return [ [ nodiscard ] ] CoeffList&.
     */
    [ [ nodiscard ] ] const CoeffList& Denominators () const;
    /**
     * @brief Denominators.
     * @return [ [ nodiscard ] ] CoeffList&.
     */
    [ [ nodiscard ] ] CoeffList& Denominators ();

      /**
       * @brief GenericMath.
       * @param math math.
       */
      void GenericMath ( std::string math );
    /**
     * @brief GenericMath.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& GenericMath () const;

      /**
       * @brief ToXml.
       * @param scales_node scales_node.
       */
      void ToXml ( IXmlNode& scales_node ) const override;
      /**
       * @brief FromXml.
       * @param scale_node scale_node.
       */
      void FromXml ( const IXmlNode& scale_node ) override;
    private:
      MdStringList description_list_;

      std::optional<double> const_float_value_;
      std::optional<std::string> const_text_value_;

      CoeffList numerator_list_;
      CoeffList denominator_list_;
      std::string generic_math_;

  };

  }  // namespace mdf