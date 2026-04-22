/**
 * @file mdnumber.h
 * @brief MDF header declarations for mdnumber.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <optional>

#include "mdf/mdstandardattribute.h"
#include "mdf/mdproperty.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief enum class MdByteOrder enumeration.
   */
  enum class MdByteOrder {
    LittleEndian,
    BigEndian
  };

  /**
   * @brief MdNumber class definition.
   */
  class MdNumber : public MdStandardAttribute {
  public:
    /**
     * @brief MdNumber.
     */
    MdNumber () = default;
    /**
     * @brief MdNumber.
     * @param number number.
     * @return explicit.
     */
    explicit MdNumber ( double number );
    /**
     * @brief MdNumber.
     * @param number number.
     * @param data_type data_type.
     * @return explicit.
     */
    explicit MdNumber ( uint64_t number, MdDataType data_type );

    /**
     * @brief Conversion operator.
     * @return T.
     */
    template<typename T> operator T () const { // NOLINT(*-explicit-constructor)
      return Number<T> ();
    }

    template<typename T>
    /**
     * @brief ==.
     * @param value value.
     * @return bool operator.
     */
    bool operator == ( const T& value ) const {
      return value == Number<T> ();
    }

    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const override;

      template <typename T>
      /**
       * @brief Number.
       * @param value value.
       */
      void Number ( T value );

      template <typename T>
    /**
     * @brief Number.
     * @return [ [ nodiscard ] ] T.
     */
    [ [ nodiscard ] ] T Number () const;

      /**
       * @brief DataType.
       * @param type type.
       */
      void DataType ( MdDataType type );
    /**
     * @brief DataType.
     * @return [ [ nodiscard ] ] MdDataType.
     */
    [ [ nodiscard ] ] MdDataType DataType () const;

      /**
       * @brief Triggered.
       * @param triggered triggered.
       */
      void Triggered ( bool triggered );
    /**
     * @brief Triggered.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Triggered () const;

      /**
       * @brief ByteCount.
       * @param byte_count byte_count.
       */
      void ByteCount ( uint64_t byte_count );
    /**
     * @brief ByteCount.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t ByteCount () const;

      /**
       * @brief BitMask.
       * @param bit_mask bit_mask.
       */
      void BitMask ( uint64_t bit_mask );
    /**
     * @brief BitMask.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t BitMask () const;

      /**
       * @brief ByteOrder.
       * @param byte_order byte_order.
       */
      void ByteOrder ( MdByteOrder byte_order );
    /**
     * @brief ByteOrder.
     * @return [ [ nodiscard ] ] MdByteOrder.
     */
    [ [ nodiscard ] ] MdByteOrder ByteOrder () const;

      /**
       * @brief Min.
       * @param min min.
       */
      void Min ( double min );
    /**
     * @brief Min.
     * @return [ [ nodiscard ] ] std::optional<double>&.
     */
    [ [ nodiscard ] ] const std::optional<double>& Min () const;

      /**
       * @brief Max.
       * @param max max.
       */
      void Max ( double max );
    /**
     * @brief Max.
     * @return [ [ nodiscard ] ] std::optional<double>&.
     */
    [ [ nodiscard ] ] const std::optional<double>& Max () const;

      /**
       * @brief Average.
       * @param average average.
       */
      void Average ( double average );
    /**
     * @brief Average.
     * @return [ [ nodiscard ] ] std::optional<double>&.
     */
    [ [ nodiscard ] ] const std::optional<double>& Average () const;

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
       * @brief UnitRef.
       * @param unit_ref unit_ref.
       */
      void UnitRef ( std::string unit_ref );
    /**
     * @brief UnitRef.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& UnitRef () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @param tag_name tag_name.
       * @return virtual void.
       */
      virtual void ToXml ( IXmlNode& root_node, const std::string& tag_name ) const;
      /**
       * @brief FromXml.
       * @param number_node number_node.
       */
      void FromXml ( const IXmlNode& number_node ) override;
    private:
      std::string number_;
      bool triggered_ = false;
      MdDataType data_type_ = MdDataType::MdFloat;
      std::optional<uint64_t> byte_count_;
      std::optional<uint64_t> bit_mask_;
      MdByteOrder byte_order_ = MdByteOrder::LittleEndian;
      std::optional<double> min_;
      std::optional<double> max_;
      std::optional<double> average_;
      std::string unit_;
      std::string unit_ref_;
  };

  template <typename T>
  /**
   * @brief MdNumber::Number.
   * @param value value.
   */
  void MdNumber::Number ( T value ) {
    try {
      /**
       * @brief std::to_string.
       * @param value value.
       * @return number_ =.
       */
      number_ = std::to_string ( value );
      } catch ( const std::exception& ) {
        /**
         * @brief number_.clear.
         */
        number_.clear ();
        /**
         * @brief number_.shrink_to_fit.
         */
        number_.shrink_to_fit ();
    }
    }

    template <>
    /**
     * @brief MdNumber::Number.
     * @param value value.
     */
    void MdNumber::Number ( uint64_t value );

    template <typename T>
    /**
     * @brief MdNumber::Number.
     * @return T.
     */
    T MdNumber::Number () const {
      T value = {};
      /**
       * @brief temp.
       * @param number_ number_.
       * @return std::istringstream.
       */
      std::istringstream temp ( number_ );
      temp >> value;
      return value;
  }

  template <>
  /**
   * @brief MdNumber::Number.
   * @return uint64_t.
   */
  uint64_t MdNumber::Number () const;
  }  // namespace mdf