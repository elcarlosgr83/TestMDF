/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <string>
#include <vector>

#include "mdf/ichannel.h"
#include "mdf/isampleobserver.h"


namespace mdf {

  /** \brief The channel observer object shall hold all samples for a channel.
   *
   * The main purpose for a channel observer is to store all channel samples for
   * a channel. This object is used when reading data from a MDF file.
   */

  class IChannelObserver : public ISampleObserver {
  protected:
    const IChannel& channel_; ///< Reference to the channel (CN) block.
    bool read_vlsd_data_ = true; ///< Defines if the VLSD bytes should be read.

    std::vector<uint64_t> offset_list_; ///< Only used for VLSD channels.
    std::vector<bool> valid_list_; ///< List of valid samples.

    /**
     * @brief GetSampleUnsigned.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return virtual bool.
     */
    virtual bool GetSampleUnsigned ( uint64_t sample, uint64_t& value,
                                     uint64_t array_index )
    const = 0; ///< Returns a unsigned  sample value.
    /**
     * @brief GetSampleSigned.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return virtual bool.
     */
    virtual bool GetSampleSigned ( uint64_t sample, int64_t& value,
                                   uint64_t array_index )
    const = 0; ///< Returns a signed sample value.
    /**
     * @brief GetSampleFloat.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return virtual bool.
     */
    virtual bool GetSampleFloat ( uint64_t sample, double& value,
                                  uint64_t array_index )
    const = 0; ///< Returns a float sample value.
    /**
     * @brief GetSampleText.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return virtual bool.
     */
    virtual bool GetSampleText ( uint64_t sample, std::string& value,
                                 uint64_t array_index )
    const = 0; ///< Returns a string sample value.
    /**
     * @brief GetSampleByteArray.
     * @param sample sample.
     * @param value value.
     * @return virtual bool.
     */
    virtual bool GetSampleByteArray ( uint64_t sample, std::vector<uint8_t>& value )
    const = 0; ///< Returns a byte array sample value.

  public:
    /**
     * @brief IChannelObserver.
     * @param dataGroup dataGroup.
     * @param channel channel.
     * @return explicit.
     */
    explicit IChannelObserver ( const IDataGroup& dataGroup,
                                const IChannel& channel ); ///< Constructor.

    /**
     * @brief ~IChannelObserver.
     */
    ~IChannelObserver () override = default; ///< Default destructor.

    /**
     * @brief IChannelObserver.
     */
    IChannelObserver () = delete;
    /**
     * @brief IChannelObserver.
     */
    IChannelObserver ( const IChannelObserver& ) = delete;
    /**
     * @brief IChannelObserver.
     */
    IChannelObserver ( IChannelObserver&& ) = delete;
    /**
     * @brief operator=.
     * @return IChannelObserver&.
     */
    IChannelObserver& operator= ( const IChannelObserver& ) = delete;
    /**
     * @brief operator=.
     * @return IChannelObserver&.
     */
    IChannelObserver& operator= ( IChannelObserver&& ) = delete;

    /**
     * @brief NofSamples.
     * @return [ [ nodiscard ] ] virtual uint64_t.
     */
    [ [ nodiscard ] ] virtual uint64_t NofSamples ()
      const = 0; ///< Returns number of samples.

    /**
     * @brief Name.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Name () const; ///< Channel name

    /**
     * @brief Unit.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Unit () const; ///< Channel unit.

      /** \brief Returns the channel object.
       *
       * Returns the channel object associated with this observer. The channel
       * is mostly needed to check if the channel is an array channel. Array
       * channels are seldom used and are complex to handle.
       * @return Returns the channel object.
       */
    /**
     * @brief Channel.
     * @return [ [ nodiscard ] ] IChannel&.
     */
    [ [ nodiscard ] ] const IChannel& Channel () const;

    /**
     * @brief IsMaster.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsMaster ()
      const; ///< True if this is the master channel.

    /**
     * @brief IsArray.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsArray ()
      const; ///< True if this channel is an array channel.

      /** \brief Returns a shape vector that describes an array dimension.
       *
       * This function is used to size an array in an external library. The Eigen
       * and XTensor C++ libraries are typical
       *
       * @return Shape vector that describes an array dimension.
       */
    /**
     * @brief Shape.
     * @return [ [ nodiscard ] ] std::vector<uint64_t>.
     */
    [ [ nodiscard ] ] std::vector<uint64_t> Shape () const;

      /** \brief Property interface that defines if the VLSD raw data should be read
       * or not.
       *
       * Reading VLSD raw data may fail if there is no room for the bytes in the
       * primary memory. Normally is this property normally set to true but if set
       * to false, only the offset into the VLSD block is read. This call should
       * be followed buy one or more call to the MdfWriter::ReadVlsdData() function.
       * By this, only partial samples can be read in and thus saving primary
       * memory.
       * @param read_vlsd_data Set to false if VLSD bytes shouldn't be read.
       */
      /**
       * @brief ReadVlsdData.
       * @param read_vlsd_data read_vlsd_data.
       */
      void ReadVlsdData ( bool read_vlsd_data );

      /** \brief Returns the read VLSD bytes property. */
    [ [ nodiscard ] ] bool ReadVlsdData () const { return read_vlsd_data_; }

    /** \brief If this is an array channel, this function returns the array size.
     *
     * Returns the array size if the channel is an array channel. The function
       * returns 1 if the channel is not an array channel.
       * @return Number of elements in the array channel or 1 for scalar channels.
       */
    /**
     * @brief ArraySize.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t ArraySize () const;

      /** \brief Returns the channel value for a sample.
       *
       * Returns the (unscaled) so-called channel value for a specific sample.
       * @tparam V Type of value
       * @param sample Sample number (0..).
       * @param value The channel value.
       * @param array_index Optional array index if the channel is an array.
       * @return True if value is valid.
       */
      template <typename V>
      /**
       * @brief GetChannelValue.
       * @param sample sample.
       * @param value value.
       * @param array_index array_index.
       * @return bool.
       */
      bool GetChannelValue ( uint64_t sample, V& value,
      uint64_t array_index = 0 ) const;

      /** \brief Simple function that returns all non-scaled samples.
       *
       * Returns all non-scaled sample values. Do not use this function for array
       * channels. Use the GetChannelValues() function for array values.
       *
       * @tparam V Type of values
       * @param values The destination sample list.
       * @return Returns a list of valid booleans.
       */
      template<typename V>
      /**
       * @brief GetChannelSamples.
       * @param values values.
       * @return std::vector<bool>.
       */
      std::vector<bool> GetChannelSamples ( std::vector<V>& values ) const;

      /** \brief Returns a vector of array channel values for a specific sample.
       *
       * The function is intended to be used on channel arrays. It returns all
       * scaled array values for a sample. Note that the valid flags are return
       * by the GetValidList() function.
       *
       * The values vector doesn't need to be sized.
       *
       * If used on non-array channels, it returns a vector of one values.
       * @tparam V Type of value
       * @param sample Sample index.
       * @param values The destination vector of values.
       * @return Returns a vector of valid booleans.
       */
      template<typename V>
      /**
       * @brief GetChannelValues.
       * @param sample sample.
       * @param values values.
       * @return std::vector<bool>.
       */
      std::vector<bool> GetChannelValues ( uint64_t sample,
      std::vector<V>& values ) const;

      /** \brief Returns the engineering value for a specific value.
       *
       * Returns the engineering (scaled) value for a specific value.
       * @tparam V Type of return value
       * @param sample Sample number (0..).
       * @param value The return value.
       * @param array_index Optional array index if the channel is an array.
       * @return True if the value is valid.
       */
      template <typename V>
      /**
       * @brief GetEngValue.
       * @param sample sample.
       * @param value value.
       * @param array_index array_index.
       * @return bool.
       */
      bool GetEngValue ( uint64_t sample, V& value, uint64_t array_index = 0 ) const;

      /** \brief Simple function that returns all scaled samples.
       *
       * Returns all scaled sample values. Do not use this function for array
       * channels. Use the GetChannelValues() function for array values.
       *
       * @tparam V Type of values
       * @param values The destination sample list.
       * @return Returns a list of valid booleans.
       */
      template<typename V>
      /**
       * @brief GetEngSamples.
       * @param values values.
       * @return std::vector<bool>.
       */
      std::vector<bool> GetEngSamples ( std::vector<V>& values ) const;

      /** \brief Returns a vector of array values for a specific sample.
       *
       * The function is intended to be used on channel arrays. It returns all
       * scaled array values for a sample. Note that the valid flags are return
       * by the GetValidList
       *
       * If used on non-array channels, the value vector is of size 1.
       * @tparam V Type of value
       * @param sample Sample index.
       * @param values List of returning array scaled values.
       * @return Returns a list of valid/invalid flags (boolean).
       */
      template<typename V>
      /**
       * @brief GetEngValues.
       * @param sample sample.
       * @param values values.
       * @return std::vector<bool>.
       */
      std::vector<bool> GetEngValues ( uint64_t sample,
      std::vector<V>& values ) const;

      /** \brief Support function that convert a sample value to a user friendly string
       *
       * Function that convert a sample to a user friendly string. For non-array samples,
       * the function is the same as GetChannelValue but for array sample a JSON array
       * string is returned.
       * @param sample Sample index
       * @return JSON formatted string
       */
    /**
     * @brief EngValueToString.
     * @param sample sample.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string EngValueToString ( uint64_t sample ) const;

      /** \brief Returns the sample to VLSD offset list.
       *
       * This VLSD offset list is only needed when setting the ReadVLSDData()
       * property to false. By only reading the offset list, the VLSD bytes can be
       * read later sample by sample or as a range of VLSD bytes. This read
       * saves primary memory and is much faster when only some samples are needed.
       * @return Reference to the VLSD sample offset list.
       */
    /**
     * @brief GetOffsetList.
     * @return [ [ nodiscard ] ] std::vector<uint64_t>&.
     */
    [ [ nodiscard ] ] const std::vector<uint64_t>& GetOffsetList () const {
        return offset_list_;
    }

    /** \brief Returns the sample validity list.
     *
     * Each entry in the vector corresponds to whether a sample is valid.
     * @return Reference to the valid sample list.
     */
    /**
     * @brief GetValidList.
     * @return [ [ nodiscard ] ] std::vector<bool>&.
     */
    [ [ nodiscard ] ] const std::vector<bool>& GetValidList () const {
        return valid_list_;
    }

  };

  template <typename V>
  /**
   * @brief IChannelObserver::GetChannelValue.
   * @param sample sample.
   * @param value value.
   * @param array_index array_index.
   * @return bool.
   */
  bool IChannelObserver::GetChannelValue ( uint64_t sample, V& value,
  uint64_t array_index ) const {
    bool valid = false;
    value = {};

    switch ( channel_.DataType () ) {
      case ChannelDataType::CanOpenDate:
      case ChannelDataType::CanOpenTime: {
        // All times are stored as ns since 1970 (uint64_t)
        uint64_t v = 0;  // ns since 1970
        /**
         * @brief GetSampleUnsigned.
         * @param sample sample.
         * @param v v.
         * @param array_index array_index.
         * @return valid =.
         */
        valid = GetSampleUnsigned ( sample, v, array_index );
        /**
         * @brief static_cast<V>.
         * @param v v.
         * @return value =.
         */
        value = static_cast<V> ( v );
        break;
        }

        case ChannelDataType::UnsignedIntegerLe:
        case ChannelDataType::UnsignedIntegerBe: {
          uint64_t v = 0;
          /**
           * @brief GetSampleUnsigned.
           * @param sample sample.
           * @param v v.
           * @param array_index array_index.
           * @return valid =.
           */
          valid = GetSampleUnsigned ( sample, v, array_index );
          /**
           * @brief static_cast<V>.
           * @param v v.
           * @return value =.
           */
          value = static_cast<V> ( v );
          break;
      }

      case ChannelDataType::SignedIntegerLe:
      case ChannelDataType::SignedIntegerBe: {
        int64_t v = 0;
        /**
         * @brief GetSampleSigned.
         * @param sample sample.
         * @param v v.
         * @param array_index array_index.
         * @return valid =.
         */
        valid = GetSampleSigned ( sample, v, array_index );
        /**
         * @brief static_cast<V>.
         * @param v v.
         * @return value =.
         */
        value = static_cast<V> ( v );
        break;
        }

        case ChannelDataType::FloatLe:
        case ChannelDataType::FloatBe: {
          double v = 0.0;
          /**
           * @brief GetSampleFloat.
           * @param sample sample.
           * @param v v.
           * @param array_index array_index.
           * @return valid =.
           */
          valid = GetSampleFloat ( sample, v, array_index );
          /**
           * @brief static_cast<V>.
           * @param v v.
           * @return value =.
           */
          value = static_cast<V> ( v );
          break;
      }

      case ChannelDataType::StringAscii:
      case ChannelDataType::StringUTF8:
      case ChannelDataType::StringUTF16Le:
      case ChannelDataType::StringUTF16Be: {
        std::string v;
        /**
         * @brief GetSampleText.
         * @param sample sample.
         * @param v v.
         * @param array_index array_index.
         * @return valid =.
         */
        valid = GetSampleText ( sample, v, array_index );
        /**
         * @brief s.
         * @param v v.
         * @return std::istringstream.
         */
        std::istringstream s ( v );
        s >> value;
        break;
      }

      case ChannelDataType::MimeStream:
      case ChannelDataType::MimeSample:
      case ChannelDataType::ByteArray: {
        std::vector<uint8_t> v;
        /**
         * @brief GetSampleByteArray.
         * @param sample sample.
         * @param v v.
         * @return valid =.
         */
        valid = GetSampleByteArray ( sample, v );
        /**
         * @brief static_cast<V>.
         * @return value =.
         */
        value = static_cast<V> ( v.empty () ? V{} : v [ 0 ] );
        break;
        }

        default:
          break;
    }

    return valid;
    }

    /** \brief Returns the sample channel value as a string. */
    template <>
    /**
     * @brief IChannelObserver::GetChannelValue.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return bool.
     */
    bool IChannelObserver::GetChannelValue ( uint64_t sample,
    std::string& value, uint64_t array_index ) const;

    /** \brief Returns the sample channel value as a byte array. */
    template <>
    /**
     * @brief IChannelObserver::GetChannelValue.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return bool.
     */
    bool IChannelObserver::GetChannelValue ( uint64_t sample,
    std::vector<uint8_t>& value, uint64_t array_index ) const;

    template <typename V>
    /**
     * @brief IChannelObserver::GetChannelSamples.
     * @param values values.
     * @return std::vector<bool>.
     */
    std::vector<bool> IChannelObserver::GetChannelSamples (
    std::vector<V>& values ) const {
      /**
       * @brief NofSamples.
       * @return uint64_t nof_samples =.
       */
      const uint64_t nof_samples = NofSamples ();
      /**
       * @brief valid_array.
       * @param nof_samples nof_samples.
       * @param false false.
       * @return std::vector<bool>.
       */
      std::vector<bool> valid_array ( nof_samples, false );
      /**
       * @brief values.resize.
       * @param nof_samples nof_samples.
       */
      values.resize ( nof_samples, {} );
      uint64_t sample = 0;

      for ( auto& value : values ) {
        /**
         * @brief GetChannelValue.
         * @param sample sample.
         * @param value value.
         * @return valid_array [ sample ] =.
         */
        valid_array [ sample ] = GetChannelValue ( sample, value, 0 );
        ++sample;
    }

    return valid_array;
    }

    template <typename V>
    /**
     * @brief IChannelObserver::GetChannelValues.
     * @param sample sample.
     * @param values values.
     * @return std::vector<bool>.
     */
    std::vector<bool> IChannelObserver::GetChannelValues ( uint64_t sample,
    std::vector<V>& values ) const {
      /**
       * @brief ArraySize.
       * @return auto array_size =.
       */
      const auto array_size = ArraySize ();
      /**
       * @brief valid_array.
       * @param array_size array_size.
       * @param false false.
       * @return std::vector<bool>.
       */
      std::vector<bool> valid_array ( array_size, false );
      /**
       * @brief values.resize.
       * @param array_size array_size.
       */
      values.resize ( array_size, {} );
      uint64_t index = 0;

      for ( auto& value : values ) {
        /**
         * @brief GetChannelValue.
         * @param sample sample.
         * @param value value.
         * @param index index.
         * @return valid_array [ index ] =.
         */
        valid_array [ index ] = GetChannelValue ( sample, value, index );
        ++index;
    }

    return valid_array;
    }

    template <typename V>
    /**
     * @brief IChannelObserver::GetEngValue.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return bool.
     */
    bool IChannelObserver::GetEngValue ( uint64_t sample, V& value,
    uint64_t array_index ) const {
      const auto* conversion = channel_.ChannelConversion ();

      if ( conversion == nullptr ) {
        return GetChannelValue ( sample, value, array_index );
      }

    bool valid = false;
    value = {};

    switch ( channel_.DataType () ) {
      case ChannelDataType::UnsignedIntegerLe:
      case ChannelDataType::UnsignedIntegerBe: {
        uint64_t v = 0;
        /**
         * @brief GetSampleUnsigned.
         * @param sample sample.
         * @param v v.
         * @param array_index array_index.
         * @return valid =.
         */
        valid = GetSampleUnsigned ( sample, v, array_index );

        if ( valid ) {
          /**
           * @brief conversion->Convert.
           * @param v v.
           * @param value value.
           * @return valid =.
           */
          valid = conversion->Convert ( v, value );
          }

          break;
      }

      case ChannelDataType::SignedIntegerLe:
      case ChannelDataType::SignedIntegerBe: {
        int64_t v = 0;
        /**
         * @brief GetSampleSigned.
         * @param sample sample.
         * @param v v.
         * @param array_index array_index.
         * @return valid =.
         */
        valid = GetSampleSigned ( sample, v, array_index )
        /**
         * @brief conversion->Convert.
         * @param v v.
         * @param value value.
         * @return &&.
         */
        && conversion->Convert ( v, value );
        break;
        }

        case ChannelDataType::FloatLe:
        case ChannelDataType::FloatBe: {
          double v = 0.0;
          /**
           * @brief GetSampleFloat.
           * @param sample sample.
           * @param v v.
           * @param array_index array_index.
           * @return valid =.
           */
          valid = GetSampleFloat ( sample, v, array_index )
          /**
           * @brief conversion->Convert.
           * @param v v.
           * @param value value.
           * @return &&.
           */
          && conversion->Convert ( v, value );
          break;
      }

      case ChannelDataType::StringAscii:
      case ChannelDataType::StringUTF16Be:
      case ChannelDataType::StringUTF16Le:
      case ChannelDataType::StringUTF8: {
        std::string v;
        /**
         * @brief GetSampleText.
         * @param sample sample.
         * @param v v.
         * @param array_index array_index.
         * @return valid =.
         */
        valid = GetSampleText ( sample, v, array_index );
        std::string temp;
        /**
         * @brief conversion->Convert.
         * @param v v.
         * @param temp temp.
         */
        conversion->Convert ( v, temp );
        /**
         * @brief temp1.
         * @param temp temp.
         * @return std::istringstream.
         */
        std::istringstream temp1 ( temp );
        temp1 >> value;
        break;
        }

        default:
          /**
           * @brief GetChannelValue.
           * @param sample sample.
           * @param value value.
           * @return valid =.
           */
          valid = GetChannelValue ( sample, value ); // No conversion is allowed;
          break;
    }

    return valid;
    }

    /** \brief Returns the sample engineering (channel) value as a byte array. */
    template <>
    /**
     * @brief IChannelObserver::GetEngValue.
     * @param sample sample.
     * @param value value.
     * @param array_index array_index.
     * @return bool.
     */
    bool IChannelObserver::GetEngValue ( uint64_t sample,
    std::vector<uint8_t>& value,
    uint64_t array_index ) const;
  template <typename V>
  /**
   * @brief IChannelObserver::GetEngSamples.
   * @param values values.
   * @return std::vector<bool>.
   */
  std::vector<bool> IChannelObserver::GetEngSamples (
    std::vector<V>& values ) const {
    /**
     * @brief NofSamples.
     * @return uint64_t nof_samples =.
     */
    const uint64_t nof_samples = NofSamples ();
    /**
     * @brief valid_array.
     * @param nof_samples nof_samples.
     * @param false false.
     * @return std::vector<bool>.
     */
    std::vector<bool> valid_array ( nof_samples, false );
    /**
     * @brief values.resize.
     * @param nof_samples nof_samples.
     */
    values.resize ( nof_samples, {} );
    uint64_t sample = 0;

    for ( auto& value : values ) {
      /**
       * @brief GetEngValue.
       * @param sample sample.
       * @param value value.
       * @return valid_array [ sample ] =.
       */
      valid_array [ sample ] = GetEngValue ( sample, value, 0 );
      ++sample;
    }

    return valid_array;
  }

  template <typename V>
  /**
   * @brief IChannelObserver::GetEngValues.
   * @param sample sample.
   * @param values values.
   * @return std::vector<bool>.
   */
  std::vector<bool> IChannelObserver::GetEngValues ( uint64_t sample,
      std::vector<V>& values ) const {
    /**
     * @brief ArraySize.
     * @return auto array_size =.
     */
    const auto array_size = ArraySize ();
    /**
     * @brief valid_array.
     * @param array_size array_size.
     * @param false false.
     * @return std::vector<bool>.
     */
    std::vector<bool> valid_array ( array_size, false );
    /**
     * @brief values.resize.
     * @param array_size array_size.
     */
    values.resize ( array_size, {} );
    uint64_t index = 0;

    for ( auto& value : values ) {
      /**
       * @brief GetEngValue.
       * @param sample sample.
       * @param value value.
       * @param index index.
       * @return valid_array [ index ] =.
       */
      valid_array [ index ] = GetEngValue ( sample, value, index );
      ++index;
    }

    return valid_array;
  }

}  // namespace mdf