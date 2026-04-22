/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <optional>

#include "mdf/honamedetails.h"
#include "mdf/hoenumerates.h"
#include "mdf/hoscaleconstraint.h"
#include "mdf/hocompuscale.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief HoCompuMethod class definition.
   */
  class HoCompuMethod : public HoNameDetails {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const override;

      /**
       * @brief Category.
       * @param category category.
       */
      void Category ( HoComputationMethodCategory category );
    /**
     * @brief Category.
     * @return [ [ nodiscard ] ] HoComputationMethodCategory.
     */
    [ [ nodiscard ] ] HoComputationMethodCategory Category () const;

      /**
       * @brief UnitReference.
       * @param unit_ref unit_ref.
       */
      void UnitReference ( std::string unit_ref );
    /**
     * @brief UnitReference.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& UnitReference () const;

      /**
       * @brief AddPhysicalConstraint.
       * @param constraint constraint.
       */
      void AddPhysicalConstraint ( HoScaleConstraint constraint );
    /**
     * @brief PhysicalConstraints.
     * @return [ [ nodiscard ] ] HoScaleConstraintList&.
     */
    [ [ nodiscard ] ] const HoScaleConstraintList& PhysicalConstraints () const;
    /**
     * @brief PhysicalConstraints.
     * @return [ [ nodiscard ] ] HoScaleConstraintList&.
     */
    [ [ nodiscard ] ] HoScaleConstraintList& PhysicalConstraints ();

      /**
       * @brief AddInternalConstraint.
       * @param constraint constraint.
       */
      void AddInternalConstraint ( HoScaleConstraint constraint );
    /**
     * @brief InternalConstraints.
     * @return [ [ nodiscard ] ] HoScaleConstraintList&.
     */
    [ [ nodiscard ] ] const HoScaleConstraintList& InternalConstraints () const;
    /**
     * @brief InternalConstraints.
     * @return [ [ nodiscard ] ] HoScaleConstraintList&.
     */
    [ [ nodiscard ] ] HoScaleConstraintList& InternalConstraints ();

      /**
       * @brief AddCompuScale.
       * @param scale scale.
       */
      void AddCompuScale ( HoCompuScale scale );
    /**
     * @brief CompuScales.
     * @return [ [ nodiscard ] ] HoCompuScaleList&.
     */
    [ [ nodiscard ] ] const HoCompuScaleList& CompuScales () const;
    /**
     * @brief CompuScales.
     * @return [ [ nodiscard ] ] HoCompuScaleList&.
     */
    [ [ nodiscard ] ] HoCompuScaleList& CompuScales ();

      /**
       * @brief DefaultFloatValue.
       * @param value value.
       */
      void DefaultFloatValue ( double value );
    /**
     * @brief DefaultFloatValue.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double DefaultFloatValue () const;

      /**
       * @brief DefaultTextValue.
       * @param value value.
       */
      void DefaultTextValue ( std::string value );
    /**
     * @brief DefaultTextValue.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string DefaultTextValue () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       */
      void ToXml ( IXmlNode& root_node ) const override;
      /**
       * @brief FromXml.
       * @param root_node root_node.
       */
      void FromXml ( const IXmlNode& root_node ) override;
    private:
      HoComputationMethodCategory category_ = HoComputationMethodCategory::Identical;
      std::string unit_ref_;
      HoScaleConstraintList physical_constraint_list_;
      HoScaleConstraintList internal_constraint_list_;
      HoCompuScaleList compu_scale_list_;

      std::optional<double> default_float_value_;
      std::optional<std::string> default_text_value_;
  };

  }  // namespace mdf