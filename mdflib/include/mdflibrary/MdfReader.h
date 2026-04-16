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
   * @ingroup mdflibrary
   */
  class MdfReader {
  private:
    mdf::MdfReader* reader;

  public:
    /**
     * @brief Open an MDF file for reading.
     * @param filename Path to the MDF file.
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
     */
    bool IsOk () { return MdfReaderIsOk ( reader ); }

    /**
     * @brief Returns the file wrapper.
     * @return `MdfFile` wrapper.
     */
    const MdfFile GetFile () const { return MdfFile ( MdfReaderGetFile ( reader ) ); }

    /**
     * @brief Returns the header wrapper.
     * @return `MdfHeader` wrapper.
     */
    MdfHeader GetHeader () const { return MdfHeader ( MdfReaderGetHeader ( reader ) ); }

    /**
     * @brief Returns a data group wrapper by index.
     * @param index Data group index.
     * @return `MdfDataGroup` wrapper.
     */
    const MdfDataGroup GetDataGroup ( size_t index ) {
      return MdfDataGroup ( MdfReaderGetDataGroup ( reader, index ) );
    }

    /**
     * @brief Open the reader.
     * @return `true` if the file was opened successfully.
     */
    bool Open () { return MdfReaderOpen ( reader ); }

    /**
     * @brief Close the reader.
     */
    void Close () { MdfReaderClose ( reader ); }

    /**
     * @brief Read the MDF file header.
     * @return `true` if successful.
     */
    bool ReadHeader () { return MdfReaderReadHeader ( reader ); }

    /**
     * @brief Read measurement information from the file.
     * @return `true` if successful.
     */
    bool ReadMeasurementInfo () { return MdfReaderReadMeasurementInfo ( reader ); }

    /**
     * @brief Read all file content except raw measurement data.
     * @return `true` if successful.
     */
    bool ReadEverythingButData () {
      return MdfReaderReadEverythingButData ( reader );
    }

    /**
     * @brief Read raw measurement data for a data group.
     * @param group Data group wrapper.
     * @return `true` if successful.
     */
    bool ReadData ( MdfDataGroup group ) {
      return MdfReaderReadData ( reader, group.GetDataGroup () );
    }
  };
}  // namespace MdfLibrary