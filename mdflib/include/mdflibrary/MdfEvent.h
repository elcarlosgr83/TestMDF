/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
/**
 * @file MdfEvent.h
 * @brief C++ wrapper for MDF event objects.
 *
 * `MdfLibrary::MdfEvent` exposes event timestamps, descriptions and referenced
 * attachments or metadata.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "MdfAttachment.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfEvent
   * @brief Wrapper for MDF events.
   *
   * Events are annotations attached to an MDF file that contain timing,
   * grouping, cause and metadata information.
   */
  class MdfEvent {
  private:
    mdf::IEvent* event;

  public:
    /**
     * @brief Wrap an existing event handle.
     * @param event Low-level event pointer.
     */
    MdfEvent ( mdf::IEvent* event ) : event ( event ) {
      if ( event == nullptr ) {
        throw std::runtime_error ( "MdfEvent Init failed" );
      }
    }

    /**
     * @brief Wrap a const event handle.
     * @param event Low-level const event pointer.
     */
    MdfEvent ( const mdf::IEvent* event )
      : MdfEvent ( const_cast<mdf::IEvent*> ( event ) ) {}

    ~MdfEvent () { event = nullptr; }

    /**
     * @brief Returns the event index.
     * @return Event index.
     */
    int64_t GetIndex () const { return MdfEventGetIndex ( event ); }

    /**
     * @brief Returns the event name.
     * @return Name string.
     */
    std::string GetName () const {
      std::string str ( MdfEventGetName ( event, nullptr ) + 1, '\0' );
      str.resize ( MdfEventGetName ( event, str.data () ) );
      return str;
    }

    /**
     * @brief Set the event name.
     * @param name Name string.
     */
    void SetName ( const char* name ) { MdfEventSetName ( event, name ); }

    /**
     * @brief Returns the event description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfEventGetDescription ( event, nullptr ) + 1, '\0' );
      str.resize ( MdfEventGetDescription ( event, str.data () ) );
      return str;
    }

    /**
     * @brief Set the event description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) { MdfEventSetDescription ( event, desc ); }

    /**
     * @brief Returns the event group name.
     * @return Group name string.
     */
    std::string GetGroupName () const {
      std::string str ( MdfEventGetGroupName ( event, nullptr ) + 1, '\0' );
      str.resize ( MdfEventGetGroupName ( event, str.data () ) );
      return str;
    }

    /**
     * @brief Set the event group name.
     * @param group Group name string.
     */
    void SetGroupName ( const char* group ) { MdfEventSetGroupName ( event, group ); }

    /**
     * @brief Returns the event type.
     * @return Event type.
     */
    EventType GetType () const { return MdfEventGetType ( event ); }

    /**
     * @brief Set the event type.
     * @param type Event type.
     */
    void SetType ( EventType type ) { MdfEventSetType ( event, type ); }

    /**
     * @brief Returns the synchronization type.
     * @return Sync type.
     */
    SyncType GetSync () const { return MdfEventGetSync ( event ); }

    /**
     * @brief Set the synchronization type.
     * @param type Sync type.
     */
    void SetSync ( SyncType type ) { MdfEventSetSync ( event, type ); }

    /**
     * @brief Returns the range type.
     * @return Range type.
     */
    RangeType GetRange () const { return MdfEventGetRange ( event ); }

    /**
     * @brief Set the range type.
     * @param type Range type.
     */
    void SetRange ( RangeType type ) { MdfEventSetRange ( event, type ); }

    /**
     * @brief Returns the event cause.
     * @return Event cause.
     */
    EventCause GetCause () const { return MdfEventGetCause ( event ); }

    /**
     * @brief Set the event cause.
     * @param cause Event cause.
     */
    void SetCause ( EventCause cause ) { MdfEventSetCause ( event, cause ); }

    /**
     * @brief Returns the creator index.
     * @return Creator index.
     */
    int64_t GetCreatorIndex () const { return MdfEventGetCreatorIndex ( event ); }

    /**
     * @brief Set the creator index.
     * @param index Creator index.
     */
    void SetCreatorIndex ( int64_t index ) { MdfEventSetCreatorIndex ( event, index ); }

    /**
     * @brief Returns the sync value.
     * @return Sync value.
     */
    int64_t GetSyncValue () const { return MdfEventGetSyncValue ( event ); }

    /**
     * @brief Set the sync value.
     * @param value Sync value.
     */
    void SetSyncValue ( int64_t value ) { MdfEventSetSyncValue ( event, value ); }

    /**
     * @brief Set the sync factor.
     * @param factor Sync factor.
     */
    void SetSyncFactor ( double factor ) { MdfEventSetSyncFactor ( event, factor ); }

    /**
     * @brief Returns the parent event.
     * @return Parent `MdfEvent` wrapper.
     */
    const MdfEvent GetParentEvent () const {
      return MdfEventGetParentEvent ( event );
    }

    /**
     * @brief Set the parent event.
     * @param parent Parent event wrapper.
     */
    void SetParentEvent ( MdfEvent parent ) {
      MdfEventSetParentEvent ( event, parent.event );
    }

    /**
     * @brief Returns the range event.
     * @return Range `MdfEvent` wrapper.
     */
    const MdfEvent GetRangeEvent () const { return MdfEventGetRangeEvent ( event ); }

    /**
     * @brief Set the range event.
     * @param range Range event wrapper.
     */
    void SetRangeEvent ( MdfEvent range ) {
      MdfEventSetRangeEvent ( event, range.event );
    }

    /**
     * @brief Returns the event attachments.
     * @return Vector of `MdfAttachment` wrappers.
     */
    std::vector<MdfAttachment> GetAttachments () const {
      size_t count = MdfEventGetAttachments ( event, nullptr );

      if ( count <= 0 )
        return {};

      auto pAttachments = new const mdf::IAttachment* [ count ];

      MdfEventGetAttachments ( event, pAttachments );

      std::vector<MdfAttachment> attachments;

      for ( size_t i = 0; i < count; i++ ) {
        attachments.push_back ( pAttachments [ i ] );
      }

      delete [] pAttachments;
      return attachments;
    }

    /**
     * @brief Returns the pre-trigger time.
     * @return Pre-trigger time.
     */
    double GetPreTrig () const { return MdfEventGetPreTrig ( event ); }

    /**
     * @brief Set the pre-trigger time.
     * @param time Pre-trigger time.
     */
    void SetPreTrig ( double time ) { MdfEventSetPreTrig ( event, time ); }

    /**
     * @brief Returns the post-trigger time.
     * @return Post-trigger time.
     */
    double GetPostTrig () const { return MdfEventGetPostTrig ( event ); }

    /**
     * @brief Set the post-trigger time.
     * @param time Post-trigger time.
     */
    void SetPostTrig ( double time ) { MdfEventSetPostTrig ( event, time ); }

    /**
     * @brief Returns the event metadata.
     * @return `MdfMetaData` wrapper.
     */
    const MdfMetaData GetMetaData () const { return MdfEventGetMetaData ( event ); }

    /**
     * @brief Add an attachment to this event.
     * @param attachment Attachment wrapper.
     */
    void AddAttachment ( MdfAttachment attachment ) {
      MdfEventAddAttachment ( event, attachment.GetAttachment () );
    }
  };
}  // namespace MdfLibrary