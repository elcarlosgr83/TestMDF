/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "mdf/iattachment.h"
#include "mdf/iblock.h"
#include "mdf/evcomment.h"


namespace mdf {
  /** \brief Type of event. */
  enum class EventType : uint8_t {
    RecordingPeriod = 0,       ///< Specifies a recording period (range).
    RecordingInterrupt = 1,    ///< The recording was interrupted.
    AcquisitionInterrupt = 2,  ///< The data acquisition was interrupted.
    StartRecording = 3,        ///< Start recording event.
    StopRecording = 4,         ///< Stop recording event.
    Trigger = 5,               ///< Generic event (no range).
    Marker = 6                 ///< Another generic event (maybe range).
  };

  /** \brief Type of synchronization value (default time) */
  enum class SyncType : uint8_t {
    SyncTime = 1,      ///< Sync value represent time (s).
    SyncAngle = 2,     ///< Sync value represent angle (rad).
    SyncDistance = 3,  ///< Sync value represent distance (m).
    SyncIndex = 4,     ///< Sync value represent sample index.
  };

  /** \brief Type of range. */
  enum class RangeType : uint8_t {
    RangePoint = 0,  ///< Defines a point
    RangeStart = 1,  ///< First in a range.
    RangeEnd = 2     ///< Last in a range.
  };

  /** \brief Type of cause. */
  enum class EventCause : uint8_t {
    CauseOther = 0,   ///< Unknown source.
    CauseError = 1,   ///< An error generated this event.
    CauseTool = 2,    ///< The tool generated this event.
    CauseScript = 3,  ///< A script generated this event.
    CauseUser = 4,    ///< A user generated this event.
  };

  /** \brief Interface against an event block.
   *
   * The event (EV) block is used to store events text and data. It is rather
   * flexible block type which makes it difficult to simplify.
   */

  class IEvent : public IBlock {
  public:
    /** \brief Sets the event name.
     * @param name Event name.
     */
    /**
     * @brief Name.
     * @param name name.
     * @return virtual void.
     */
    virtual void Name ( const std::string& name ) = 0;
    /**
     * @brief Name.
     * @return [ [ nodiscard ] ] virtual std::string&.
     */
    [ [ nodiscard ] ] virtual const std::string& Name () const = 0; ///< Name.

      /** \brief Sets the event group name.
       * @param group_name Group name.
       */
      /**
       * @brief GroupName.
       * @param group_name group_name.
       * @return virtual void.
       */
      virtual void GroupName ( const std::string& group_name ) = 0;
      /** \brief Returns the group name. */
    [ [ nodiscard ] ] virtual const std::string& GroupName () const = 0;


      /** \brief Sets the event type.
       * @param event_type Event type value.
       */
      /**
       * @brief Type.
       * @param event_type event_type.
       * @return virtual void.
       */
      virtual void Type ( EventType event_type ) = 0; ///< Sets type of event.
    /**
     * @brief Type.
     * @return [ [ nodiscard ] ] virtual EventType.
     */
    [ [ nodiscard ] ] virtual EventType Type () const = 0; ///< Type of event.
    /**
     * @brief TypeToString.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string TypeToString () const; ///< Typ as string.

      /** \brief Sets the sync type.
       * @param sync_type Synchronization type.
       */
      /**
       * @brief Sync.
       * @param sync_type sync_type.
       * @return virtual void.
       */
      virtual void Sync ( SyncType sync_type ) = 0;
    /**
     * @brief Sync.
     * @return [ [ nodiscard ] ] virtual SyncType.
     */
    [ [ nodiscard ] ] virtual SyncType Sync () const = 0; ///< Type of sync.

      /** \brief Sets the range type.
       * @param range_type Range type.
       */
      /**
       * @brief Range.
       * @param range_type range_type.
       * @return virtual void.
       */
      virtual void Range ( RangeType range_type ) = 0;
    /**
     * @brief Range.
     * @return [ [ nodiscard ] ] virtual RangeType.
     */
    [ [ nodiscard ] ] virtual RangeType Range () const = 0; ///< Type of range.
    /**
     * @brief RangeToString.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string RangeToString () const; ///< Range to string.

      /** \brief Sets the event cause.
       * @param cause Event cause.
       */
      /**
       * @brief Cause.
       * @param cause cause.
       * @return virtual void.
       */
      virtual void Cause ( EventCause cause ) = 0;
    /**
     * @brief Cause.
     * @return [ [ nodiscard ] ] virtual EventCause.
     */
    [ [ nodiscard ] ] virtual EventCause Cause () const = 0; ///< Cause of event.
    /**
     * @brief CauseToString.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string CauseToString () const; ///< Cause to string.

      /** \brief Sets the creator index.
       * @param index Creator index.
       */
      /**
       * @brief CreatorIndex.
       * @param index index.
       * @return virtual void.
       */
      virtual void CreatorIndex ( size_t index ) = 0;
    /**
     * @brief CreatorIndex.
     * @return [ [ nodiscard ] ] virtual size_t.
     */
    [ [ nodiscard ] ] virtual size_t CreatorIndex () const = 0; ///< Creator index.

      /** \brief Sets the sync value.
       * @param value Sync value.
       */
      /**
       * @brief SyncValue.
       * @param value value.
       * @return virtual void.
       */
      virtual void SyncValue ( int64_t value ) = 0;
    /**
     * @brief SyncValue.
     * @return [ [ nodiscard ] ] virtual int64_t.
     */
    [ [ nodiscard ] ] virtual int64_t SyncValue () const = 0; ///< Sync value.

      /** \brief Sets the sync factor.
       * @param factor Sync factor.
       */
      /**
       * @brief SyncFactor.
       * @param factor factor.
       * @return virtual void.
       */
      virtual void SyncFactor ( double factor ) = 0;
    /**
     * @brief SyncFactor.
     * @return [ [ nodiscard ] ] virtual double.
     */
    [ [ nodiscard ] ] virtual double SyncFactor () const = 0; ///< Sync factor.
    /**
     * @brief ValueToString.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ValueToString () const; ///< Sync value as string.

      /** \brief Sets the parent event.
       * @param parent Parent event object.
       */
      /**
       * @brief ParentEvent.
       * @param parent parent.
       * @return virtual void.
       */
      virtual void ParentEvent ( const IEvent* parent ) = 0;
      /** \brief Returns the parent event. */
    [ [ nodiscard ] ] virtual const IEvent* ParentEvent () const = 0;

      /** \brief Sets the range event.
       * @param range_event Range event object.
       */
      /**
       * @brief RangeEvent.
       * @param range_event range_event.
       * @return virtual void.
       */
      virtual void RangeEvent ( const IEvent* range_event ) = 0;
      /** \brief Returns the range. */
    [ [ nodiscard ] ] virtual const IEvent* RangeEvent () const = 0;

      /** \brief Adds a scope reference.
       * @param scope Scope pointer to reference.
       */
      /**
       * @brief AddScope.
       * @param scope scope.
       * @return virtual void.
       */
      virtual void AddScope ( const void* scope ) = 0;
      /** \brief Returns referenced CN and CG blocks. */
    [ [ nodiscard ] ] virtual const std::vector<const void*>& Scopes () const = 0;

      /** \brief Adds an attachment reference.
       * @param attachment Attachment to reference.
       */
      /**
       * @brief AddAttachment.
       * @param attachment attachment.
       * @return virtual void.
       */
      virtual void AddAttachment ( const IAttachment* attachment ) = 0;
      /** \brief Returns a list of attachment references. */
    [ [ nodiscard ] ] virtual const std::vector<const IAttachment*>& Attachments ()
      const = 0;

      /** \brief Returns an interface against an MD4 block.
       * @return Pointer to a meta data block.
       */
    /**
     * @brief CreateMetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData () = 0;

      /** \brief Returns a constant interface against an MD4 block.
       * @return Pointer to a meta data block or nullptr.
       */
    /**
     * @brief MetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual const IMetaData* MetaData () const = 0;

      /** \brief Sets the event description.
       * @param description Event description text.
       */
      /**
       * @brief Description.
       * @param description description.
       */
      void Description ( const std::string& description );
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Description () const; ///< Returns description.

      /** \brief Sets the pre-trigger time.
       * @param pre_trig Pre-trigger time in seconds.
       */
      /**
       * @brief PreTrig.
       * @param pre_trig pre_trig.
       */
      void PreTrig ( double pre_trig );

    /**
     * @brief PreTrig.
     * @param s s.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double PreTrig () const; ///< Returns the pre-trig value (s).

      /** \brief Sets the post-trigger time.
       * @param post_trig Post-trigger time in seconds.
       */
      /**
       * @brief PostTrig.
       * @param post_trig post_trig.
       */
      void PostTrig ( double post_trig );

    /**
     * @brief PostTrig.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double PostTrig ()
      const; ///< Returns the post-trig value (s).

      /** \brief Sets the event comment block.
       * @param ev_comment Event comment object.
       */
      /**
       * @brief SetEvComment.
       * @param ev_comment ev_comment.
       */
      void SetEvComment ( const EvComment& ev_comment );
      /** \brief Retrieves the event comment block.
       * @param ev_comment Receives the event comment object.
       */
      /**
       * @brief GetEvComment.
       * @param ev_comment ev_comment.
       */
      void GetEvComment ( EvComment& ev_comment ) const;
  };

  }  // namespace mdf