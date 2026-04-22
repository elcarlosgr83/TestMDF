/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>

#include "MdfFile.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @file MdfReader.h
   * @brief Wrapper for MDF reader operations.
   *
   * Provides a C++ API for reading MDF files, opening and closing the reader,
   * and loading header or data group content.
  *
  * Typical flow:
  * @code{.cpp}
  * MdfLibrary::MdfReader reader("capture.mf4");
  * if (reader.Open() && reader.ReadHeader()) {
  *   auto file = reader.GetFile();
  *   auto header = reader.GetHeader();
  * }
  * @endcode
   *
   * @ingroup mdflibrary
   */
  class MdfReader {
  private:
    mdf::MdfReader* reader;

  public:
    /**
     * @brief Open an MDF file for reading.
     * @param filename Path to the MDF file.
      * @details Initializes the low-level reader handle. Use `Open()` before
      * invoking read operations.
      * @see Open
      * @see ReadHeader
     */
    MdfReader ( const char* filename ) : reader ( MdfReaderInit ( filename ) ) {
      if ( reader == nullptr ) {
        throw std::runtime_error ( "MdfReader Init failed" );
      }
    }

    /**
     * @brief Destroy the reader.
     */
    ~MdfReader () {
      if ( reader == nullptr ) {
        return;
      }

      MdfReaderUnInit ( reader );
      reader = nullptr;
    }

    MdfReader ( const MdfReader& ) = delete;

    /**
     * @brief Returns the reader index.
     * @return Reader index.
     */
    int64_t GetIndex () const { return MdfReaderGetIndex ( reader ); }

    /**
     * @brief Returns whether the reader is in a valid state.
     * @return `true` if the reader is OK.
      * @see Open
      * @see ReadHeader
     */
    bool IsOk () { return MdfReaderIsOk ( reader ); }

    /**
     * @brief Returns the file wrapper.
     * @return `MdfFile` wrapper.
      * @see GetHeader
      * @see ReadHeader
     */
    const MdfFile GetFile () const { return MdfFile ( MdfReaderGetFile ( reader ) ); }

    /**
     * @brief Returns the header wrapper.
     * @return `MdfHeader` wrapper.
      * @see ReadHeader
      * @see GetDataGroup
     */
    MdfHeader GetHeader () const { return MdfHeader ( MdfReaderGetHeader ( reader ) ); }

    /**
     * @brief Returns a data group wrapper by index.
     * @param index Data group index.
     * @return `MdfDataGroup` wrapper.
     * @details Use this after header/measurement metadata has been read.
     * @see ReadMeasurementInfo
     * @see ReadData
     */
    const MdfDataGroup GetDataGroup ( size_t index ) {
      return MdfDataGroup ( MdfReaderGetDataGroup ( reader, index ) );
    }

    /**
     * @brief Open the reader.
     * @return `true` if the file was opened successfully.
      * @details Opens the MDF file stream and prepares internal structures for
      * subsequent read operations.
      * @see ReadHeader
      * @see Close
     */
    bool Open () { return MdfReaderOpen ( reader ); }

    /**
     * @brief Close the reader.
      * @details Closes file resources acquired by `Open()`.
      * @see Open
     */
    void Close () { MdfReaderClose ( reader ); }

    /**
     * @brief Read the MDF file header.
     * @return `true` if successful.
      * @details Reads file-level metadata and the root MDF hierarchy.
      * @see GetHeader
      * @see ReadMeasurementInfo
     */
    bool ReadHeader () { return MdfReaderReadHeader ( reader ); }

    /**
     * @brief Read measurement information from the file.
     * @return `true` if successful.
      * @details Loads data-group and channel-group metadata required before
      * retrieving sample payload data.
      * @see GetDataGroup
      * @see ReadData
     */
    bool ReadMeasurementInfo () { return MdfReaderReadMeasurementInfo ( reader ); }

    /**
     * @brief Read all file content except raw measurement data.
     * @return `true` if successful.
     * @details Convenience step that loads all metadata blocks while deferring
     * heavy sample payload reads.
     * @see ReadHeader
     * @see ReadMeasurementInfo
     */
    bool ReadEverythingButData () {
      return MdfReaderReadEverythingButData ( reader );
    }

    /**
     * @brief Read raw measurement data for a data group.
     * @param group Data group wrapper.
     * @return `true` if successful.
     * @details Loads the sample records for one data group so channel
     * observers can read values.
     * @see GetDataGroup
     * @see MdfChannelObserver
     */
    bool ReadData ( MdfDataGroup group ) {
      return MdfReaderReadData ( reader, group.GetDataGroup () );
    }
  };
}  // namespace MdfLibrary