/**
 * @file mdenumerate.h
 * @brief MDF header declarations for mdenumerate.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <utility>
#include <string>
#include <vector>

#include "mdf/mdstandardattribute.h"
#include "mdf/mdproperty.h"
#include "mdf/mdstring.h"

namespace mdf {

  /**
   * @brief MdEnumerate class definition.
   */
  class MdEnumerate;

  using MdEnumerateValueList = std::vector<MdString>;
  using MdEnumerateList = std::map<std::string, MdEnumerate>;

  /**
   * @brief MdEnumerate class definition.
   */
  class MdEnumerate : public MdProperty {
  public:
    /**
     * @brief AddValue.
     * @param value value.
     */
    void AddValue ( MdString value );
    /**
     * @brief ValueList.
     * @return [ [ nodiscard ] ] MdEnumerateValueList&.
     */
    [ [ nodiscard ] ] const MdEnumerateValueList& ValueList () const;
    /**
     * @brief ValueList.
     * @return [ [ nodiscard ] ] MdEnumerateValueList&.
     */
    [ [ nodiscard ] ] MdEnumerateValueList& ValueList ();
      /**
       * @brief ToXml.
       * @param elist_node elist_node.
       */
      void ToXml ( IXmlNode& elist_node ) const override;
      /**
       * @brief FromXml.
       * @param elist_node elist_node.
       */
      void FromXml ( const IXmlNode& elist_node ) override;

    protected:
      MdEnumerateValueList value_list_;
  };

  }  // namespace mdf