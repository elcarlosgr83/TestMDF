/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

/** \file
 * Defines an interface against a sample reduction (SR) block.
 * The sample reduction block (SR) stores the minimal, maximum and average
 * value for each channel in a CG block.
 */

#pragma once

#include "mdf/iblock.h"
#include <string>
#include "mdf/ichannel.h"
namespace mdf {
  /**
   * @brief IChannelGroup class definition.
   */
  class IChannelGroup;

  /** \brief Type of master for a sample reduction (SR) block.
   *
   */
  enum class SrSyncType : uint8_t {
    Undefined = 0,
    Time = 1,
    Angle = 2,
    Distance = 3,
    Index = 4,
  };

  namespace SrFlag {

    constexpr uint8_t InvalidationByte =
      0x01; ///< The block contains an invalidation byte.
    constexpr uint8_t DominantBit = 0x02; ///< Dominant invalidation flag.

  } // End namespace SrFlag

  /** \brief Template class that is used to handle reduction sample.
   *
   * @tparam T Type of value.
   */
  template <typename T>
  /**
   * @brief SrValue struct definition.
   */
  struct SrValue {
    T MeanValue = {}; ///< Mean value.
    T MinValue = {};  ///< Min value.
    T MaxValue = {};  ///< Max value.
    bool MeanValid = false; ///< Mean value valid.
    bool MinValid = false;  ///< Min value valid.
    bool MaxValid = false;  ///< Max value valid.
  };

  /** \class ISampleReduction mdf/isamplereduction.h isamplereduction.h
   * \brief Defines an interface to a sample reduction (SR) block.
   *
   * Sample reduction (SR) blocks stores min, max and average values for the all
   * samples or for an interval of samples values.
   */

  class ISampleReduction : public IBlock {
  public:
    /** \brief Sets number of samples in the block.
     *
     * @param nof_samples Number of sample values.
     */
    /**
     * @brief NofSamples.
     * @param nof_samples nof_samples.
     * @return virtual void.
     */
    virtual void NofSamples ( uint64_t nof_samples ) = 0;

    /** \brief Returns number of samples.
     *
     * @return Number of samples.
     */
    /**
     * @brief NofSamples.
     * @return [ [ nodiscard ] ] virtual uint64_t.
     */
    [ [ nodiscard ] ] virtual uint64_t NofSamples () const = 0;

      /** \brief Sets the interval value.
       *
       * Sets the interval value. Note that the value is dependent on
       * the synchronization type.
       * @param interval Interval value.
       */
      /**
       * @brief Interval.
       * @param interval interval.
       * @return virtual void.
       */
      virtual void Interval ( double interval ) = 0;

      /** \brief Returns the interval value.
       *
       * @return The interval value.
       */
    /**
     * @brief Interval.
     * @return [ [ nodiscard ] ] virtual double.
     */
    [ [ nodiscard ] ] virtual double Interval () const = 0;

      /** \brief Synchronization type, for example Time or number of samples.
       *
       * @param type Type of synchronization.
       */
      /**
       * @brief SyncType.
       * @param type type.
       * @return virtual void.
       */
      virtual void SyncType ( SrSyncType type );

      /** \brief Returns the synchronization type.
       *
       * @return Synchronization type.
       */
    /**
     * @brief SyncType.
     * @return [ [ nodiscard ] ] virtual SrSyncType.
     */
    [ [ nodiscard ] ] virtual SrSyncType SyncType () const;

      /** \brief Sets SR flags.
       *
       * @param flags Flags to store in the SR block.
       */
      /**
       * @brief Flags.
       * @param flags flags.
       * @return virtual void.
       */
      virtual void Flags ( uint8_t flags );

      /** \brief Returns the SR flags.
       *
       * @return SR flags.
       */
    /**
     * @brief Flags.
     * @return [ [ nodiscard ] ] virtual uint8_t.
     */
    [ [ nodiscard ] ] virtual uint8_t Flags () const;

      /** \brief Returns its channel group. */
    [ [ nodiscard ] ] virtual const IChannelGroup* ChannelGroup () const = 0;

      /** \brief Returns the reduced SR value for a specific sample.
       *
       * @tparam T Type of value.
       * @param channel Reference to the channel.
       * @param sample Sample index.
       * @param array_index Array index. Only used for array channels.
       * @param value Returns the SR sample values.
       */
      template <typename T>
      /**
       * @brief GetChannelValue.
       * @param channel channel.
       * @param sample sample.
       * @param array_index array_index.
       * @param value value.
       */
      void GetChannelValue ( const IChannel& channel, uint64_t sample,
      uint64_t array_index, SrValue<T>& value ) const;

      /** \brief Returns the scaled SR value.
       *
       * @tparam T Type of value.
       * @param channel Reference to the channel
       * @param sample Sample index.
       * @param array_index Array offset in case of array type.
       * @param value Returns the SR sample value.
       */
      template <typename T>
      /**
       * @brief GetEngValue.
       * @param channel channel.
       * @param sample sample.
       * @param array_index array_index.
       * @param value value.
       */
      void GetEngValue ( const IChannel& channel, uint64_t sample,
      uint64_t array_index, SrValue<T>& value ) const;

      /**
       * @brief ClearData.
       * @return virtual void.
       */
      virtual void ClearData () = 0; ///< Resets the internal SR data bytes.

    protected:
      /** \brief Returns the value as an unsigned integer.
       *
       * @param channel Reference to the channel.
       * @param sample Sample index.
       * @param array_index Array index for array channels.
       * @param value Returns the unsigned SR values.
       */
      /**
       * @brief GetChannelValueUint.
       * @param channel channel.
       * @param sample sample.
       * @param array_index array_index.
       * @param value value.
       * @return virtual void.
       */
      virtual void GetChannelValueUint ( const IChannel& channel, uint64_t sample,
      uint64_t array_index, SrValue<uint64_t>& value ) const = 0;

      /** \brief Returns the value as a signed integer.
       *
       * @param channel Reference to the channel.
       * @param sample Sample index.
       * @param array_index Array index for array channels.
       * @param value Returns the signed SR values.
       */
      /**
       * @brief GetChannelValueInt.
       * @param channel channel.
       * @param sample sample.
       * @param array_index array_index.
       * @param value value.
       * @return virtual void.
       */
      virtual void GetChannelValueInt ( const IChannel& channel, uint64_t sample,
      uint64_t array_index, SrValue<int64_t>& value ) const = 0;

      /** \brief Returns the value as a double.
       *
       * @param channel Reference to the channel.
       * @param sample Sample index.
       * @param array_index Array index for array channels.
       * @param value Returns the double SR values.
       */
      /**
       * @brief GetChannelValueDouble.
       * @param channel channel.
       * @param sample sample.
       * @param array_index array_index.
       * @param value value.
       * @return virtual void.
       */
      virtual void GetChannelValueDouble ( const IChannel& channel, uint64_t sample,
      uint64_t array_index, SrValue<double>& value ) const = 0;
  };

  template<typename T>
  /**
   * @brief ISampleReduction::GetChannelValue.
   * @param channel channel.
   * @param sample sample.
   * @param array_index array_index.
   * @param value value.
   */
  void ISampleReduction::GetChannelValue ( const IChannel& channel,
  uint64_t sample,
  uint64_t array_index, SrValue<T>& value ) const {
    value = {};

    switch ( channel.DataType () ) {
      case ChannelDataType::UnsignedIntegerLe:
      case ChannelDataType::UnsignedIntegerBe: {
        SrValue<uint64_t> temp;
        /**
         * @brief GetChannelValueUint.
         * @param channel channel.
         * @param sample sample.
         * @param array_index array_index.
         * @param temp temp.
         */
        GetChannelValueUint ( channel, sample, array_index, temp );
        /**
         * @brief static_cast<T>.
         * @param MeanValue MeanValue.
         * @return value.MeanValue =.
         */
        value.MeanValue = static_cast<T> ( temp.MeanValue );
        /**
         * @brief static_cast<T>.
         * @param MinValue MinValue.
         * @return value.MinValue =.
         */
        value.MinValue = static_cast<T> ( temp.MinValue );
        /**
         * @brief static_cast<T>.
         * @param MaxValue MaxValue.
         * @return value.MaxValue =.
         */
        value.MaxValue = static_cast<T> ( temp.MaxValue );
        value.MeanValid = temp.MeanValid;
        value.MinValid = temp.MinValid;
        value.MaxValid = temp.MaxValid;
        break;
        }

        case ChannelDataType::SignedIntegerLe:
        case ChannelDataType::SignedIntegerBe: {
          SrValue<int64_t> temp;
          /**
           * @brief GetChannelValueInt.
           * @param channel channel.
           * @param sample sample.
           * @param array_index array_index.
           * @param temp temp.
           */
          GetChannelValueInt ( channel, sample, array_index, temp );
          /**
           * @brief static_cast<T>.
           * @param MeanValue MeanValue.
           * @return value.MeanValue =.
           */
          value.MeanValue = static_cast<T> ( temp.MeanValue );
          /**
           * @brief static_cast<T>.
           * @param MinValue MinValue.
           * @return value.MinValue =.
           */
          value.MinValue = static_cast<T> ( temp.MinValue );
          /**
           * @brief static_cast<T>.
           * @param MaxValue MaxValue.
           * @return value.MaxValue =.
           */
          value.MaxValue = static_cast<T> ( temp.MaxValue );
          value.MeanValid = temp.MeanValid;
          value.MinValid = temp.MinValid;
          value.MaxValid = temp.MaxValid;
          break;
      }

      case ChannelDataType::FloatLe:
      case ChannelDataType::FloatBe: {
        SrValue<double> temp;
        /**
         * @brief GetChannelValueDouble.
         * @param channel channel.
         * @param sample sample.
         * @param array_index array_index.
         * @param temp temp.
         */
        GetChannelValueDouble ( channel, sample, array_index, temp );
        /**
         * @brief static_cast<T>.
         * @param MeanValue MeanValue.
         * @return value.MeanValue =.
         */
        value.MeanValue = static_cast<T> ( temp.MeanValue );
        /**
         * @brief static_cast<T>.
         * @param MinValue MinValue.
         * @return value.MinValue =.
         */
        value.MinValue = static_cast<T> ( temp.MinValue );
        /**
         * @brief static_cast<T>.
         * @param MaxValue MaxValue.
         * @return value.MaxValue =.
         */
        value.MaxValue = static_cast<T> ( temp.MaxValue );
        value.MeanValid = temp.MeanValid;
        value.MinValid = temp.MinValid;
        value.MaxValid = temp.MaxValid;
        break;
        }

        default:
          break;
    }
    }

    /** \brief Specialized function that return an unsigned value. */
    template<>
    /**
     * @brief ISampleReduction::GetChannelValue.
     * @param channel channel.
     * @param sample sample.
     * @param array_index array_index.
     * @param value value.
     */
    void ISampleReduction::GetChannelValue ( const IChannel& channel,
    uint64_t sample,
    uint64_t array_index, SrValue<std::string>& value ) const;


    template<typename T>
    /**
     * @brief ISampleReduction::GetEngValue.
     * @param channel channel.
     * @param sample sample.
     * @param array_index array_index.
     * @param value value.
     */
    void ISampleReduction::GetEngValue ( const IChannel& channel, uint64_t sample,
    uint64_t array_index, SrValue<T>& value ) const {
      value = {};

      /**
       * @brief channel.ChannelConversion.
       * @return auto* channel_conversion =.
       */
      const auto* channel_conversion = channel.ChannelConversion ();

      switch ( channel.DataType () ) {
        case ChannelDataType::UnsignedIntegerLe:
        case ChannelDataType::UnsignedIntegerBe: {
          SrValue<uint64_t> temp;
          /**
           * @brief GetChannelValueUint.
           * @param channel channel.
           * @param sample sample.
           * @param array_index array_index.
           * @param temp temp.
           */
          GetChannelValueUint ( channel, sample, array_index, temp );

          if ( channel_conversion != 0 ) {
            /**
             * @brief channel_conversion->Convert.
             * @param MeanValue MeanValue.
             * @param MeanValue MeanValue.
             * @return bool mean_valid =.
             */
            const bool mean_valid = channel_conversion->Convert ( temp.MeanValue,
            value.MeanValue );
            /**
             * @brief channel_conversion->Convert.
             * @param MinValue MinValue.
             * @param MinValue MinValue.
             * @return bool min_valid =.
             */
            const bool min_valid = channel_conversion->Convert ( temp.MinValue,
            value.MinValue );
            /**
             * @brief channel_conversion->Convert.
             * @param MaxValue MaxValue.
             * @param MaxValue MaxValue.
             * @return bool max_valid =.
             */
            const bool max_valid = channel_conversion->Convert ( temp.MaxValue,
            value.MaxValue );
            value.MeanValid = temp.MeanValid && mean_valid;
            value.MinValid = temp.MinValid && min_valid;
            value.MaxValid = temp.MaxValid && max_valid;
        } else {
          /**
           * @brief static_cast<T>.
           * @param MeanValue MeanValue.
           * @return value.MeanValue =.
           */
          value.MeanValue = static_cast<T> ( temp.MeanValue );
          /**
           * @brief static_cast<T>.
           * @param MinValue MinValue.
           * @return value.MinValue =.
           */
          value.MinValue = static_cast<T> ( temp.MinValue );
          /**
           * @brief static_cast<T>.
           * @param MaxValue MaxValue.
           * @return value.MaxValue =.
           */
          value.MaxValue = static_cast<T> ( temp.MaxValue );
          value.MeanValid = temp.MeanValid;
          value.MinValid = temp.MinValid;
          value.MaxValid = temp.MaxValid;
          }

          break;
      }

      case ChannelDataType::SignedIntegerLe:
      case ChannelDataType::SignedIntegerBe: {
        SrValue<int64_t> temp;
        /**
         * @brief GetChannelValueInt.
         * @param channel channel.
         * @param sample sample.
         * @param array_index array_index.
         * @param temp temp.
         */
        GetChannelValueInt ( channel, sample, array_index, temp );

        if ( channel_conversion != 0 ) {
          /**
           * @brief channel_conversion->Convert.
           * @param MeanValue MeanValue.
           * @param MeanValue MeanValue.
           * @return bool mean_valid =.
           */
          const bool mean_valid = channel_conversion->Convert ( temp.MeanValue,
          value.MeanValue );
          /**
           * @brief channel_conversion->Convert.
           * @param MinValue MinValue.
           * @param MinValue MinValue.
           * @return bool min_valid =.
           */
          const bool min_valid = channel_conversion->Convert ( temp.MinValue,
          value.MinValue );
          /**
           * @brief channel_conversion->Convert.
           * @param MaxValue MaxValue.
           * @param MaxValue MaxValue.
           * @return bool max_valid =.
           */
          const bool max_valid = channel_conversion->Convert ( temp.MaxValue,
          value.MaxValue );
          value.MeanValid = temp.MeanValid && mean_valid;
          value.MinValid = temp.MinValid && min_valid;
          value.MaxValid = temp.MaxValid && max_valid;
          } else {
            /**
             * @brief static_cast<T>.
             * @param MeanValue MeanValue.
             * @return value.MeanValue =.
             */
            value.MeanValue = static_cast<T> ( temp.MeanValue );
            /**
             * @brief static_cast<T>.
             * @param MinValue MinValue.
             * @return value.MinValue =.
             */
            value.MinValue = static_cast<T> ( temp.MinValue );
          /**
           * @brief static_cast<T>.
           * @param MaxValue MaxValue.
           * @return value.MaxValue =.
           */
          value.MaxValue = static_cast<T> ( temp.MaxValue );
          value.MeanValid = temp.MeanValid;
          value.MinValid = temp.MinValid;
          value.MaxValid = temp.MaxValid;
        }

        break;
      }

      case ChannelDataType::FloatLe:
      case ChannelDataType::FloatBe: {
        SrValue<double> temp;
        /**
         * @brief GetChannelValueDouble.
         * @param channel channel.
         * @param sample sample.
         * @param array_index array_index.
         * @param temp temp.
         */
        GetChannelValueDouble ( channel, sample, array_index, temp );

        if ( channel_conversion != 0 ) {
          /**
           * @brief channel_conversion->Convert.
           * @param MeanValue MeanValue.
           * @param MeanValue MeanValue.
           * @return bool mean_valid =.
           */
          const bool mean_valid = channel_conversion->Convert ( temp.MeanValue,
                                  value.MeanValue );
          /**
           * @brief channel_conversion->Convert.
           * @param MinValue MinValue.
           * @param MinValue MinValue.
           * @return bool min_valid =.
           */
          const bool min_valid = channel_conversion->Convert ( temp.MinValue,
                                 value.MinValue );
          /**
           * @brief channel_conversion->Convert.
           * @param MaxValue MaxValue.
           * @param MaxValue MaxValue.
           * @return bool max_valid =.
           */
          const bool max_valid = channel_conversion->Convert ( temp.MaxValue,
                                 value.MaxValue );
          value.MeanValid = temp.MeanValid && mean_valid;
          value.MinValid = temp.MinValid && min_valid;
          value.MaxValid = temp.MaxValid && max_valid;
        } else {
          /**
           * @brief static_cast<T>.
           * @param MeanValue MeanValue.
           * @return value.MeanValue =.
           */
          value.MeanValue = static_cast<T> ( temp.MeanValue );
          /**
           * @brief static_cast<T>.
           * @param MinValue MinValue.
           * @return value.MinValue =.
           */
          value.MinValue = static_cast<T> ( temp.MinValue );
          /**
           * @brief static_cast<T>.
           * @param MaxValue MaxValue.
           * @return value.MaxValue =.
           */
          value.MaxValue = static_cast<T> ( temp.MaxValue );
          value.MeanValid = temp.MeanValid;
          value.MinValid = temp.MinValid;
          value.MaxValid = temp.MaxValid;
        }

        break;
      }

      default:
        break;
    }
  }

  /** \brief Specialized function that returns SR values as strings. */
  template<>
  /**
   * @brief ISampleReduction::GetEngValue.
   * @param channel channel.
   * @param sample sample.
   * @param array_index array_index.
   * @param value value.
   */
  void ISampleReduction::GetEngValue ( const IChannel& channel, uint64_t sample,
                                       uint64_t array_index, SrValue<std::string>& value ) const;
} // mdf