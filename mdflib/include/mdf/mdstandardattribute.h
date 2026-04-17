/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <string>
#include <map>

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using AttributeList = std::map<std::string, std::string>;

  /**
   * @brief MdStandardAttribute class definition.
   */
  class MdStandardAttribute {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] virtual bool.
     */
    [ [ nodiscard ] ] virtual bool IsActive () const;

      /**
       * @brief MdStandardAttribute.
       */
      MdStandardAttribute () = default;
      /**
       * @brief MdStandardAttribute.
       * @param index index.
       * @param language language.
       * @return explicit.
       */
      explicit MdStandardAttribute ( uint64_t index,
      /**
       * @brief std::string.
       * @return std::string language =.
       */
      std::string language = std::string () );

      /**
       * @brief HistoryIndex.
       * @param index index.
       */
      void HistoryIndex ( uint64_t index );
    /**
     * @brief HistoryIndex.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t HistoryIndex () const;

      /**
       * @brief Language.
       * @param language language.
       */
      void Language ( std::string language );
    /**
     * @brief Language.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Language () const;

      /**
       * @brief AddCustomAttribute.
       * @param key key.
       * @param value value.
       */
      void AddCustomAttribute ( std::string key, std::string value );
    /**
     * @brief CustomAttributes.
     * @return [ [ nodiscard ] ] AttributeList&.
     */
    [ [ nodiscard ] ] const AttributeList& CustomAttributes () const;
    /**
     * @brief CustomAttributes.
     * @return [ [ nodiscard ] ] AttributeList&.
     */
    [ [ nodiscard ] ] AttributeList& CustomAttributes ();

      /**
       * @brief ToXml.
       * @param node node.
       * @return virtual void.
       */
      virtual void ToXml ( IXmlNode& node ) const;
      /**
       * @brief FromXml.
       * @param node node.
       * @return virtual void.
       */
      virtual void FromXml ( const IXmlNode& node );
    protected:

      uint64_t ci_ = 0;
      std::string lang_;
      AttributeList custom_attribute_list_;
  };

  }  // namespace mdf