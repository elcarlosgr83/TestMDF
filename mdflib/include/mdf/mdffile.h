/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <cstdio>

#include <string>
#include <vector>

#include "mdf/iheader.h"

namespace mdf {

  /**
   * @brief IAttachment class definition.
   */
  class IAttachment;
  /**
   * @brief IDataGroup class definition.
   */
  class IDataGroup;
  /**
   * @brief IChannel class definition.
   */
  class IChannel;

  /** @brief List of pointers to attachments.
   */
  using AttachmentList = std::vector<const IAttachment*>;

  /** \brief List of pointers to measurements (DG block).
   */
  using DataGroupList = std::vector<IDataGroup*>;

  /**
   * @class MdfFile mdffile.h mdf/mdffile.h
   * @ingroup mdf
   * @brief Core MDF file object.
   *
   * The `MdfFile` class provides a common interface for accessing MDF file
   * metadata, attachments, measurements and writer/read operations.
   */

  class MdfFile {
  public:
    /**
     * @brief ~MdfFile.
     */
    virtual ~MdfFile () = default; ///< Default destructor

    /**
     * @brief Returns all file attachments.
     * @param dest Destination container receiving attachment pointers.
     * @details MDF4 supports attachments as external references or embedded
     * binary objects.
     * @see CreateAttachment
     * @see Header
     */
    virtual void Attachments ( AttachmentList& dest ) const = 0;

    /**
     * @brief Returns all measurement data groups.
     * @param dest Destination container receiving DG pointers.
     * @details Data groups form the root of measurement payload traversal.
     * @see CreateDataGroup
     * @see Header
     */
    virtual void DataGroups ( DataGroupList& dest ) const = 0;

    /** @brief Returns the MDF file version string.
     *
     * Returns the full MDF version string, for example "4.11".
     * @return MDF version string.
     */
    [[nodiscard]] virtual std::string Version () const = 0;

    /** @brief Returns the major MDF version.
     *
     * Returns the major version number for the file, for example 4 for MDF4.
     * @return Major version number.
     */
    [[nodiscard]] int MainVersion () const;

      /** @brief Set the minor version of the file.
       *
       * Sets the minor version number used in the MDF version string.
       * @param minor Minor version number.
       */
      virtual void MinorVersion ( int minor ) = 0;

      /** @brief Returns the minor MDF version number.
       *
       * Returns the minor part of the version, for example 11 for 4.11.
       * @return Minor version number.
       */
    [[nodiscard]] int MinorVersion () const;

      /** @brief Set the program identifier in the ID block.
       *
       * Sets the program identifier string (up to 8 characters) that describes
       * the software that created the file.
       * @param program_id Program identifier.
       */
      virtual void ProgramId ( const std::string& program_id ) = 0;

      /** @brief Returns the program identifier.
       *
       * Returns the identifier of the program that created the MDF file.
       * @return Program identifier string.
       */
    [[nodiscard]] virtual std::string ProgramId () const = 0;

      /** @brief Returns the header object.
       *
       * Returns the header instance that exposes general file metadata and
       * the root objects for the file contents.
       * @return Pointer to the header object.
       */
    /**
     * @brief Returns the root header interface.
     * @return Header pointer.
     * @see DataGroups
     * @see ReadHeader
     */
    [[nodiscard]] virtual IHeader* Header () const = 0;

      /** @brief Creates a new attachment (AT block).
       *
       * Creates a new attachment for the MDF file. Attachments may be
       * references to external files or embedded binary resources.
       * MDF3 files do not support attachments.
       * @return Pointer to the newly created attachment.
       */
    [[nodiscard]] virtual IAttachment* CreateAttachment ();

      /** \brief Creates a new measurement (DG block).
       *
       * Creates a new measurement block in the file also known as a DG block.
       * A DG block defines one measurement with one or more sub-measurements (CG
       * block). The new DG block is always put last in the file.
       * @return Pointer to the new measurement.
       */
    /**
     * @brief Creates a new measurement data group.
     * @return Pointer to the created DG block.
     * @details New DG blocks are appended after existing groups.
     * @see DataGroups
     * @see Header
     */
    [ [ nodiscard ] ] virtual IDataGroup* CreateDataGroup () = 0;

      /** @brief Returns true if this is a MDF4 file.
       *
       * Returns true when the file is in the MDF4 family.
       * @return `true` for MDF4, otherwise `false`.
       */
    /**
     * @brief Indicates whether this file uses MDF4 format.
     * @return `true` for MDF4 variants.
     * @see Version
     * @see MainVersion
     */
    [[nodiscard]] virtual bool IsMdf4 () const = 0;

      /**
       * @brief Reads file-level ID/HD metadata blocks.
       * @param buffer Source stream.
       * @see ReadMeasurementInfo
       * @see Header
       */
      virtual void ReadHeader ( std::streambuf& buffer ) = 0;

      /**
       * @brief Reads DG/CG/CN metadata blocks.
       * @param buffer Source stream.
       * @details Populates group/channel metadata without loading sample
       * payload data.
       * @see ReadHeader
       * @see ReadEverythingButData
       */
      virtual void ReadMeasurementInfo ( std::streambuf& buffer ) = 0;

      virtual void
      /**
       * @brief Reads all non-payload structures from stream.
       * @param buffer Source stream.
       * @see ReadHeader
       * @see ReadMeasurementInfo
       */
      ReadEverythingButData ( std::streambuf& buffer ) = 0;

      /**
        * @brief Writes file content to the output stream.
        * @param buffer Output stream buffer.
        * @return `true` on success.
       */
      virtual bool Write ( std::streambuf& buffer ) = 0;

      /** \brief Display name of the file.
       *
       * Default set to the stem of the file. Not stored in the file itself. Only
       * used for display purpose.
       * @return Short name of the file.
       */
    [ [ nodiscard ] ] const std::string& Name () const { return name_; }

    /** \brief Set the display name of the file.
     *
     * Sets the display name of the file. By default this is
     * set to the file name without path and extension (stem).
     * @param name Short name of the file.
     */
      void Name ( const std::string& name ) { name_ = name; }

      /** \brief Returns the full name of the file.
       *
       * Returns the file name with path and extension.
       * @return File name with path and extension.
       */
    [ [ nodiscard ] ] const std::string& FileName () const { return filename_; }

    /** \brief Sets the file name.
     *
     * Sets the file name and the short name of the object.
     * @param filename File name with path and extension.
     */
    void FileName ( const std::string& filename );

/** @brief Set the file finalized state.
       *
       * Marks the file as finalized and writes the finalized state to the
       * output buffer.
       * @param finalized `true` to finalize the file.
       * @param buffer Output stream buffer.
       * @param standard_flags Standard finalize flags.
       * @param custom_flags Custom finalize flags.
       */
    virtual void IsFinalized ( bool finalized, std::streambuf& buffer,
    uint16_t standard_flags, uint16_t custom_flags ) = 0;

    /**
     * @brief Returns finalized state and finalize flags.
     * @param standard_flags Receives standard finalize bits.
     * @param custom_flags Receives custom finalize bits.
     * @return `true` if the file is marked finalized.
     * @see IsFinalizedDone
     * @see IsFinalized(bool,std::streambuf&,uint16_t,uint16_t)
     */
    [[nodiscard]] virtual bool IsFinalized ( uint16_t& standard_flags,
      uint16_t& custom_flags ) const = 0;

      /** @brief Returns whether finalization succeeded.
       *
       * Checks if the file has been finalized successfully.
       * @return `true` when finalization is complete.
       */
    [[nodiscard]] virtual bool IsFinalizedDone () const;

      /** @brief Find the parent data group for a channel.
       *
       * Returns the measurement group (DG block) that contains the specified
       * channel.
       * @param channel Channel object to search for.
       * @return Pointer to the parent data group, or `nullptr` if not found.
       */
    [[nodiscard]] virtual IDataGroup* FindParentDataGroup (
      const IChannel &channel ) const = 0;
    protected:
      /**
       * @brief MdfFile.
       */
      MdfFile () = default; ///< Default constructor
    private:
      std::string name_;      ///< File name without path and extension.
      std::string filename_;  ///< File name with full path.
  };

  }  // namespace mdf