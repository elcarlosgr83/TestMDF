/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <string>
#include <map>
#include "mdf/mdstring.h"

namespace mdf {
  /**
   * @brief MdSyntax class definition.
   */
  class MdSyntax;

  using MdSyntaxList = std::map<std::string, MdSyntax>;

  /**
   * @brief MdSyntax class definition.
   */
  class MdSyntax : public MdString {
  public:
    /**
     * @brief Syntax.
     * @param syntax syntax.
     */
    void Syntax ( std::string syntax );
    /**
     * @brief Syntax.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Syntax () const;

      /**
       * @brief Version.
       * @param version version.
       */
      void Version ( std::string version );
    /**
     * @brief Version.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Version () const;

      /**
       * @brief Source.
       * @param source source.
       */
      void Source ( std::string source );
    /**
     * @brief Source.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Source () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @param tag_name tag_name.
       */
      void ToXml ( IXmlNode& root_node, const std::string& tag_name ) const override;
      /**
       * @brief FromXml.
       * @param syntax_node syntax_node.
       */
      void FromXml ( const IXmlNode& syntax_node ) override;
    private:
      std::string version_ = "1.0";
      std::string source_;
  };

  }  // namespace mdf