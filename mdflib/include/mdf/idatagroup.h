/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <string>
#include <vector>
#include <map>

#include "mdf/iblock.h"
#include "mdf/dgcomment.h"

namespace mdf {

  /**
   * @brief IMetaData class definition.
   */
  class IMetaData;
  /**
   * @brief ISampleObserver class definition.
   */
  class ISampleObserver;
  /**
   * @brief IChannelGroup class definition.
   */
  class IChannelGroup;
  /**
   * @brief IChannel class definition.
   */
  class IChannel;
  /** \brief Interface to a data group (DG) block.
   *
   * The data group block is the entry point for a measurement. The header (HD)
   * block is the entry point for a test. A test consist of one or more
   * measurements (DG).
   *
   * Each measurement is defined by one or more channel groups (CG). The channel
   * group in turn, consist of one or more channels. The group have an unique
   * record ID.
   *
   * A record is a byte array with fixed length and hold one sample for each
   * channel in the group. The DG block also points to the data blocks (DT) which
   * is an array of sample records.
   *
   * In MDF version 3, data was always stored as raw bytes in a DT block. In
   * version 4 the DT block may be split, reorganized and compressed.
   *
   */

  class IDataGroup : public IBlock {
  public:

    /** \brief Sets the descriptive text for the measurement.
     *
     * @param desc Description text for the data group.
     */
    /**
     * @brief Description.
     * @param desc desc.
     * @return virtual void.
     */
    virtual void Description ( const std::string& desc );

    /** \brief Returns the descriptive text for the measurement.
     *
     * @return Description text.
     */
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Description () const;

      /** \brief Sets the size of the record ID in bytes.
       *
       * Note that the record ID and its size are automatically set when
       * writing MDF files.
       * @param id_size Record ID size in bytes.
       */
      /**
       * @brief RecordIdSize.
       * @param id_size id_size.
       * @return virtual void.
       */
      virtual void RecordIdSize ( uint8_t id_size );

      /** \brief Returns the record ID size in bytes.
       *
       * @return Record ID size in bytes.
       */
    /**
     * @brief RecordIdSize.
     * @return [ [ nodiscard ] ] virtual uint8_t.
     */
    [ [ nodiscard ] ] virtual uint8_t RecordIdSize () const;

      /** \brief Returns a list of channel groups.
       *
       * @return Vector of channel group pointers.
       */
    /**
     * @brief ChannelGroups.
     * @return [ [ nodiscard ] ] virtual std::vector<IChannelGroup*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IChannelGroup*> ChannelGroups () const =
      0;

      /** \brief Create a new empty channel group.
       *
       * @return Pointer to the newly created channel group.
       */
    /**
     * @brief CreateChannelGroup.
     * @return [ [ nodiscard ] ] virtual IChannelGroup*.
     */
    [ [ nodiscard ] ] virtual IChannelGroup* CreateChannelGroup () = 0;

      /** \brief Create a new channel group or return the existing group.
       *
       * @param name Full name of the group.
       * @return Existing or newly created channel group.
       */
    /**
     * @brief CreateChannelGroup.
     * @param name name.
     * @return [ [ nodiscard ] ] IChannelGroup*.
     */
    [ [ nodiscard ] ] IChannelGroup* CreateChannelGroup (
      const std::string_view& name );

      /** \brief Returns a channel group by its full name or sub-string.
       *
       * The function return a channel group by its full name. If the full name
       * search fails, it search on a sub-string instead. The sub-string must
       * be larger than 3 characters.
       * @param name Full name of the group or a sub-string.
       * @return Pointer to the matching channel group or nullptr at no match.
       */
    /**
     * @brief GetChannelGroup.
     * @param name name.
     * @return [ [ nodiscard ] ] IChannelGroup*.
     */
    [ [ nodiscard ] ] IChannelGroup* GetChannelGroup ( const std::string_view& 
      name ) const;

      /** \brief Returns a channel group by its record id.
       * @param record_id Group record identifier.
       * @return Pointer to the matching channel group or nullptr if not found.
       */
    /**
     * @brief GetChannelGroup.
     * @param record_id record_id.
     * @return [ [ nodiscard ] ] IChannelGroup*.
     */
    [ [ nodiscard ] ] IChannelGroup* GetChannelGroup ( uint64_t record_id ) const;

      /** \brief Create or return the existing meta-data (MD) block.
       *
       * @return Pointer to the created or existing IMetaData block.
       */
    /**
     * @brief CreateMetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData ();

      /** \brief Returns the existing meta-data (MD) block if it exists.
       *
       * @return Pointer to the IMetaData block or nullptr.
       */
    /**
     * @brief MetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* MetaData () const;

      /** \brief Internal function that attaches a sample observer to the
       *  measurement block.
       * @param observer Observer to attach.
       */
      /**
       * @brief AttachSampleObserver.
       * @param observer observer.
       */
      void AttachSampleObserver ( ISampleObserver* observer ) const;
      /** \brief Detach an observer from the measurement.
       * @param observer Observer to detach.
       */
      /**
       * @brief DetachSampleObserver.
       * @param observer observer.
       */
      void DetachSampleObserver ( const ISampleObserver* observer ) const;
      /** \brief Detaches all observers from the measurement. */
      void DetachAllSampleObservers () const;
      /** \brief Notifies the observers that a new sample record has been read.
       * @param sample Sample index.
       * @param record_id Record identifier.
       * @param record Record bytes.
       * @return True if any observer handled the sample notification.
       */
      /**
       * @brief NotifySampleObservers.
       * @param sample sample.
       * @param record_id record_id.
       * @param record record.
       * @return bool.
       */
      bool NotifySampleObservers ( uint64_t sample, uint64_t record_id,
      const std::vector<uint8_t>& record ) const;

      /** \brief Clear all temporary sample and data buffers.
       *
       * Clear all sample and signal data buffers. Call this function
       * when no need of any signal data (SD) or sample reduction (SR) data
       * are needed. This reduce memory usage if more DG blocks should
       * read in data bytes.
       */
      /**
       * @brief ClearData.
       * @return virtual void.
       */
      virtual void ClearData ();

      /** \brief Mark the DG block data as read.
       *
       * @param mark_as_read True to mark the data as read.
       */
      /**
       * @brief SetAsRead.
       * @param mark_as_read mark_as_read.
       */
      void SetAsRead ( bool mark_as_read = true ) const {
        mark_as_read_ = mark_as_read;
    }

    /** \brief Returns true if no samples have been stored yet.
     *
     * @return True if the data group is empty.
     */
    /**
     * @brief IsEmpty.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsEmpty () const;

      /** \brief Returns true if the DG block data has been read, not the DG block
       * itself.
       *
       * @return True if the data group has been marked as read.
       */
    [ [ nodiscard ] ] bool IsRead () const { return mark_as_read_; }

    /** \brief Support function that return the first CG block that contains
     * a specific CN block.
     * @param channel Channel to search for.
     * @return Parent channel group containing the channel, or nullptr.
     */
    /**
     * @brief FindParentChannelGroup.
     * @param channel channel.
     * @return [ [ nodiscard ] ] virtual IChannelGroup*.
     */
    [ [ nodiscard ] ] virtual IChannelGroup* FindParentChannelGroup (
      const IChannel &channel ) const = 0;

      /**
       * \brief Checks if this data group subscribes on a specific record.
       * @param record_id Record ID of the channel group.
       * @return True if the observer list subscribe on this channel group.
       */
    [ [ nodiscard ] ] bool IsSubscribingOnRecord ( uint64_t record_id ) const;

      /**
      * \brief Checks if this data group subscribes on a specific channel.
      * @param channel Reference to the channel.
      * @return True if the observer list subscribe on this channel.
      */
    [ [ nodiscard ] ] bool IsSubscribingOnChannel ( const IChannel& channel ) const;

      /**
      * \brief Checks if this data group subscribes on a specific channel's VLSD raw data.
      * @param channel Reference to the channel.
      * @return True if the observer list subscribe on this channel's VLSD raw data.
      */
    [ [ nodiscard ] ] bool IsSubscribingOnChannelVlsd ( const IChannel& channel )
      const;

      /** \brief Sets the DG comment block.
       *
       * @param dg_comment DG comment object.
       */
      /**
       * @brief SetDgComment.
       * @param dg_comment dg_comment.
       */
      void SetDgComment ( const DgComment& dg_comment );

      /** \brief Retrieves the DG comment block.
       *
       * @param dg_comment Receives the DG comment object.
       */
      /**
       * @brief GetDgComment.
       * @param dg_comment dg_comment.
       */
      void GetDgComment ( DgComment& dg_comment ) const;

      /**
       * @brief MandatoryMembersOnly.
       * @param mandatory_only mandatory_only.
       */
      void MandatoryMembersOnly ( bool mandatory_only ) const {
        mandatory_members_only_ = mandatory_only;
    }

    /**
     * @brief MandatoryMembersOnly.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool MandatoryMembersOnly () const {
        return mandatory_members_only_;
    }
  protected:
    mutable std::vector<ISampleObserver*> observer_list_; ///< List of observers.

    /** \brief The fast observer list is used internally when reading data.
     *
     */
    std::map<uint64_t, std::vector<ISampleObserver*>> fast_observer_list_;

    /**
     * @brief ~IDataGroup.
     */
    ~IDataGroup () override = default; ///< Default destructor

    /** \brief The function optimize the observer list before reading data.
     *
     * The function is called before reading any data in the file. The purpose is
     * optimize the read speed of files with many sample. The function is used
     * internally only.
     */
    /**
     * @brief InitFastObserverList.
     */
    void InitFastObserverList ();

  private:
    mutable bool mark_as_read_ = false; ///< True if the data block has been read.
    mutable bool mandatory_members_only_ = false;


  };

  }  // namespace mdf