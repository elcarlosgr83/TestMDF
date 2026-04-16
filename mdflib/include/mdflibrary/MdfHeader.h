/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
/**
 * @file MdfHeader.h
 * @brief C++ wrapper for MDF file header metadata.
 *
 * `MdfLibrary::MdfHeader` provides access to measurement-level metadata,
 * attachments, events, file history and nested data groups.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "MdfDataGroup.h"
#include "MdfEvent.h"
#include "MdfFileHistory.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfHeader
   * @brief Wrapper for MDF file header data.
   *
   * Provides access to measurement metadata, author information, attachments,
   * events, file history and contained data groups.
   */
  class MdfHeader {
  private:
    mdf::IHeader* header;

  public:
    /**
     * @brief Wrap an existing header handle.
     * @param header Low-level header pointer.
     */
    MdfHeader ( mdf::IHeader* header ) : header ( header ) {
      if ( header == nullptr ) {
        throw std::runtime_error ( "MdfHeader Init failed" );
      }
    }

    /**
     * @brief Wrap a const header handle.
     * @param header Low-level const header pointer.
     */
    MdfHeader ( const mdf::IHeader* header )
      : MdfHeader ( const_cast<mdf::IHeader*> ( header ) ) {}

    ~MdfHeader () { header = nullptr; }

    /**
     * @brief Returns the header index.
     * @return Header index.
     */
    int64_t GetIndex () const { return MdfHeaderGetIndex ( header ); }

    /**
     * @brief Returns the header description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfHeaderGetDescription ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetDescription ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the header description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) {
      MdfHeaderSetDescription ( header, desc );
    }

    /**
     * @brief Returns the author name.
     * @return Author string.
     */
    std::string GetAuthor () const {
      std::string str ( MdfHeaderGetAuthor ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetAuthor ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the author name.
     * @param author Author string.
     */
    void SetAuthor ( const char* author ) { MdfHeaderSetAuthor ( header, author ); }

    /**
     * @brief Returns the department name.
     * @return Department string.
     */
    std::string GetDepartment () const {
      std::string str ( MdfHeaderGetDepartment ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetDepartment ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the department name.
     * @param department Department string.
     */
    void SetDepartment ( const char* department ) {
      MdfHeaderSetDepartment ( header, department );
    }

    /**
     * @brief Returns the project name.
     * @return Project string.
     */
    std::string GetProject () const {
      std::string str ( MdfHeaderGetProject ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetProject ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the project name.
     * @param project Project string.
     */
    void SetProject ( const char* project ) { MdfHeaderSetProject ( header, project ); }

    /**
     * @brief Returns the subject string.
     * @return Subject string.
     */
    std::string GetSubject () const {
      std::string str ( MdfHeaderGetSubject ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetSubject ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the subject string.
     * @param subject Subject string.
     */
    void SetSubject ( const char* subject ) { MdfHeaderSetSubject ( header, subject ); }

    /**
     * @brief Returns the measurement identifier.
     * @return Measurement ID.
     */
    std::string GetMeasurementId () const {
      std::string str ( MdfHeaderGetMeasurementId ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetMeasurementId ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the measurement identifier.
     * @param uuid Measurement ID string.
     */
    void SetMeasurementId ( const char* uuid ) {
      MdfHeaderSetMeasurementId ( header, uuid );
    }

    /**
     * @brief Returns the recorder identifier.
     * @return Recorder ID string.
     */
    std::string GetRecorderId () const {
      std::string str ( MdfHeaderGetRecorderId ( header, nullptr ) + 1, '\0' );
      str.resize ( MdfHeaderGetRecorderId ( header, str.data () ) );
      return str;
    }

    /**
     * @brief Set the recorder identifier.
     * @param uuid Recorder ID string.
     */
    void SetRecorderId ( const char* uuid ) { MdfHeaderSetRecorderId ( header, uuid ); }

    /**
     * @brief Returns the recorder index.
     * @return Recorder index.
     */
    int64_t GetRecorderIndex () const { return MdfHeaderGetRecorderIndex ( header ); }

    /**
     * @brief Set the recorder index.
     * @param index Recorder index.
     */
    void SetRecorderIndex ( int64_t index ) {
      MdfHeaderSetRecorderIndex ( header, index );
    }

    /**
     * @brief Returns the measurement start time.
     * @return Start time.
     */
    uint64_t GetStartTime () const { return MdfHeaderGetStartTime ( header ); }

    /**
     * @brief Set the measurement start time.
     * @param time Start time.
     */
    void SetStartTime ( uint64_t time ) { MdfHeaderSetStartTime ( header, time ); }

    /**
     * @brief Returns whether a start angle is used.
     * @return `true` when start angle is used.
     */
    bool IsStartAngleUsed () { return MdfHeaderIsStartAngleUsed ( header ); }

    /**
     * @brief Returns the start angle.
     * @return Start angle.
     */
    double GetStartAngle () const { return MdfHeaderGetStartAngle ( header ); }

    /**
     * @brief Set the start angle.
     * @param angle Start angle.
     */
    void SetStartAngle ( double angle ) { MdfHeaderSetStartAngle ( header, angle ); }

    /**
     * @brief Returns whether a start distance is used.
     * @return `true` when start distance is used.
     */
    bool IsStartDistanceUsed () { return MdfHeaderIsStartDistanceUsed ( header ); }

    /**
     * @brief Returns the start distance.
     * @return Start distance.
     */
    double GetStartDistance () const { return MdfHeaderGetStartDistance ( header ); }

    /**
     * @brief Set the start distance.
     * @param distance Start distance.
     */
    void SetStartDistance ( double distance ) {
      MdfHeaderSetStartDistance ( header, distance );
    }

    /**
     * @brief Returns the header metadata.
     * @return `MdfMetaData` wrapper.
     */
    const MdfMetaData GetMetaData () const {
      return MdfHeaderGetMetaData ( header );
    }

    /**
     * @brief Returns the attachments for the header.
     * @return Vector of `MdfAttachment` wrappers.
     */
    std::vector<MdfAttachment> GetAttachments () const {
      size_t count = MdfHeaderGetAttachments ( header, nullptr );

      if ( count <= 0 )
        return {};

      auto pAttachments = new mdf::IAttachment* [ count ];

      MdfHeaderGetAttachments ( header, pAttachments );

      std::vector<MdfAttachment> attachments;

      for ( size_t i = 0; i < count; i++ ) {
        attachments.push_back ( pAttachments [ i ] );
      }

      delete [] pAttachments;
      return attachments;
    }

    /**
     * @brief Returns the file history entries.
     * @return Vector of `MdfFileHistory` wrappers.
     */
    std::vector<MdfFileHistory> GetFileHistorys () const {
      size_t count = MdfHeaderGetFileHistorys ( header, nullptr );

      if ( count <= 0 )
        return {};

      auto pFileHistorys = new mdf::IFileHistory* [ count ];

      MdfHeaderGetFileHistorys ( header, pFileHistorys );

      std::vector<MdfFileHistory> fileHistorys;

      for ( size_t i = 0; i < count; i++ ) {
        fileHistorys.push_back ( pFileHistorys [ i ] );
      }

      delete [] pFileHistorys;
      return fileHistorys;
    }

    /**
     * @brief Returns the events for the header.
     * @return Vector of `MdfEvent` wrappers.
     */
    std::vector<MdfEvent> GetEvents () const {
      size_t count = MdfHeaderGetEvents ( header, nullptr );

      if ( count <= 0 )
        return {};

      auto pEvents = new mdf::IEvent* [ count ];

      MdfHeaderGetEvents ( header, pEvents );

      std::vector<MdfEvent> events;

      for ( size_t i = 0; i < count; i++ ) {
        events.push_back ( pEvents [ i ] );
      }

      delete [] pEvents;
      return events;
    }

    /**
     * @brief Returns the data groups for the header.
     * @return Vector of `MdfDataGroup` wrappers.
     */
    std::vector<MdfDataGroup> GetDataGroups () const {
      size_t count = MdfHeaderGetDataGroups ( header, nullptr );

      if ( count <= 0 )
        return {};

      auto pDataGroups = new mdf::IDataGroup* [ count ];

      MdfHeaderGetDataGroups ( header, pDataGroups );

      std::vector<MdfDataGroup> dataGroups;

      for ( size_t i = 0; i < count; i++ ) {
        dataGroups.push_back ( pDataGroups [ i ] );
      }

      delete [] pDataGroups;
      return dataGroups;
    }

    /**
     * @brief Returns the last data group.
     * @return `MdfDataGroup` wrapper.
     */
    MdfDataGroup GetLastDataGroup () { return MdfHeaderGetLastDataGroup ( header ); }

    /**
     * @brief Create header metadata.
     * @return `MdfMetaData` wrapper.
     */
    MdfMetaData CreateMetaData () { return MdfHeaderCreateMetaData ( header ); }

    /**
     * @brief Create an attachment.
     * @return `MdfAttachment` wrapper.
     */
    MdfAttachment CreateAttachment () { return MdfHeaderCreateAttachment ( header ); }

    /**
     * @brief Create a file history entry.
     * @return `MdfFileHistory` wrapper.
     */
    MdfFileHistory CreateFileHistory () {
      return MdfHeaderCreateFileHistory ( header );
    }

    /**
     * @brief Create an event.
     * @return `MdfEvent` wrapper.
     */
    MdfEvent CreateEvent () { return MdfHeaderCreateEvent ( header ); }

    /**
     * @brief Create a data group.
     * @return `MdfDataGroup` wrapper.
     */
    MdfDataGroup CreateDataGroup () { return MdfHeaderCreateDataGroup ( header ); }
  };
}  // namespace MdfLibrary