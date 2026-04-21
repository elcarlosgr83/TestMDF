/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>

#include "MdfFile.h"
#include "CanMessage.h"
#include "LinMessage.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @file MdfWriter.h
   * @brief Wrapper for MDF writer operations.
   *
   * Provides a C++ interface for writing MDF files, creating data groups and
   * saving sample messages.
  *
  * Typical flow:
  * @code{.cpp}
  * MdfLibrary::MdfWriter writer(MdfWriterType::MdfBusLogger, "capture.mf4");
  * writer.SetBusType(MdfBusType::CAN);
  * writer.CreateBusLogConfiguration();
  * writer.InitMeasurement();
  * writer.StartMeasurement(start_ns);
  * // SaveSample / SaveCanMessage / SaveLinMessage ...
  * writer.StopMeasurement(stop_ns);
  * writer.FinalizeMeasurement();
  * @endcode
   *
   * @ingroup mdflibrary
   */
  class MdfWriter {
  private:
    mdf::MdfWriter* writer;

  public:
    /**
     * @brief Create an MDF writer.
     * @param type Writer type.
     * @param filename Output file path.
      * @details Initializes the low-level writer handle for one MDF output
      * stream.
      * @see InitMeasurement
      * @see FinalizeMeasurement
     */
    MdfWriter ( MdfWriterType type, const char* filename )
      : writer ( MdfWriterInit ( type, filename ) ) {
      if ( writer == nullptr ) {
        throw std::runtime_error ( "MdfWriter Init failed" );
      }
    }

    /**
     * @brief Destroy the writer.
     */
    ~MdfWriter () {
      if ( writer == nullptr ) {
        return;
      }

      MdfWriterUnInit ( writer );
      writer = nullptr;
    }

    MdfWriter ( const MdfWriter& ) = delete;

    /**
     * @brief Returns the current MDF file wrapper.
     * @return `MdfFile` wrapper.
      * @see GetHeader
      * @see CreateDataGroup
     */
    MdfFile GetFile () const { return MdfWriterGetFile ( writer ); }

    /**
     * @brief Returns the current header wrapper.
     * @return `MdfHeader` wrapper.
      * @see GetFile
      * @see CreateBusLogConfiguration
     */
    MdfHeader GetHeader () const { return MdfWriterGetHeader ( writer ); }

    /**
     * @brief Returns whether the file is newly created.
     * @return `true` if file is new.
      * @see GetFile
     */
    bool IsFileNew () const { return MdfWriterIsFileNew ( writer ); }

    /**
     * @brief Returns whether data compression is enabled.
     * @return `true` if compression is enabled.
     */
    bool GetCompressData () const { return MdfWriterGetCompressData ( writer ); }

    /**
     * @brief Enable or disable data compression.
     * @param compress Compression toggle.
     * @see GetCompressData
     */
    void SetCompressData ( bool compress ) {
      MdfWriterSetCompressData ( writer, compress );
    }

    /**
     * @brief Returns the pre-trigger time.
     * @return Pre-trigger time.
     */
    double GetPreTrigTime () const { return MdfWriterGetPreTrigTime ( writer ); }

    /**
     * @brief Set the pre-trigger time.
     * @param pre_trig_time Pre-trigger time.
     * @see GetPreTrigTime
     */
    void SetPreTrigTime ( double pre_trig_time ) {
      MdfWriterSetPreTrigTime ( writer, pre_trig_time );
    }

    /**
     * @brief Returns the start time.
     * @return Start time.
     */
    uint64_t GetStartTime () const { return MdfWriterGetStartTime ( writer ); }

    /**
     * @brief Returns the stop time.
     * @return Stop time.
     */
    uint64_t GetStopTime () const { return MdfWriterGetStopTime ( writer ); }

    /**
     * @brief Returns the bus type.
     * @return Bus type enum.
     */
    MdfBusType GetBusType () const { return MdfWriterGetBusType ( writer ); }

    /**
     * @brief Set the bus type.
     * @param type Bus type.
      * @see GetBusType
      * @see CreateBusLogConfiguration
     */
    void SetBusType ( MdfBusType type ) { MdfWriterSetBusType ( writer, type ); }

    /**
     * @brief Returns the storage type.
     * @return Storage type enum.
     */
    MdfStorageType GetStorageType () const {
      return MdfWriterGetStorageType ( writer );
    }

    /**
     * @brief Set the storage type.
     * @param type Storage type.
     * @see GetStorageType
     */
    void SetStorageType ( MdfStorageType type ) {
      MdfWriterSetStorageType ( writer, type );
    }

    /**
     * @brief Returns the maximum record length.
     * @return Maximum length.
     */
    uint32_t GetMaxLength () const { return MdfWriterGetMaxLength ( writer ); }

    /**
     * @brief Set the maximum record length.
     * @param length Maximum length.
      * @see GetMaxLength
     */
    void SetMaxLength ( uint32_t length ) { MdfWriterSetMaxLength ( writer, length ); }

    /**
     * @brief Create a bus log configuration.
     * @return `true` if creation succeeded.
      * @details Creates bus-specific channel groups/metadata according to the
      * current writer bus and storage settings.
      * @see SetBusType
      * @see SetStorageType
     */
    bool CreateBusLogConfiguration () { return MdfWriterCreateBusLogConfiguration ( writer ); }

    /**
     * @brief Create a new data group.
     * @return `MdfDataGroup` wrapper.
     * @see SaveSample
     * @see GetFile
     */
    MdfDataGroup CreateDataGroup () {
      return MdfDataGroup ( MdfWriterCreateDataGroup ( writer ) );
    }

    /**
     * @brief Save a sample for a channel group.
     * @param group Channel group wrapper.
     * @param time Timestamp.
     * @details Appends one sample event at the provided timestamp for the
     * target group.
     * @see SaveCanMessage
     * @see SaveLinMessage
     */
    void SaveSample ( MdfChannelGroup group, uint64_t time ) {
      MdfWriterSaveSample ( writer, group.GetChannelGroup (), time );
    }

    /**
     * @brief Save a CAN message sample.
     * @param group Channel group wrapper.
     * @param time Timestamp.
     * @param msg CAN message wrapper.
      * @details Serializes CAN payload fields into the configured bus logging
      * channel group.
      * @see SaveSample
      * @see SaveLinMessage
     */
    void SaveCanMessage ( const MdfChannelGroup group, uint64_t time,
                          const CanMessage& msg ) {
      MdfWriterSaveCanMessage ( writer, group.GetChannelGroup (), time,
                                msg.GetCanMessage () );
    }

    /**
     * @brief Save a LIN message sample.
     * @param group Channel group wrapper.
     * @param time Timestamp.
     * @param msg LIN message wrapper.
      * @details Serializes LIN payload fields into the configured bus logging
      * channel group.
      * @see SaveSample
      * @see SaveCanMessage
     */
    void SaveLinMessage ( const MdfChannelGroup group, uint64_t time,
                          const LinMessage& msg ) {
      MdfWriterSaveLinMessage ( writer, group.GetChannelGroup (), time,
                                msg.GetLinMessage () );
    }

    /**
     * @brief Initialize the measurement.
     * @return `true` if initialization succeeds.
      * @details Prepares internal write state before timestamps and samples are
      * appended.
      * @see StartMeasurement
      * @see FinalizeMeasurement
     */
    bool InitMeasurement () { return MdfWriterInitMeasurement ( writer ); }

    /**
     * @brief Start the measurement.
     * @param start_time Start timestamp.
     * @see InitMeasurement
     * @see StopMeasurement
     */
    void StartMeasurement ( uint64_t start_time ) {
      MdfWriterStartMeasurement ( writer, start_time );
    }

    /**
     * @brief Stop the measurement.
     * @param stop_time Stop timestamp.
     * @see StartMeasurement
     * @see FinalizeMeasurement
     */
    void StopMeasurement ( uint64_t stop_time ) {
      MdfWriterStopMeasurement ( writer, stop_time );
    }

    /**
     * @brief Finalize the measurement.
     * @return `true` if finalization succeeds.
     * @details Flushes pending data and writes final MDF end-of-measurement
     * metadata.
     * @see StopMeasurement
     * @see InitMeasurement
     */
    bool FinalizeMeasurement () { return MdfWriterFinalizeMeasurement ( writer ); }
  };
}  // namespace MdfLibrary