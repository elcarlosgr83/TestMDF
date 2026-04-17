/**
 * @file hoenumerates.h
 * @brief MDF header declarations for hoenumerates.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstddef>
#include <string_view>
#include <string>

namespace mdf {

  /**
   * @brief enum class HoDataType enumeration.
   */
  enum class HoDataType : size_t {
    Uint8 = 0,
    Int8,
    Uint16,
    Int16,
    Uint32,
    Int32,
    Uint64,
    Int64,
    Float32,
    Float64,
    AsciiString,
    Unicode2String,
    ByteField,
    BitField,
    Other
  };

  /**
   * @brief HoDataTypeToString.
   * @param data_type data_type.
   * @return std::string_view.
   */
  std::string_view HoDataTypeToString ( HoDataType data_type );
  /**
   * @brief StringToHoDataType.
   * @param data_type data_type.
   * @return HoDataType.
   */
  HoDataType StringToHoDataType ( const std::string& data_type );

  /**
   * @brief enum class HoIntervalType enumeration.
   */
  enum class HoIntervalType : size_t {
    Open = 0,
    Closed,
    Infinite
  };

  /**
   * @brief HoIntervalTypeToString.
   * @param type type.
   * @return std::string_view.
   */
  std::string_view HoIntervalTypeToString ( HoIntervalType type );
  /**
   * @brief StringToHoIntervalType.
   * @param interval_type interval_type.
   * @return HoIntervalType.
   */
  HoIntervalType StringToHoIntervalType ( const std::string& interval_type );

  /**
   * @brief enum class HoValidity enumeration.
   */
  enum class HoValidity : size_t {
    Valid = 0,
    NotValid,
    NotAvailable,
    NotDefined,
    Error,
    Other,
  };

  /**
   * @brief HoValidityToString.
   * @param valid valid.
   * @return std::string_view.
   */
  std::string_view HoValidityToString ( HoValidity valid );
  /**
   * @brief StringToHoValidity.
   * @param valid valid.
   * @return HoValidity.
   */
  HoValidity StringToHoValidity ( const std::string& valid );

  /**
   * @brief enum class HoDataCategory enumeration.
   */
  enum class HoDataCategory : size_t {
    LendingLengthInfoType = 0,
    EndOfPdu,
    MinMaxLengthType,
    StandardLengthType
  };

  /**
   * @brief HoDataCategoryToString.
   * @param category category.
   * @return std::string_view.
   */
  std::string_view HoDataCategoryToString ( HoDataCategory category );
  /**
   * @brief StringToHoDataCategory.
   * @param category category.
   * @return HoDataCategory.
   */
  HoDataCategory StringToHoDataCategory ( const std::string& category );

  /**
   * @brief enum class HoDataEncoding enumeration.
   */
  enum class HoDataEncoding : size_t {
    Signed = 0,
    Unsigned,
    Bit,
    IeeeFloatingType,
    Bcd,
    DspFractional,
    Sm,
    BcdP,
    BcdUp,
    OneC,
    TwoC,
    Utf8,
    Ucs2,
    Iso8859_1,
    Iso8859_2,
    Windows1252,
  };

  /**
   * @brief HoDataEncodingToString.
   * @param encoding encoding.
   * @return std::string_view.
   */
  std::string_view HoDataEncodingToString ( HoDataEncoding encoding );
  /**
   * @brief StringToHoDataEncoding.
   * @param encoding encoding.
   * @return HoDataEncoding.
   */
  HoDataEncoding StringToHoDataEncoding ( const std::string& encoding );

  /**
   * @brief enum class HoDataTermination enumeration.
   */
  enum class HoDataTermination : size_t {
    None = 0,
    Zero,
    HexFF,
    Length
  };

  /**
   * @brief HoDataTerminationToString.
   * @param termination termination.
   * @return std::string_view.
   */
  std::string_view HoDataTerminationToString ( HoDataTermination termination );
  /**
   * @brief StringToHoDataTermination.
   * @param termination termination.
   * @return HoDataTermination.
   */
  HoDataTermination StringToHoDataTermination ( const std::string& termination );

  /**
   * @brief enum class HoRoleType enumeration.
   */
  enum class HoRoleType : size_t {
    Manufacturer = 0,
    Supplier
  };

  /**
   * @brief HoRoleTypeToString.
   * @param role role.
   * @return std::string_view.
   */
  std::string_view HoRoleTypeToString ( HoRoleType role );
  /**
   * @brief StringToHoRoleTYpe.
   * @param role role.
   * @return HoRoleType.
   */
  HoRoleType StringToHoRoleTYpe ( const std::string& role );

  /**
   * @brief enum class HoComputationMethodCategory enumeration.
   */
  enum class HoComputationMethodCategory : size_t {
    Identical = 0,
    Linear,
    ScaleLinear,
    TextTable,
    TabNoInterpolation,
    Formula
  };

  /**
   * @brief HoComputationMethodCategoryToString.
   * @param category category.
   * @return std::string_view.
   */
  std::string_view HoComputationMethodCategoryToString (
    HoComputationMethodCategory category );
  /**
   * @brief StringToHoComputationMethodCategory.
   * @param category category.
   * @return HoComputationMethodCategory.
   */
  HoComputationMethodCategory StringToHoComputationMethodCategory (
    const std::string& category );

  /**
   * @brief enum class HoUnitGroupCategory enumeration.
   */
  enum class HoUnitGroupCategory : size_t {
    Country = 0,
    EquivUnits,
  };

  /**
   * @brief HoUnitGroupCategoryToString.
   * @param category category.
   * @return std::string_view.
   */
  std::string_view HoUnitGroupCategoryToString (
    HoUnitGroupCategory category );
  /**
   * @brief StringToHoUnitGroupCategory.
   * @param category category.
   * @return HoUnitGroupCategory.
   */
  HoUnitGroupCategory StringToHoUnitGroupCategory (
    const std::string& category );

} // end namespace mdf