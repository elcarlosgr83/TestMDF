/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <vector>

#include "mdf/hoenumerates.h"
#include "mdf/hointerval.h"

namespace mdf {

  /**
   * @brief HoScaleConstraint class definition.
   */
  class HoScaleConstraint;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using HoScaleConstraintList = std::vector<HoScaleConstraint>;

  /**
   * @brief HoScaleConstraint class definition.
   */
  class HoScaleConstraint {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const;

      /**
       * @brief LowerLimit.
       * @param limit limit.
       */
      void LowerLimit ( HoInterval limit );
    /**
     * @brief LowerLimit.
     * @return [ [ nodiscard ] ] HoInterval&.
     */
    [ [ nodiscard ] ] const HoInterval& LowerLimit () const;

      /**
       * @brief UpperLimit.
       * @param limit limit.
       */
      void UpperLimit ( HoInterval limit );
    /**
     * @brief UpperLimit.
     * @return [ [ nodiscard ] ] HoInterval&.
     */
    [ [ nodiscard ] ] const HoInterval& UpperLimit () const;

      /**
       * @brief Validity.
       * @param validity validity.
       */
      void Validity ( HoValidity validity );
    /**
     * @brief Validity.
     * @return [ [ nodiscard ] ] HoValidity.
     */
    [ [ nodiscard ] ] HoValidity Validity () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @return virtual void.
       */
      virtual void ToXml ( IXmlNode& root_node ) const;
      /**
       * @brief FromXml.
       * @param scale_node scale_node.
       * @return virtual void.
       */
      virtual void FromXml ( const IXmlNode& scale_node );

    protected:
      HoInterval lower_limit_;
      HoInterval upper_limit_;
      HoValidity validity_ = HoValidity::Valid;
  };

  }  // namespace mdf