/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <string>

#include "mdf/imetadata.h"
#include "mdf/iblock.h"
#include "mdf/sicomment.h"

namespace mdf {

  /** \brief Type of source information. */
  enum class SourceType : uint8_t {
    Other = 0, ///< Unknown source type.
    Ecu = 1, ///< ECU.
    Bus = 2, ///< Bus.
    IoDevice = 3, ///< I/O device.
    Tool = 4, ///< Tool.
    User = 5 ///< User.
  };

  /** \brief Type of bus. */
  enum class BusType : uint8_t {
    None = 0, ///< No bus (default).
    Other = 1, ///< Unknown bus type.
    Can = 2, ///< CAN bus.
    Lin = 3, ///< LIN bus.
    Most = 4, ///< MOST bus.
    FlexRay = 5, ///< FlexRay bus.
    Kline = 6, ///< KLINE bus.
    Ethernet = 7, ///< EtherNet bus.
    Usb = 8 ///< USB bus.
  };

  /** \brief Source information flags. */
  namespace SiFlag {
    constexpr uint8_t Simulated = 0x01; ///< Simulated device.
  }

  /** \brief Interface to a source information (SI) block.
   *
   * The source information (SI) describe the test equipment or its environment.
   */

  class ISourceInformation : public IBlock {
  public:
    /**
     * @brief Sets source name.
     * @param name Source name.
     * @see Name() const
     */
    virtual void Name ( const std::string& name ) = 0; ///< Sets the name.
    /**
     * @brief Returns source name.
     * @return Source name.
     * @see Name(const std::string&)
     */
    [ [ nodiscard ] ] virtual const std::string& Name () const = 0; ///< Name.

      /**
       * @brief Sets source path.
       * @param path Source path.
       * @see Path() const
       */
      virtual void Path ( const std::string& path ) = 0; ///< Sets the path.
    /**
     * @brief Returns source path.
     * @return Source path.
     * @see Path(const std::string&)
     */
    [ [ nodiscard ] ] virtual const std::string& Path () const = 0; ///< Path.

      /** \brief Sets the descriptive text. */
      virtual void Description ( const std::string& desc ) = 0;
      /** \brief Return the descriptive text. */
    [ [ nodiscard ] ] virtual std::string Description () const = 0;

      /**
       * @brief Sets source type.
       * @param type Source type.
       * @see Type() const
       */
      virtual void Type ( SourceType type ) = 0; ///< Sets the type of source.
    /**
     * @brief Returns source type.
     * @return Source type.
     * @see Type(SourceType)
     */
    [ [ nodiscard ] ] virtual SourceType Type () const = 0; ///< Type of source.

      /**
       * @brief Sets bus type associated with source.
       * @param type Bus type.
       * @see Bus() const
       */
      virtual void Bus ( BusType type ) = 0; ///< Set the type of bus.
    /**
     * @brief Returns bus type associated with source.
     * @return Bus type.
     * @see Bus(BusType)
     */
    [ [ nodiscard ] ] virtual BusType Bus () const = 0; ///< Type of bus.

      /**
       * @brief Sets source information flags.
       * @param flags Flag bit mask.
       * @see Flags() const
       */
      virtual void Flags ( uint8_t flags ) = 0; ///< Set the SiFlag.
    /**
     * @brief Returns source information flags.
     * @return Flag bit mask.
     * @see Flags(uint8_t)
     */
    [ [ nodiscard ] ] virtual uint8_t Flags () const = 0; ///< Returns SiFlag.

      /** \brief Creates a meta-data (MD) block. */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData () = 0;
      /** \brief Returns an existing meta-data (MD) block. */
    [ [ nodiscard ] ] virtual const IMetaData* MetaData () const = 0;

      /**
       * @brief Sets SI comment content.
       * @param si_comment SI comment object.
       * @see GetSiComment
       */
      void SetSiComment ( const SiComment& si_comment );
      /**
       * @brief Retrieves SI comment content.
       * @param si_comment Receives SI comment object.
       * @see SetSiComment
       */
      void GetSiComment ( SiComment& si_comment ) const;
  };

  }  // end namespace mdf