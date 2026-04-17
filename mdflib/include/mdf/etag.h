/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
namespace mdf {

  /** \brief The e-tag may optional have a data type below. The value in the
   * XML file is of course string but the data type may be used for
   * interpretation of the value. Note that unit property can also be added.
   *
   * Use ISO UTC date and time formats or avoid these data types if possible
   * as they just causing problem at presentation.
   */
  enum class ETagDataType : uint8_t {
    StringType = 0,  ///< Text value.
    /**
     * @brief value.
     * @param instead instead.
     * @return DecimalType = 1, ///< Decimal.
     */
    DecimalType = 1, ///< Decimal value (use float instead)
    IntegerType = 2, ///< Integer value
    FloatType = 3,   ///< Floating point value
    BooleanType = 4, ///< Boolean tru/false value
    DateType = 5,    ///< Date value according to ISO (YYYY-MM-DD).
    TimeType = 6,    ///< Time value ISO
    /**
     * @brief string.
     * @param ss ss.
     * @return DateTimeType = 7 ///< Date and Time ISO.
     */
    DateTimeType = 7 ///< Date and Time ISO string (YYYY-MM-DD hh:mm:ss)
  };

  /** \brief Helper class for meta data items in an MDF file.
   *
   * Most of meta data related items are stored in an associated MD block
   * which is an XML snippet. The items are stored in 'e' and 'tree' tags.
   *
   * The 'tree' tag is a list of 'e' tags and shall have a unique name attribute
   * and optional description and creator index.
   *
   * The e-tag shall have a unique name attribute and a value. The other
   * attributes are optional.
   */

  class ETag {
  public:
    /** \brief Sets the name attribute in an e-tag or a tree-tag.
     *
     * The name attribute  should be unique making it
     * possible to search for. It is not possible to store if the name is blank.
     * @param name Unique name and not empty.
     */
    /**
     * @brief Name.
     * @param name name.
     */
    void Name ( const std::string& name ) { name_ = name; }

    /** \brief Returns the name attribute
     *
     * @return Name attribute
     */
    [ [ nodiscard ] ] const std::string& Name () const { return name_; }

    /** \brief Optional attribute in an e-tag or tree-tag.
     *
     * @param desc Description text (UTF8)
     */
      /**
       * @brief Description.
       * @param desc desc.
       */
      void Description ( const std::string& desc ) { desc_ = desc; }

      /** \brief Description text
       *
       * @return Description text (UTF8)
       */
    [ [ nodiscard ] ] const std::string& Description () const { return desc_; }

    /** \brief Optional unit of the value in a nn e-tag..
     *
     * @param unit Unit text (UTF8)
     */
      /**
       * @brief Unit.
       * @param unit unit.
       */
      void Unit ( const std::string& unit ) { unit_ = unit; }

      /** \brief Unit of value.
       *
       * @return Unit of value (UTF8)
       */
    [ [ nodiscard ] ] const std::string& Unit () const { return unit_; }

    /** \brief Reference unit
     *
     * Reference to a global unit. This is an advanced MDF4 feature.
     * @param unit_ref Reference to a global unit.
     */
      /**
       * @brief UnitRef.
       * @param unit_ref unit_ref.
       */
      void UnitRef ( const std::string& unit_ref ) { unit_ref_ = unit_ref; }

      /** \brief Reference unit
       *
       * @return Reference unit
       */
    [ [ nodiscard ] ] const std::string& UnitRef () const { return unit_ref_; }

    /**
     * @brief DataType.
     * @param type type.
     */
    void DataType ( ETagDataType type ); ///< Sets the data type
    /**
     * @brief DataType.
     * @return [ [ nodiscard ] ] ETagDataType.
     */
    [ [ nodiscard ] ] ETagDataType DataType () const; ///< Retuns the data type

      /** \brief Data type of the value.
       *
       * The data type is default set to a string. Standard types are according to
       * the XML standard primitive types. Standard types are 'string', 'decimal',
       * 'integer', 'float', 'boolean', 'date', 'time' and 'dateTime'.
       * @param type Data type string
       */
    /**
     * @brief Type.
     * @param type type.
     */
    void Type ( const std::string& type ) { type_ = type; }

    /** \brief Data type of the value.
     *
     * Data types as defined in 'Primitive XML Data Types'.
     * @return Value data type.
     */
    [ [ nodiscard ] ] const std::string& Type () const { return type_; }

    /** \brief Language of the value.
     *
     * Defines the language. Advanced feature.
     * @param language Language string
     */
    /**
     * @brief Language.
     * @param language language.
     */
    void Language ( const std::string& language ) { language_ = language; }

    /** \brief Language code.
     *
     * @return Language code.
     */
    [ [ nodiscard ] ] const std::string& Language () const { return language_; }

    /** \brief The value is read-only.
     *
     * @param read_only Set to true if the value is read-only.
     */
    /**
     * @brief ReadOnly.
     * @param read_only read_only.
     */
    void ReadOnly ( bool read_only ) { read_only_ = read_only; }

    /** \brief Indicates that the value is read-only.
     *
     * @return True if the value is read-only.
     */
    [ [ nodiscard ] ] bool ReadOnly () const { return read_only_; }

    /** \brief Index to FH block.
     *
     * Default set to -1 but can be set to which an index to a FH block indicating
     * who set the value in the block.
     * @param index Index to file history block.
     */
    /**
     * @brief CreatorIndex.
     * @param index index.
     */
    void CreatorIndex ( int index ) { creator_index_ = index; }

    /** \brief Index to file history block
     *
     * @return Index to a file history block.
     */
    [ [ nodiscard ] ] int CreatorIndex () const { return creator_index_; }

    /** \brief Sets the value for an e-tag.
     *
     * @tparam T Type of value.
     * @param value Tag value.
     */
    template <typename T>
    /**
     * @brief Value.
     * @param value value.
     */
    void Value ( const T& value );

    /** \brief Returns the tag value.
     *
     * @tparam T Type of value.
     * @return Tag value.
     */
    template <typename T>
    /**
     * @brief Value.
     * @return [ [ nodiscard ] ] T.
     */
    [ [ nodiscard ] ] T Value () const;

      /** \brief Adds a tag and define this to be a list of tags (tree).
       *
       * Adds a tag meaning that this tag should be treated as a list of tags
       * (tree).
       * @param tag Tag item to add
       */
      /**
       * @brief AddTag.
       * @param tag tag.
       */
      void AddTag ( const ETag& tag );

      /** \brief Return a list of tags.
       *
       * @return List of tag items.
       */
    [ [ nodiscard ] ] const std::vector<ETag>& TreeList () const { return tree_list_; }

  private:
    std::string name_; ///< Tag name
    std::string desc_; ///< Optional descriptive text
    std::string unit_; ///< Optional unit of measure
    /**
     * @brief reference.
     * @param feature feature.
     * @return std::string unit_ref_; ///< Unit.
     */
    std::string unit_ref_; ///< Unit reference (advance feature)
    std::string type_;  ///< Data type
    /**
     * @brief Language.
     * @param feature feature.
     * @return std::string language_; ///<.
     */
    std::string language_; ///< Language (advance feature)
    std::string value_;    ///< Value
    bool read_only_ = false; ///< True if read-only (advance feature)
    int creator_index_ = -1; ///< Reference to the FH block that created the tag)

    std::vector<ETag> tree_list_;
    };

    template <typename T>
    /**
     * @brief ETag::Value.
     * @param value value.
     */
    void ETag::Value ( const T& value ) {
      std::ostringstream temp;
      temp << value;
      /**
       * @brief temp.str.
       * @return value_ =.
       */
      value_ = temp.str ();
  }

  /** \brief Specialization of setting boolean values
   *
   * @param value Boolean value
   */
  template <>
  /**
   * @brief ETag::Value.
   * @param value value.
   */
  void ETag::Value ( const bool& value );

  template <typename T>
  /**
   * @brief ETag::Value.
   * @return T.
   */
  T ETag::Value () const {
    T temp_value = {};

    if ( !value_.empty () ) {
      /**
       * @brief temp.
       * @param value_ value_.
       * @return std::istringstream.
       */
      std::istringstream temp ( value_ );
      temp >> temp_value;
    }

    return temp_value;
  }

  /** \brief Specialization of getting a boolean value.
   *
   * @return Boolean value true/false
   */
  template <>
  /**
   * @brief ETag::Value.
   * @return [ [ nodiscard ] ] bool.
   */
  [ [ nodiscard ] ] bool ETag::Value () const;

    /** \brief Specialization of getting a string value.
     *
     * @return The value as a text string.
     */
    template <>
  /**
   * @brief ETag::Value.
   * @return [ [ nodiscard ] ] std::string.
   */
  [ [ nodiscard ] ] std::string ETag::Value () const;
}  // namespace mdf