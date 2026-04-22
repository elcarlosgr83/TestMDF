/**
 * @file mdf4file.h
 * @brief MDF4 file container implementation.
 *
 * Defines the concrete MDF4 file object used by the core reader and writer.
 * This file handles the ID (ID4) and header (HD4) blocks for MDF version 4.
 *
 * @ingroup mdf
 */
/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <cstdio>
#include <memory>

#include "hd4block.h"
#include "idblock.h"
#include "mdf/mdffile.h"

namespace mdf::detail {

  /**
   * @brief MDF4 implementation of the generic `MdfFile` interface.
   *
   * This class owns the MDF4 ID and HD blocks and provides the concrete file
   * operations for reading, querying, and writing MDF version 4 files.
   */
  class Mdf4File : public MdfFile {
  public:
    /**
     * @brief Construct an empty MDF4 file object.
     */
    Mdf4File ();

    /**
     * @brief Construct an MDF4 file object from an existing ID block.
     * @param id_block Unique pointer to an initialized ID block.
     */
    explicit Mdf4File ( std::unique_ptr<IdBlock> id_block );

    ~Mdf4File () override = default;

    Mdf4File ( const Mdf4File& ) = delete;
    Mdf4File ( Mdf4File&& ) = delete;
    Mdf4File& operator= ( const Mdf4File& ) = delete;
    Mdf4File& operator= ( Mdf4File&& ) = delete;

    /**
     * @brief Append attachments from the HD block to the destination list.
     * @param dest Recipient list for attachment pointers.
     */
    void Attachments ( AttachmentList& dest ) const override;

    /**
     * @brief Append data groups from the HD block to the destination list.
     * @param dest Recipient list for data group pointers.
     */
    void DataGroups ( DataGroupList& dest ) const override;

    /**
     * @brief Get the MDF file version string.
     * @return The MDF file version as a string.
     */
    [ [ nodiscard ] ] std::string Version () const override;

    /**
     * @brief Set the MDF file minor version.
     * @param minor Minor version number.
     */
    void MinorVersion ( int minor ) override;

    /**
     * @brief Set the program identifier stored in the ID block.
     * @param program_id Identifier string.
     */
    void ProgramId ( const std::string& program_id ) override;

    /**
     * @brief Return the program identifier from the ID block.
     * @return Program identifier string.
     */
    [ [ nodiscard ] ] std::string ProgramId () const override;

    /**
     * @brief Return the header block for this file.
     * @return Pointer to the header interface.
     */
    [ [ nodiscard ] ] IHeader* Header () const override;

    /**
     * @brief Create a new attachment block in the HD block.
     * @return Pointer to the created attachment block.
     */
    [ [ nodiscard ] ] IAttachment* CreateAttachment () override;

    /**
     * @brief Create a new data group in the HD block.
     * @return Pointer to the created data group.
     */
    [ [ nodiscard ] ] IDataGroup* CreateDataGroup () override;

    /**
     * @brief Find a child MDF block by its ID.
     * @param id Block identifier.
     * @return Pointer to the found block or nullptr.
     */
    [ [ nodiscard ] ] MdfBlock* Find ( int64_t id ) const;

    /**
     * @brief Return true for MDF4 file objects.
     * @return Always true.
     */
    [ [ nodiscard ] ] bool IsMdf4 () const override;

    /**
     * @brief Update the finalized state of the file.
     * @param finalized Finalized flag.
     * @param buffer Stream buffer for writing updates.
     * @param standard_flags Standard finalization flags.
     * @param custom_flags Custom finalization flags.
     */
    void IsFinalized ( bool finalized, std::streambuf& buffer,
      uint16_t standard_flags,
      uint16_t custom_flags ) override;

    /**
     * @brief Query whether this file is finalized.
     * @param standard_flags Returned standard finalization flags.
     * @param custom_flags Returned custom finalization flags.
     * @return True when the file is finalized.
     */
    [ [ nodiscard ] ] bool IsFinalized ( uint16_t& standard_flags,
      uint16_t& custom_flags ) const override;

    /**
     * @brief Query whether finalization was completed during reading.
     * @return True when finalization was completed.
     */
    [ [ nodiscard ] ] bool IsFinalizedDone () const override;

    /**
     * @brief Read the basic MDF4 header blocks from the stream.
     * @param buffer Stream buffer to read from.
     */
    void ReadHeader ( std::streambuf& buffer ) override;

    /**
     * @brief Read measurement information from the MDF4 file.
     * @param buffer Stream buffer to read from.
     */
    void ReadMeasurementInfo ( std::streambuf& buffer ) override;

    /**
     * @brief Read all MDF4 metadata blocks except raw sample data.
     * @param buffer Stream buffer to read from.
     */
    void ReadEverythingButData ( std::streambuf& buffer ) override;

    /**
     * @brief Get the MDF4 ID block.
     * @return Reference to the ID block.
     */
    [ [ nodiscard ] ] const IdBlock& Id () const;

    /**
     * @brief Get the MDF4 HD block.
     * @return Reference to the HD block.
     */
    [ [ nodiscard ] ] const Hd4Block& Hd () const;

    /**
     * @brief Write the MDF4 file contents to a stream.
     * @param buffer Stream buffer to write into.
     * @return True on success.
     */
    bool Write ( std::streambuf& buffer ) override;

    /**
     * @brief Find the parent data group for a channel.
     * @param channel Channel to search.
     * @return Parent data group or nullptr.
     */
    [ [ nodiscard ] ] IDataGroup* FindParentDataGroup (
      const IChannel& channel ) const override;

    private:
      std::unique_ptr<IdBlock> id_block_;
      std::unique_ptr<Hd4Block> hd_block_;

      bool finalized_done_ = false;
      bool FinalizeFile ( std::streambuf& buffer );
      void FindAllReferences ( std::streambuf& buffer );
  };
  }  // namespace mdf::detail
