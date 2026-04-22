/**
 * @file ichannelconversion.h
 * @brief MDF header declarations for ichannelconversion.
 */

/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <variant>

#include "mdf/iblock.h"
#include "mdf/imetadata.h"
#include "mdf/mdfhelper.h"
#include "mdf/cccomment.h"
#include "mdf/ccunit.h"

namespace mdf {

  /** \brief Type of conversion formula
   *
   * The type together with the Parameter() function defines
   * the conversion between channel and engineering value.
   *
   */
  enum class ConversionType : uint8_t {
    /** \brief 1:1 conversion. No parameters needed. */
    NoConversion = 0,

    /** \brief Linear conversion. 2 parameters.
     * Eng = Ch * Par(1) + Par(0).
     */
    Linear = 1,

    /** \brief Rational function conversion. 6 parameters.
     *  Eng = (Par(0)*Ch^2 + Par(1)*Ch + Par(2)) /
     *  (Par(3)*Ch^2 + Par(4)*Ch + Par(5))
     */
    Rational = 2,
    Algebraic = 3, ///< Text formula.

    /** \brief Value to value conversion with interpolation.
     * Defined by a list of Key value pairs.
     * Par(n) = key and Par(n+1) value.
     */
    ValueToValueInterpolation = 4,

    /** \brief Value to value conversion without interpolation.
     * Defined by a list of Key value pairs.
     * Par(n) = key and Par(n+1) value.
     */
    ValueToValue = 5,

    /** \brief Value range to value conversion without interpolation.
     * Defined by a list of Key min/max value triplets.
     * Par(3*n) = key min, Par(3*(n+1)) = key max and Par(3*(n+2)) value. Add a default
     * value last, after all the triplets.
     */
    ValueRangeToValue = 6,

    /** \brief Value to text conversion.
     * Defined by a list of key values to text string conversions. This is
     * normally used for enumerated channels.
     * Par(n) value to Ref(n) text. Add a default
     * referenced text last.
     */
    ValueToText = 7,

    /** \brief Value range to text conversion.
     * Defined by a list of key min/max values to text string conversions. This is
     * normally used for enumerated channels.
     * Par(2*n) min key, Par(2(n+1)) max key to Ref(n) value. Add a default
     * referenced text  last.
     */
    ValueRangeToText = 8,

    /** \brief Text to value conversion.
     * Defines a list of text string to value conversion.
     * Ref(n) key to Par(n) value. Add a default value last to the parameter list.
     */
    TextToValue = 9,

    /** \brief Text to text conversion.
      * Defines a list of text string to text conversion.
      * Ref(2*n) key to Ref(2*(n+1)) value.
      * Add a text value last to the parameter list.
      */
    TextToTranslation = 10,

    /** \brief Bitfield to text conversion
     * Currently unsupported conversion.
     */
    BitfieldToText = 11,
    // MDF 3 types
    Polynomial = 30, ///< MDF 3 polynomial conversion.
    Exponential = 31, ///< MDF 3 exponential conversion.
    Logarithmic = 32, ///< MDF 3 logarithmic conversion.
    DateConversion = 33, ///< MDF 3 Date conversion
    TimeConversion = 34 ///< MDF 3 Time conversion
  };

  /** \brief MDF 3 text conversion structure. Not used
   * in MDF 4. Key to text conversion.
   */

  struct TextConversion {
    double value = 0; ///< Key
    std::string text; ///< Text string
  };

  /** \brief MDF 3 range conversion structure. Not used in MDF 4.
   * Key min/max to text conversion
   */

  struct TextRangeConversion {
    double lower = 0; ///< Key min value.
    double upper = 0; ///< Key max value.
    uint32_t link_text = 0; ///< File position of the text value
    std::string text; ///< The text value.
  };

  /** \brief Channel conversion flags.
   *
   */
  namespace CcFlag {
    constexpr uint16_t PrecisionValid = 0x0001; ///< Precision is used.
    constexpr uint16_t RangeValid = 0x0002; ///< Range is used.
    constexpr uint16_t StatusString = 0x0004; ///< Status string flag.
  }  // namespace CcFlag

  /** \brief Defines a channel conversion (CC) block.
   *
   * The channel conversion (CC) block shall convert the channel value to
   * an engineering value. If the CN block doesn't reference any CC block, the
   * engineer and channel values are identical.
   *
   * Depending on the type of conversion (ConversionType), none or more parameters
   * (Parameter()) and none or more text string (Reference()) are used to define
   * the conversion. Check description in ConversionType.
   */

  class IChannelConversion : public IBlock {

  public:
    /**
     * @brief ~IChannelConversion.
     */
    ~IChannelConversion () override = default;

    /**
     * @brief Name.
     * @param name name.
     * @return virtual void.
     */
    virtual void Name ( const std::string& name ); ///< Sets the CC name.
    /**
     * @brief Name.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Name () const; ///< Name.

      /**
       * @brief Description.
       * @param desc desc.
       * @return virtual void.
       */
      virtual void Description ( const std::string& desc ); ///< Sets the description.
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Description () const; ///< Description.

      /**
       * @brief Unit.
       * @param unit unit.
       * @return virtual void.
       */
      virtual void Unit ( const std::string& unit ) = 0; ///< Sets the unit.
    /**
     * @brief Unit.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Unit () const = 0; ///< Unit of measure.
    /**
     * @brief IsUnitValid.
     * @return [ [ nodiscard ] ] virtual bool.
     */
    [ [ nodiscard ] ] virtual bool IsUnitValid () const =
      0; ///< True if unit exist.

      /** \brief Sets the channel conversion unit.
       * @param unit CC unit object.
       */
      /**
       * @brief SetCcUnit.
       * @param unit unit.
       * @return virtual void.
       */
      virtual void SetCcUnit ( const CcUnit& unit );
      /** \brief Retrieves the channel conversion unit.
       * @param unit Receives the CC unit object.
       */
      /**
       * @brief GetCcUnit.
       * @param unit unit.
       * @return virtual void.
       */
      virtual void GetCcUnit ( CcUnit& unit ) const;

      /**
       * @brief Type.
       * @param type type.
       * @return virtual void.
       */
      virtual void Type ( ConversionType type ) = 0; ///< Sets the conversion type.
    /**
     * @brief Type.
     * @return [ [ nodiscard ] ] virtual ConversionType.
     */
    [ [ nodiscard ] ] virtual ConversionType Type () const =
      0; ///< Conversion type.

    /**
     * @brief IsDecimalUsed.
     * @return [ [ nodiscard ] ] virtual bool.
     */
    [ [ nodiscard ] ] virtual bool IsDecimalUsed ()
      const = 0; ///< True if decimal is used.
      /** \brief Sets number of decimals.
       * @param decimals Number of decimals.
       */
      /**
       * @brief Decimals.
       * @param decimals decimals.
       * @return virtual void.
       */
      virtual void Decimals ( uint8_t decimals );
    /**
     * @brief Decimals.
     * @return [ [ nodiscard ] ] virtual uint8_t.
     */
    [ [ nodiscard ] ] virtual uint8_t Decimals () const =
      0; ///< Number of decimals.

      /** \brief Creates an inverse conversion block.
       * @return Inverse conversion block.
       */
    /**
     * @brief CreateInverse.
     * @return [ [ nodiscard ] ] virtual IChannelConversion*.
     */
    [ [ nodiscard ] ] virtual IChannelConversion* CreateInverse ();

      /** \brief Returns the inverse conversion block. Seldom in use.
       * @return Inverse conversion block or nullptr.
       */
    /**
     * @brief Inverse.
     * @return [ [ nodiscard ] ] virtual IChannelConversion*.
     */
    [ [ nodiscard ] ] virtual IChannelConversion* Inverse () const;

      /** \brief Sets the conversion range.
       * @param min Minimum value.
       * @param max Maximum value.
       */
      /**
       * @brief Range.
       * @param min min.
       * @param max max.
       * @return virtual void.
       */
      virtual void Range ( double min, double max );
    /**
     * @brief Range.
     * @return [ [ nodiscard ] ] virtual std::optional<std::pair<double, double>>.
     */
    [ [ nodiscard ] ] virtual std::optional<std::pair<double, double>> Range ()
      const; ///< Returns the range if it exists.

      /** \brief Sets CC flags.
       * @param flags Flags from the CcFlag namespace.
       */
      /**
       * @brief Flags.
       * @param flags flags.
       * @return virtual void.
       */
      virtual void Flags ( uint16_t flags );
    /**
     * @brief Flags.
     * @return [ [ nodiscard ] ] virtual uint16_t.
     */
    [ [ nodiscard ] ] virtual uint16_t Flags () const; ///< Returns CcFlag

      /** \brief Creates a meta-data (MD) block.
       * @return Meta-data block.
       */
    /**
     * @brief CreateMetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData ();

      /** \brief Returns the meta-data block.
       * @return Meta-data block or nullptr.
       */
    /**
     * @brief MetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* MetaData () const;

      /** \brief Sets the CC comment block.
       * @param cc_comment CC comment object.
       */
      /**
       * @brief SetCcComment.
       * @param cc_comment cc_comment.
       */
      void SetCcComment ( const CcComment& cc_comment );
      /** \brief Retrieves the CC comment block.
       * @param cc_comment Receives the CC comment object.
       */
      /**
       * @brief GetCcComment.
       * @param cc_comment cc_comment.
       */
      void GetCcComment ( CcComment& cc_comment ) const;

      /** \brief Sets the formula string.
       * @param formula Formula text.
       */
      /**
       * @brief Formula.
       * @param formula formula.
       * @return virtual void.
       */
      virtual void Formula ( const std::string& formula );
      /** \brief Returns formula string. */
    [ [ nodiscard ] ] virtual const std::string& Formula () const;

      /** \brief Returns number of parameters in the block. */
    [ [ nodiscard ] ] uint16_t NofParameters () const;

      /** \brief Sets a floating point parameter value.
       *
       * @param index Parameter index to set.
       * @param parameter Value to set.
       */
      /**
       * @brief Parameter.
       * @param index index.
       * @param parameter parameter.
       */
      void Parameter ( uint16_t index, double parameter );

      /** \brief Returns the parameter value.
       *
       * @param index Parameter index.
       * @return Floating point parameter value.
       */
    /**
     * @brief Parameter.
     * @param index index.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double Parameter ( uint16_t index ) const;

      /** \brief Returns the parameter as a bit field (uint64_t).
       *
       * @param index Parameter index.
       * @return Unsigned integer parameter value.
       */
    /**
     * @brief ParameterUint.
     * @param index index.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t ParameterUint ( uint16_t index ) const;
      /** \brief Sets an unsigned integer parameter value.
       *
       * @param index Parameter index to set.
       * @param parameter Value to set.
       */
      /**
       * @brief ParameterUint.
       * @param index index.
       * @param parameter parameter.
       */
      void ParameterUint ( uint16_t index, uint64_t parameter );

      /** \brief Number of references in the block. */
    [ [ nodiscard ] ] virtual uint16_t NofReferences () const;

      /** \brief Sets text reference (TX) block.
       *
       * @param index Index of the text block (TX).
       * @param text Text content of the TX block.
       */
      /**
       * @brief Reference.
       * @param index index.
       * @param text text.
       * @return virtual void.
       */
      virtual void Reference ( uint16_t index, const std::string& text );

      /** \brief Returns the reference string by its index.
       * @param index Reference index.
       * @return Reference text.
       */
    /**
     * @brief Reference.
     * @param index index.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Reference ( uint16_t index ) const;

      /** \brief Sets the CN block data type.
       *
       * Some of the conversion methods need to know the CN channels data type.
       * @param channel_data_type Channel data type.
       */
      /**
       * @brief ChannelDataType.
       * @param channel_data_type channel_data_type.
       */
      void ChannelDataType ( uint8_t channel_data_type );

      /** \brief Converts a channel value to an engineering (scaled) value.
       *
       * Converts the channel value to a scaled value.
       * @tparam T Channel data type.
       * @tparam V Engineering value data type.
       * @param channel_value The channel value.
       * @param eng_value The scaled engineering value.
       * @return True if the conversion is valid.
       */
      template <typename T, typename V>
      /**
       * @brief Convert.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return bool.
       */
      bool Convert ( const T& channel_value, V& eng_value ) const;

      /** \brief Converts a channel value to an engineering string value.
       *
       * Converts a channel value to an scaled value converted to a string. This
       * function is typical used when presenting data in GUI.
       * @tparam T Channel data type
       * @tparam V String type.
       * @param channel_value The channel value.
       * @param eng_value The output string.
       * @return True if the conversion is valid.
       */
      template <typename T, typename V = std::string>
      /**
       * @brief Convert.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return bool.
       */
      bool Convert ( const T& channel_value, std::string& eng_value ) const;

      /** \brief Convert from string to double with full precision */
      template <typename T = std::string, typename V = double>
      /**
       * @brief Convert.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return bool.
       */
      bool Convert ( const std::string& channel_value, double& eng_value ) const;

      /** \brief Converts from string to string. */
      template <typename T = std::string, typename V = std::string>
      /**
       * @brief Convert.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return bool.
       */
      bool Convert ( const std::string& channel_value,
      std::string& eng_value ) const {
        if ( Type () == ConversionType::TextToTranslation ) {
          /**
           * @brief ConvertTextToTranslation.
           * @param channel_value channel_value.
           * @param eng_value eng_value.
           */
          ConvertTextToTranslation ( channel_value, eng_value );
      } else if ( Type () == ConversionType::NoConversion ) {
        eng_value = channel_value;
        } else {
          return false;
      }

      return true;
      }

    protected:
      uint16_t nof_values_ = 0; ///< Number of parameter values (MDF3).

      /** \brief List of floating point constants. */
      using ParameterList = std::vector<std::variant<uint64_t, double>>;

      ParameterList value_list_; ///< List of parameters.
      uint8_t channel_data_type_ =
      0;  ///< The channels data type. Needed by some conversions

      // The formula and conversion list is used in MDF 3 while MDF4
      // uses the reference list.
      mutable std::string formula_; ///< Formula string (MDF3).
      std::vector<TextConversion> text_conversion_list_; ///< MDF3
      std::vector<TextRangeConversion> text_range_conversion_list_; ///< MDF3

    /**
     * @brief IsChannelInteger.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsChannelInteger ()
      const; ///< Returns true if channel is an integer.
    /**
     * @brief IsChannelFloat.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsChannelFloat ()
      const; ///< Returns true if the channel is a float.

      /**
       * @brief ConvertLinear.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertLinear ( double channel_value, double& eng_value )
      const; ///< Linear conversion.
      /**
       * @brief ConvertRational.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertRational ( double channel_value, double& eng_value )
      const; ///< Rational conversion.
      /**
       * @brief ConvertAlgebraic.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertAlgebraic ( double channel_value, double& eng_value )
      const; ///< Algebraic conversion.
      /**
       * @brief ConvertValueToValueInterpolate.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertValueToValueInterpolate ( double channel_value,
      double& eng_value ) const; ///< Value to value interpolation conversion.
      /**
       * @brief ConvertValueToValue.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertValueToValue ( double channel_value,
      double& eng_value ) const; ///< Value to value conversion.
      /**
       * @brief ConvertValueRangeToValue.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertValueRangeToValue ( double channel_value,
      double& eng_value ) const; ///< Value range to value conversion.

      /**
       * @brief ConvertValueToText.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertValueToText ( double channel_value,
      std::string& eng_value ) const; ///< Value to text conversion.
      /**
       * @brief ConvertValueRangeToText.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertValueRangeToText ( double channel_value,
      std::string& eng_value ) const; ///< Value range to text value.
      /**
       * @brief ConvertTextToValue.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertTextToValue ( const std::string& channel_value,
      double& eng_value ) const; ///< Text to value conversion.
      /**
       * @brief ConvertTextToTranslation.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertTextToTranslation ( const std::string& channel_value,
      std::string& eng_value ) const; ///< Text to text conversion.
      /**
       * @brief ConvertPolynomial.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       * @return virtual bool.
       */
      virtual bool ConvertPolynomial ( double channel_value, double& eng_value )
      const; ///< Polynomial conversion (MDF3).
      /**
       * @brief ConvertLogarithmic.
       * @param channel_value channel_value.
       * @param MDF3 MDF3.
       * @return virtual bool.
       */
      virtual bool ConvertLogarithmic ( double channel_value,
      /**
       * @brief conversion.
       * @param MDF3 MDF3.
       * @return double& eng_value ) ; ///< Logarithmic.
       */
      double& eng_value ) const; ///< Logarithmic conversion (MDF3).
      /**
       * @brief ConvertExponential.
       * @param channel_value channel_value.
       * @param MDF3 MDF3.
       * @return virtual bool.
       */
      virtual bool ConvertExponential ( double channel_value,
      /**
       * @brief conversion.
       * @param MDF3 MDF3.
       * @return double& eng_value ) ; ///< Exponential.
       */
      double& eng_value ) const; ///< Exponential conversion (MDF3).
  };

  template <typename T, typename V>
  /**
   * @brief IChannelConversion::Convert.
   * @param channel_value channel_value.
   * @param eng_value eng_value.
   * @return inline bool.
   */
  inline bool IChannelConversion::Convert ( const T& channel_value,
  V& eng_value ) const {
    bool valid = false;
    double value = 0.0;

    switch ( Type () ) {
      case ConversionType::Linear: {
        /**
         * @brief ConvertLinear.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertLinear ( static_cast<double> ( channel_value ), value );
        /**
         * @brief static_cast<V>.
         * @param value value.
         * @return eng_value =.
         */
        eng_value = static_cast<V> ( value );
        break;
        }

        case ConversionType::Rational: {
          /**
           * @brief ConvertRational.
           * @param value value.
           * @return valid =.
           */
          valid = ConvertRational ( static_cast<double> ( channel_value ), value );
          /**
           * @brief static_cast<V>.
           * @param value value.
           * @return eng_value =.
           */
          eng_value = static_cast<V> ( value );
          break;
      }

      case ConversionType::Algebraic: {
        /**
         * @brief ConvertAlgebraic.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertAlgebraic ( static_cast<double> ( channel_value ), value );
        /**
         * @brief static_cast<V>.
         * @param value value.
         * @return eng_value =.
         */
        eng_value = static_cast<V> ( value );
        break;
        }

        case ConversionType::ValueToValueInterpolation: {
          /**
           * @brief ConvertValueToValueInterpolate.
           * @param value value.
           * @return valid =.
           */
          valid = ConvertValueToValueInterpolate (
          /**
           * @brief static_cast<double>.
           * @param value value.
           */
          static_cast<double> ( channel_value ), value );
          /**
           * @brief static_cast<V>.
           * @param value value.
           * @return eng_value =.
           */
          eng_value = static_cast<V> ( value );
          break;
      }

      case ConversionType::ValueToValue: {
        /**
         * @brief ConvertValueToValue.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertValueToValue ( static_cast<double> ( channel_value ), value );
        /**
         * @brief static_cast<V>.
         * @param value value.
         * @return eng_value =.
         */
        eng_value = static_cast<V> ( value );
        break;
        }

        case ConversionType::ValueRangeToValue: {
          valid =
          /**
           * @brief ConvertValueRangeToValue.
           * @param value value.
           */
          ConvertValueRangeToValue ( static_cast<double> ( channel_value ), value );
          /**
           * @brief static_cast<V>.
           * @param value value.
           * @return eng_value =.
           */
          eng_value = static_cast<V> ( value );
          break;
      }

      case ConversionType::ValueToText: {
        std::string text;
        /**
         * @brief ConvertValueToText.
         * @param text text.
         * @return valid =.
         */
        valid = ConvertValueToText ( static_cast<double> ( channel_value ), text );
        /**
         * @brief s.
         * @param text text.
         * @return std::istringstream.
         */
        std::istringstream s ( text );
        s >> eng_value;
        break;
        }

        case ConversionType::ValueRangeToText: {
          std::string text;
          valid =
          /**
           * @brief ConvertValueRangeToText.
           * @param text text.
           */
          ConvertValueRangeToText ( static_cast<double> ( channel_value ), text );
          /**
           * @brief s.
           * @param text text.
           * @return std::istringstream.
           */
          std::istringstream s ( text );
          s >> eng_value;
          break;
      }

      case ConversionType::Polynomial: {
        /**
         * @brief ConvertPolynomial.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertPolynomial ( static_cast<double> ( channel_value ), value );
        /**
         * @brief static_cast<V>.
         * @param value value.
         * @return eng_value =.
         */
        eng_value = static_cast<V> ( value );
        break;
        }

        case ConversionType::Exponential: {
          /**
           * @brief ConvertExponential.
           * @param value value.
           * @return valid =.
           */
          valid = ConvertExponential ( static_cast<double> ( channel_value ), value );
          /**
           * @brief static_cast<V>.
           * @param value value.
           * @return eng_value =.
           */
          eng_value = static_cast<V> ( value );
          break;
      }

      case ConversionType::Logarithmic: {
        /**
         * @brief ConvertLogarithmic.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertLogarithmic ( static_cast<double> ( channel_value ), value );
        /**
         * @brief static_cast<V>.
         * @param value value.
         * @return eng_value =.
         */
        eng_value = static_cast<V> ( value );
        break;
        }

        case ConversionType::NoConversion:
        default: {
          /**
           * @brief static_cast<V>.
           * @param channel_value channel_value.
           * @return eng_value =.
           */
          eng_value = static_cast<V> ( channel_value );
          valid = true;
          break;
      }
      }

      return valid;
  }

  template <typename T, typename V>
  /**
   * @brief IChannelConversion::Convert.
   * @param channel_value channel_value.
   * @param eng_value eng_value.
   * @return inline bool.
   */
  inline bool IChannelConversion::Convert ( const T& channel_value,
  std::string& eng_value ) const {
    bool valid = false;
    double value = 0.0;

    switch ( Type () ) {
      case ConversionType::Linear: {
        /**
         * @brief ConvertLinear.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertLinear ( static_cast<double> ( channel_value ), value );
        eng_value =
        /**
         * @brief MdfHelper::FormatDouble.
         * @param value value.
         */
        MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
        break;
        }

        case ConversionType::Rational: {
          /**
           * @brief ConvertRational.
           * @param value value.
           * @return valid =.
           */
          valid = ConvertRational ( static_cast<double> ( channel_value ), value );
          eng_value =
          /**
           * @brief MdfHelper::FormatDouble.
           * @param value value.
           */
          MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
          break;
      }

      case ConversionType::Algebraic: {
        /**
         * @brief ConvertAlgebraic.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertAlgebraic ( static_cast<double> ( channel_value ), value );
        eng_value =
        /**
         * @brief MdfHelper::FormatDouble.
         * @param value value.
         */
        MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
        break;
        }

        case ConversionType::ValueToValueInterpolation: {
          /**
           * @brief ConvertValueToValueInterpolate.
           * @param value value.
           * @return valid =.
           */
          valid = ConvertValueToValueInterpolate (
          /**
           * @brief static_cast<double>.
           * @param value value.
           */
          static_cast<double> ( channel_value ), value );
          eng_value =
          /**
           * @brief MdfHelper::FormatDouble.
           * @param value value.
           */
          MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
          break;
      }

      case ConversionType::ValueToValue: {
        /**
         * @brief ConvertValueToValue.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertValueToValue ( static_cast<double> ( channel_value ), value );
        eng_value =
        /**
         * @brief MdfHelper::FormatDouble.
         * @param value value.
         */
        MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
        break;
        }

        case ConversionType::ValueRangeToValue: {
          valid =
          /**
           * @brief ConvertValueRangeToValue.
           * @param value value.
           */
          ConvertValueRangeToValue ( static_cast<double> ( channel_value ), value );
          eng_value =
          /**
           * @brief MdfHelper::FormatDouble.
           * @param value value.
           */
          MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
          break;
      }

      case ConversionType::ValueToText: {
        valid =
        /**
         * @brief ConvertValueToText.
         * @param eng_value eng_value.
         */
        ConvertValueToText ( static_cast<double> ( channel_value ), eng_value );
        break;
        }

        case ConversionType::ValueRangeToText: {
          /**
           * @brief ConvertValueRangeToText.
           * @param eng_value eng_value.
           * @return valid =.
           */
          valid = ConvertValueRangeToText ( static_cast<double> ( channel_value ),
          eng_value );
          break;
      }

      case ConversionType::Polynomial: {
        /**
         * @brief ConvertPolynomial.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertPolynomial ( static_cast<double> ( channel_value ), value );
        eng_value =
        /**
         * @brief MdfHelper::FormatDouble.
         * @param value value.
         */
        MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
        break;
        }

        case ConversionType::Exponential: {
          /**
           * @brief ConvertExponential.
           * @param value value.
           * @return valid =.
           */
          valid = ConvertExponential ( static_cast<double> ( channel_value ), value );
          eng_value =
          /**
           * @brief MdfHelper::FormatDouble.
           * @param value value.
           */
          MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
          break;
      }

      case ConversionType::Logarithmic: {
        /**
         * @brief ConvertLogarithmic.
         * @param value value.
         * @return valid =.
         */
        valid = ConvertLogarithmic ( static_cast<double> ( channel_value ), value );
        eng_value =
        /**
         * @brief MdfHelper::FormatDouble.
         * @param value value.
         */
        MdfHelper::FormatDouble ( value, IsDecimalUsed () ? Decimals () : 6 );
        break;
        }

        case ConversionType::NoConversion:
        default: {
          /**
           * @brief MdfHelper::FormatDouble.
           * @return eng_value =.
           */
          eng_value = MdfHelper::FormatDouble ( static_cast<double> ( channel_value ),
          /**
           * @brief IsDecimalUsed.
           */
          IsDecimalUsed () ? Decimals () : 6 );
          valid = true;
          break;
      }
      }

      return valid;
  }

  template <typename T, typename V>
  /**
   * @brief IChannelConversion::Convert.
   * @param channel_value channel_value.
   * @param eng_value eng_value.
   * @return bool.
   */
  bool IChannelConversion::Convert ( const std::string& channel_value,
  double& eng_value ) const {
    if ( Type () == ConversionType::TextToValue ) {
      /**
       * @brief ConvertTextToValue.
       * @param channel_value channel_value.
       * @param eng_value eng_value.
       */
      ConvertTextToValue ( channel_value, eng_value );
      } else if ( Type () == ConversionType::NoConversion ) {
        /**
         * @brief std::stod.
         * @param channel_value channel_value.
         * @return eng_value =.
         */
        eng_value = std::stod ( channel_value );
    } else {
      return false;
      }

      return true;
  }

  }  // namespace mdf