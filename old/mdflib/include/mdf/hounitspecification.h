/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <optional>

#include "mdf/hoadmindata.h"
#include "mdf/hophysicaldimension.h"
#include "mdf/hounitgroup.h"
#include "mdf/hounit.h"
#include "mdf/hointerval.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief HoUnitSpecification class definition.
   */
  class HoUnitSpecification {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const;
    /**
     * @brief AdminData.
     * @return [ [ nodiscard ] ] HoAdminData&.
     */
    [ [ nodiscard ] ] const HoAdminData& AdminData () const;
    /**
     * @brief AdminData.
     * @return [ [ nodiscard ] ] HoAdminData&.
     */
    [ [ nodiscard ] ] HoAdminData& AdminData ();

      /**
       * @brief AddPhysicalDimension.
       * @param dimension dimension.
       */
      void AddPhysicalDimension ( HoPhysicalDimension dimension );
    /**
     * @brief PhysicalDimensions.
     * @return [ [ nodiscard ] ] HoPhysicalDimensionList&.
     */
    [ [ nodiscard ] ] const HoPhysicalDimensionList& PhysicalDimensions () const;
    /**
     * @brief PhysicalDimensions.
     * @return [ [ nodiscard ] ] HoPhysicalDimensionList&.
     */
    [ [ nodiscard ] ] HoPhysicalDimensionList& PhysicalDimensions ();

      /**
       * @brief AddUnitGroup.
       * @param group group.
       */
      void AddUnitGroup ( HoUnitGroup group );
    /**
     * @brief UnitGroups.
     * @return [ [ nodiscard ] ] HoUnitGroupList&.
     */
    [ [ nodiscard ] ] const HoUnitGroupList& UnitGroups () const;
    /**
     * @brief UnitGroups.
     * @return [ [ nodiscard ] ] HoUnitGroupList&.
     */
    [ [ nodiscard ] ] HoUnitGroupList& UnitGroups ();

      /**
       * @brief AddUnit.
       * @param unit unit.
       */
      void AddUnit ( HoUnit unit );
    /**
     * @brief Units.
     * @return [ [ nodiscard ] ] HoUnitList&.
     */
    [ [ nodiscard ] ] const HoUnitList& Units () const;
    /**
     * @brief Units.
     * @return [ [ nodiscard ] ] HoUnitList&.
     */
    [ [ nodiscard ] ] HoUnitList& Units ();

      /**
       * @brief ToXml.
       * @param root_node root_node.
       */
      void ToXml ( IXmlNode& root_node ) const;
      /**
       * @brief FromXml.
       * @param unit_spec_node unit_spec_node.
       */
      void FromXml ( const IXmlNode& unit_spec_node );

    private:
      HoAdminData admin_data_;
      HoPhysicalDimensionList phys_dim_list_;
      HoUnitGroupList unit_group_list_;
      HoUnitList unit_list_;

  };

  }  // namespace mdf