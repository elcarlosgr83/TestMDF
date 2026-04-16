/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

/**
 * \file mdenumerate.h
 * \brief MDF core API header for enumerations.
 *
 * @ingroup mdf
 */

/**
 * \file mdenumerate.h
 * \brief MDF core API header for enumerations.
 *
 * @ingroup mdf
 */

#pragma once

#include <utility>
#include <string>
#include <vector>

#include "mdf/mdstandardattribute.h"
#include "mdf/mdproperty.h"
#include "mdf/mdstring.h"

namespace mdf {

  class MdEnumerate;

  using MdEnumerateValueList = std::vector<MdString>;
  using MdEnumerateList = std::map<std::string, MdEnumerate>;

  class MdEnumerate : public MdProperty {
  public:
    void AddValue ( MdString value );
    [ [ nodiscard ] ] const MdEnumerateValueList& ValueList () const;
    [ [ nodiscard ] ] MdEnumerateValueList& ValueList ();
      void ToXml ( IXmlNode& elist_node ) const override;
      void FromXml ( const IXmlNode& elist_node ) override;

    protected:
      MdEnumerateValueList value_list_;
  };

  }  // namespace mdf

