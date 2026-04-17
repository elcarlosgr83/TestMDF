/**
 * @file mdstring.h
 * @brief MDF header declarations for mdstring.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <string_view>
#include <string>
#include <vector>
#include <optional>

#include "mdf/mdstandardattribute.h"

namespace mdf {

  /**
   * @brief MdString class definition.
   */
  class MdString;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using MdStringList = std::vector<MdString>;

  /**
   * @brief MdString class definition.
   */
  class MdString : public MdStandardAttribute {
  public:

    /**
     * @brief MdString.
     */
    MdString () = default;
    /**
     * @brief MdString.
     * @param text text.
     * @param history_index history_index.
     * @param language language.
     * @return explicit.
     */
    explicit MdString ( const char* text, uint64_t history_index = 0,
                        std::string language = {} );

    /**
     * @brief MdString.
     * @param text text.
     * @param history_index history_index.
     * @param language language.
     * @return explicit.
     */
    explicit MdString ( const std::string_view& text, uint64_t history_index = 0,
                        std::string language = {} );

    /**
     * @brief MdString.
     * @param text text.
     * @param history_index history_index.
     * @param language language.
     * @return explicit.
     */
    explicit MdString ( std::string text, uint64_t history_index = 0,
                        std::string language = {} );

    /**
     * @brief std::string&.
     * @param constructor constructor.
     * @return operator.
     */
    operator const std::string& () const; // NOLINT(*-explicit-constructor)

    /**
     * @brief <.
     * @param text text.
     * @return [ [ nodiscard ] ] bool operator.
     */
    [ [ nodiscard ] ] bool operator < ( const MdString& text ) const;

    /**
     * @brief ==.
     * @param text text.
     * @return [ [ nodiscard ] ] bool operator.
     */
    [ [ nodiscard ] ] bool operator == ( const MdString& text ) const;

    /**
     * @brief ==.
     * @param text text.
     * @return [ [ nodiscard ] ] bool operator.
     */
    [ [ nodiscard ] ] bool operator == ( const std::string& text ) const;

    /**
     * @brief ==.
     * @param text text.
     * @return [ [ nodiscard ] ] bool operator.
     */
    [ [ nodiscard ] ] bool operator == ( const std::string_view& text ) const;

    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const override;

      /**
       * @brief Text.
       * @param text text.
       */
      void Text ( std::string text );
    /**
     * @brief Text.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Text () const;

      /**
       * @brief Offset.
       * @param offset offset.
       */
      void Offset ( uint64_t offset );
    /**
     * @brief Offset.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t Offset () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @param tag_name tag_name.
       * @return virtual void.
       */
      virtual void ToXml ( IXmlNode& root_node, const std::string& tag_name ) const;
      /**
       * @brief FromXml.
       * @param node node.
       */
      void FromXml ( const IXmlNode& node ) override;
    private:
      std::string text_;
      std::optional<uint64_t> offset_;

  };

  }  // namespace mdf