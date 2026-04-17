/**
 * @file mdproperty.h
 * @brief MDF header declarations for mdproperty.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */


#pragma once

#include <cstdint>
#include <string_view>
#include <string>
#include <map>
#include <sstream>

#include "mdf/mdstandardattribute.h"

namespace mdf {

  /**
   * @brief enum class MdDataType enumeration.
   */
  enum class MdDataType : uint16_t {
    MdString = 0,
    MdDecimal,
    MdInteger,
    MdFloat,
    MdBoolean,
    MdDate,
    MdTime,
    MdDateTime,
    MdHex, ///< Same as MdInteger but written as hex string
  };

  /**
   * @brief MdProperty class definition.
   */
  class MdProperty;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using MdPropertyList = std::map<std::string, MdProperty>;

  /**
   * @brief MdProperty class definition.
   */
  class MdProperty : public MdStandardAttribute {
  public:
    /**
     * @brief MdProperty.
     */
    MdProperty () = default;
    /**
     * @brief MdProperty.
     * @param property property.
     * @param value value.
     */
    MdProperty ( std::string property, std::string value );

    /**
     * @brief Name.
     * @param name name.
     */
    void Name ( std::string name );
    /**
     * @brief Name.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Name () const;

      /**
       * @brief Description.
       * @param description description.
       */
      void Description ( std::string description );
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Description () const;

      /**
       * @brief Unit.
       * @param unit unit.
       */
      void Unit ( std::string unit );
    /**
     * @brief Unit.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Unit () const;

      /**
       * @brief UnitReference.
       * @param unit_reference unit_reference.
       */
      void UnitReference ( std::string unit_reference );
    /**
     * @brief UnitReference.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& UnitReference () const;

      /**
       * @brief DataType.
       * @param data_type data_type.
       */
      void DataType ( MdDataType data_type );
    /**
     * @brief DataType.
     * @return [ [ nodiscard ] ] MdDataType.
     */
    [ [ nodiscard ] ] MdDataType DataType () const;

      /**
       * @brief ReadOnly.
       * @param read_only read_only.
       */
      void ReadOnly ( bool read_only );
    /**
     * @brief ReadOnly.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool ReadOnly () const;

      template <typename T>
      /**
       * @brief Value.
       * @param value value.
       */
      void Value ( T value );

      template <typename T>
    /**
     * @brief Value.
     * @return [ [ nodiscard ] ] T.
     */
    [ [ nodiscard ] ] T Value () const;

      /**
       * @brief ToXml.
       * @param prop_node prop_node.
       */
      void ToXml ( IXmlNode& prop_node ) const override;
      /**
       * @brief FromXml.
       * @param prop_node prop_node.
       */
      void FromXml ( const IXmlNode& prop_node ) override;

    private:
      std::string name_;
      std::string desc_;
      std::string unit_;
      std::string unit_ref_;
      MdDataType data_type_ = MdDataType::MdString;
      bool read_only_ = false;


      std::string value_;

    /**
     * @brief DataTypeToString.
     * @return [ [ nodiscard ] ] std::string_view.
     */
    [ [ nodiscard ] ] std::string_view DataTypeToString () const;
      /**
       * @brief StringToDataType.
       * @param text text.
       */
      void StringToDataType ( const std::string& text );
  };

  template <typename T>
  /**
   * @brief MdProperty::Value.
   * @param value value.
   */
  void MdProperty::Value ( T value ) {
    /**
     * @brief std::to_string.
     * @param value value.
     * @return value_ =.
     */
    value_ = std::to_string ( value );
    }

    template <>
    /**
     * @brief MdProperty::Value.
     * @param value value.
     */
    void MdProperty::Value ( std::string value );

    template <>
    /**
     * @brief MdProperty::Value.
     * @param value value.
     */
    void MdProperty::Value ( bool value );

    template <>
    /**
     * @brief MdProperty::Value.
     * @param value value.
     */
    void MdProperty::Value ( uint64_t value );

    template <typename T>
    /**
     * @brief MdProperty::Value.
     * @return T.
     */
    T MdProperty::Value () const {
      T output = {};

      if ( value_.empty () ) {
        return output;
    }

    /**
     * @brief temp.
     * @param value_ value_.
     * @return std::istringstream.
     */
    std::istringstream temp ( value_ );
    temp >> output;
    return output;
    }

    template <>
    /**
     * @brief MdProperty::Value.
     * @return std::string.
     */
    std::string MdProperty::Value () const;

    template <>
    /**
     * @brief MdProperty::Value.
     * @return uint64_t.
     */
    uint64_t MdProperty::Value () const;

    template <>
    /**
     * @brief MdProperty::Value.
     * @return bool.
     */
    bool MdProperty::Value () const;
}  // namespace mdf