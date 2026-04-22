/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <string>
#include <set>

#include "mdf/honamedetails.h"
#include "mdf/hoenumerates.h"

namespace mdf {

  /**
   * @brief HoUnitGroup class definition.
   */
  class HoUnitGroup;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using HoUnitGroupList = std::map<std::string, HoUnitGroup>;
  using HoUnitRefList = std::set<std::string>;

  /**
   * @brief HoUnitGroup class definition.
   */
  class HoUnitGroup : public HoNameDetails {
  public:
    /**
     * @brief Category.
     * @param category category.
     */
    void Category ( HoUnitGroupCategory category );
    /**
     * @brief Category.
     * @return [ [ nodiscard ] ] HoUnitGroupCategory.
     */
    [ [ nodiscard ] ] HoUnitGroupCategory Category () const;

      /**
       * @brief AddUnitReference.
       * @param unit_ref unit_ref.
       */
      void AddUnitReference ( std::string unit_ref );
    /**
     * @brief UnitRefs.
     * @return [ [ nodiscard ] ] HoUnitRefList&.
     */
    [ [ nodiscard ] ] const HoUnitRefList& UnitRefs () const;
    /**
     * @brief UnitRefs.
     * @return [ [ nodiscard ] ] HoUnitRefList&.
     */
    [ [ nodiscard ] ] HoUnitRefList& UnitRefs ();

      /**
       * @brief ToXml.
       * @param unit_groups_node unit_groups_node.
       */
      void ToXml ( IXmlNode& unit_groups_node ) const override;
      /**
       * @brief FromXml.
       * @param group_node group_node.
       */
      void FromXml ( const IXmlNode& group_node ) override;

    private:
      HoUnitGroupCategory category_ = HoUnitGroupCategory::Country;
      HoUnitRefList unit_ref_list_;

  };

  }  // namespace mdf