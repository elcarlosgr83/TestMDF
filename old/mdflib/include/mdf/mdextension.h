/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <memory>
#include <vector>

#include "mdf/mdstandardattribute.h"

namespace mdf {

  /**
   * @brief MdExtension class definition.
   */
  class MdExtension;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using MdExtensionPtr = std::unique_ptr<MdExtension>;

  using MdExtensionList = std::vector<MdExtensionPtr>;

  /**
   * @brief MdExtension class definition.
   */
  class MdExtension : public MdStandardAttribute {
  public:
    /**
     * @brief Create.
     * @return [ [ nodiscard ] ] virtual MdExtensionPtr.
     */
    [ [ nodiscard ] ] virtual MdExtensionPtr Create () const;
      /**
       * @brief ToXml.
       * @param ext_node ext_node.
       */
      void ToXml ( IXmlNode& ext_node ) const override;
      /**
       * @brief FromXml.
       * @param ext_node ext_node.
       */
      void FromXml ( const IXmlNode& ext_node ) override;
    protected:
      /**
       * @brief MdExtension.
       */
      MdExtension () = default;
  };

}  // namespace mdf