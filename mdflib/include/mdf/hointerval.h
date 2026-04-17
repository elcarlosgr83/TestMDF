/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <optional>
#include "mdf/hoenumerates.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief HoInterval class definition.
   */
  class HoInterval {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const;

      /**
       * @brief Limit.
       * @param limit limit.
       */
      void Limit ( double limit );
    /**
     * @brief Limit.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double Limit () const;

      /**
       * @brief Type.
       * @param type type.
       */
      void Type ( HoIntervalType type );
    /**
     * @brief Type.
     * @return [ [ nodiscard ] ] HoIntervalType.
     */
    [ [ nodiscard ] ] HoIntervalType Type () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @param tag_name tag_name.
       */
      void ToXml ( IXmlNode& root_node, const std::string_view& tag_name ) const;
      /**
       * @brief FromXml.
       * @param limit_node limit_node.
       */
      void FromXml ( const IXmlNode& limit_node );
    private:
      std::optional<double> limit_;
      HoIntervalType type_ = HoIntervalType::Closed;
  };

  }  // namespace mdf