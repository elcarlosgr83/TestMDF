/**
 * @file MdfChannelConversion.h
 * @brief Wrapper for MDF channel conversion definitions.
 *
 * The `MdfChannelConversion` wrapper exposes conversion metadata for a channel.
 * It provides access to conversion name, description, unit, precision, range,
 * flags, references and parameters.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <string>

#include "MdfMetaData.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfChannelConversion
   * @brief Channel conversion wrapper.
   */
  class MdfChannelConversion {
  private:
    mdf::IChannelConversion* conversion;

  public:
    /**
     * @brief Wrap an existing channel conversion handle.
     * @param conversion Low-level conversion pointer.
     */
    MdfChannelConversion ( mdf::IChannelConversion* conversion )
      : conversion ( conversion ) {
      if ( conversion == nullptr )
      { throw std::runtime_error ( "MdfChannelConversion Init failed" ); }
    }

    /**
     * @brief Wrap a const channel conversion handle.
     * @param conversion Low-level const conversion pointer.
     */
    MdfChannelConversion ( const mdf::IChannelConversion* conversion )
      : MdfChannelConversion ( const_cast<mdf::IChannelConversion*> ( conversion ) ) {
    }

    ~MdfChannelConversion () { conversion = nullptr; }

    /**
     * @brief Returns the conversion index.
     * @return Conversion index.
     */
    int64_t GetIndex () const { return MdfChannelConversionGetIndex ( conversion ); }

    /**
     * @brief Returns the conversion name.
     * @return Conversion name.
     */
    std::string GetName () const {
      std::string str ( MdfChannelConversionGetName ( conversion, nullptr ) + 1,
                        '\0' );
      str.resize ( MdfChannelConversionGetName ( conversion, str.data () ) );
      return str;
    }

    /**
     * @brief Set the conversion name.
     * @param name Name string.
     */
    void SetName ( const char* name ) {
      MdfChannelConversionSetName ( conversion, name );
    }

    /**
     * @brief Returns the conversion description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfChannelConversionGetDescription ( conversion,
                        nullptr ) + 1, '\0' );
      str.resize ( MdfChannelConversionGetDescription ( conversion, str.data () ) );
      return str;
    }

    /**
     * @brief Set the conversion description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) {
      MdfChannelConversionSetDescription ( conversion, desc );
    }

    /**
     * @brief Returns the conversion unit.
     * @return Unit string.
     */
    std::string GetUnit () const {
      std::string str ( MdfChannelConversionGetUnit ( conversion, nullptr ) + 1,
                        '\0' );
      str.resize ( MdfChannelConversionGetUnit ( conversion, str.data () ) );
      return str;
    }

    /**
     * @brief Set the conversion unit.
     * @param unit Unit string.
     */
    void SetUnit ( const char* unit ) {
      MdfChannelConversionSetUnit ( conversion, unit );
    }

    /**
     * @brief Returns the conversion type.
     * @return Conversion type enum.
     */
    ConversionType GetType () const {
      return MdfChannelConversionGetType ( conversion );
    }

    /**
     * @brief Set the conversion type.
     * @param type Conversion type.
     */
    void SetType ( ConversionType type ) {
      MdfChannelConversionSetType ( conversion, type );
    }

    /**
     * @brief Returns whether precision is used.
     * @return `true` when precision is used.
     */
    bool IsPrecisionUsed () {
      return MdfChannelConversionIsPrecisionUsed ( conversion );
    }

    /**
     * @brief Returns the conversion precision.
     * @return Precision value.
     */
    uint8_t GetPrecision () const {
      return MdfChannelConversionGetPrecision ( conversion );
    }

    /**
     * @brief Returns whether the conversion range is used.
     * @return `true` when range is used.
     */
    bool IsRangeUsed () { return MdfChannelConversionIsRangeUsed ( conversion ); }

    /**
     * @brief Returns the conversion range minimum.
     * @return Minimum range value.
     */
    double GetRangeMin () const {
      return MdfChannelConversionGetRangeMin ( conversion );
    }

    /**
     * @brief Returns the conversion range maximum.
     * @return Maximum range value.
     */
    double GetRangeMax () const {
      return MdfChannelConversionGetRangeMax ( conversion );
    }

    /**
     * @brief Set the conversion range.
     * @param min Minimum range value.
     * @param max Maximum range value.
     */
    void SetRange ( double min, double max ) {
      MdfChannelConversionSetRange ( conversion, min, max );
    }

    /**
     * @brief Returns the conversion flags.
     * @return Flags bitmask.
     */
    uint16_t GetFlags () const { return MdfChannelConversionGetFlags ( conversion ); }

    /**
     * @brief Returns the inverse conversion.
     * @return Inverse channel conversion wrapper.
     */
    const MdfChannelConversion GetInverse () const {
      return MdfChannelConversionGetInverse ( conversion );
    }

    /**
     * @brief Returns the metadata wrapper for this conversion.
     * @return `MdfMetaData` wrapper.
     */
    const MdfMetaData GetMetadata () const {
      return MdfChannelConversionGetMetaData ( conversion );
    }

    /**
     * @brief Returns a conversion reference string.
     * @param index Reference index.
     * @return Reference string.
     */
    std::string GetReference ( uint16_t index ) const {
      std::string str ( MdfChannelConversionGetReference ( conversion, index,
                        nullptr ) + 1, '\0' );
      str.resize ( MdfChannelConversionGetReference ( conversion, index,
                   str.data () ) );
      return str;
    }

    /**
     * @brief Set a conversion reference string.
     * @param index Reference index.
     * @param ref Reference text.
     */
    void SetReference ( uint16_t index, const char* ref ) {
      MdfChannelConversionSetReference ( conversion, index, ref );
    }

    /**
     * @brief Returns a conversion parameter as double.
     * @param index Parameter index.
     * @return Parameter value.
     */
    double GetParameter ( uint16_t index ) const {
      return MdfChannelConversionGetParameterAsDouble ( conversion, index );
    }

    /**
     * @brief Returns a conversion parameter as unsigned integer.
     * @param index Parameter index.
     * @return Parameter value.
     */
    uint64_t GetParameterUint ( uint16_t index ) const {
      return MdfChannelConversionGetParameterAsUInt64 ( conversion, index );
    }

    /**
     * @brief Set a conversion parameter as double.
     * @param index Parameter index.
     * @param param Parameter value.
     */
    void SetParameter ( uint16_t index, double param ) {
      MdfChannelConversionSetParameterAsDouble ( conversion, index, param );
    }

    /**
     * @brief Set a conversion parameter as unsigned integer.
     * @param index Parameter index.
     * @param param Parameter value.
     */
    void SetParameter ( uint16_t index, uint64_t param ) {
      MdfChannelConversionSetParameterAsUInt64 ( conversion, index, param );
    }

    /**
     * @brief Create an inverse conversion wrapper.
     * @return Inverse conversion wrapper.
     */
    MdfChannelConversion CreateInverse () {
      return MdfChannelConversionCreateInverse ( conversion );
    }
  };
}  // namespace MdfLibrary