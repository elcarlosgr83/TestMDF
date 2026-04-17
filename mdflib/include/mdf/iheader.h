/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <optional>
#include <string>
#include <vector>

#include "mdf/iblock.h"
#include "mdf/itimestamp.h"
#include "mdf/imdftimestamp.h"
#include "mdf/hdcomment.h"

namespace mdf {

  /**
   * @brief IAttachment class definition.
   */
  class IAttachment;
  /**
   * @brief IChannelHierarchy class definition.
   */
  class IChannelHierarchy;
  /**
   * @brief IEvent class definition.
   */
  class IEvent;
  /**
   * @brief IFileHistory class definition.
   */
  class IFileHistory;
  /**
   * @brief IMetaData class definition.
   */
  class IMetaData;
  /**
   * @brief IDataGroup class definition.
   */
  class IDataGroup;

  /** \class IHeader iheader.h "mdf/iheader.h"
   * \brief Interface class against an MDF HD block
   *
   * Interface class against a header block (HD) in a MDF file. The header
   * block is the main root that holds all other blocks except the ID block.
   */

  class IHeader : public IBlock {
  public:
    /** \brief Sets the author of the file.
     *
     * Sets the author of the files.
     * @param author Author of the file.
     */
    /**
     * @brief Author.
     * @param author author.
     * @return virtual void.
     */
    virtual void Author ( const std::string& author ) = 0;

    /** \brief Returns the author of the file.
     *
     * Returns the author of the file.
     * @return Author of the file.
     */
    /**
     * @brief Author.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Author () const = 0;

      /** \brief Sets the department name.
       *
       * Sets the department name.
       * @param department Department name.
       */
      /**
       * @brief Department.
       * @param department department.
       * @return virtual void.
       */
      virtual void Department ( const std::string& department ) = 0;

      /** \brief Returns the department.
       *
       * Returns the department name.
       * @return Department name.
       */
    /**
     * @brief Department.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Department () const = 0;

      /** \brief Sets the project name.
       *
       * Sets the project name.
       * @param name Project name.
       */
      /**
       * @brief Project.
       * @param name name.
       * @return virtual void.
       */
      virtual void Project ( const std::string& name ) = 0;

      /** \brief Returns the project name.
       *
       * Returns the project name.
       * @return Project name
       */
    /**
     * @brief Project.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Project () const = 0;

      /** \brief Sets the subject of the file.
       *
       * Sets the subject of the file.
       * @param subject Subject of the file.
       */
      /**
       * @brief Subject.
       * @param subject subject.
       * @return virtual void.
       */
      virtual void Subject ( const std::string& subject ) = 0;

      /** \brief Returns the subject of the file.
       *
       * Returns the subject of the file
       * @return Subject of the file.
       */
    /**
     * @brief Subject.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Subject () const = 0;

      /** \brief Sets the description of the file.
       *
       * Sets the description of the file.
       * @param description Description of the file.
       */
      /**
       * @brief Description.
       * @param description description.
       * @return virtual void.
       */
      virtual void Description ( const std::string& description ) = 0;

      /** \brief Returns the description of the file.
       *
       * Returns the description of the file.
       * @return Description of the file.
       */
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Description () const = 0;

      /** \brief Sets a unique identifier for the measurement.
       *
       * Sets a unique identifier (UUID) for the file. This identify files
       * from the same measurement.
       * @param uuid Unique identifier (UUID).
       */
      /**
       * @brief MeasurementId.
       * @param uuid uuid.
       * @return virtual void.
       */
      virtual void MeasurementId ( const std::string& uuid );

      /** \brief Returns the unique measurement identifier.
       *
       * Returns the unique measurement identifier of the file.
       * @return Unique identifier (UUID) of the measurement.
       */
    /**
     * @brief MeasurementId.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string MeasurementId () const;

      /** \brief Sets a unique identifier for the recorder.
       *
       * Sets a unique identifier (UUID) for measurements from the same
       * recorder.
       * @param uuid Unique identifier (UUID).
       */
      /**
       * @brief RecorderId.
       * @param uuid uuid.
       * @return virtual void.
       */
      virtual void RecorderId ( const std::string& uuid );

      /** \brief Returns the unique recorder identifier.
       *
       * Returns the unique recorder identifier of the file.
       * @return Unique identifier (UUID) of the recorder.
       */
    /**
     * @brief RecorderId.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string RecorderId () const;

      /** \brief Sets the recorder order number.
       *
       * Sets the recorder order number.
       * @param index Order number
       */
      /**
       * @brief RecorderIndex.
       * @param index index.
       * @return virtual void.
       */
      virtual void RecorderIndex ( int64_t index );

      /** \brief Returns the recorder order number
       *
       * Returns the recorder order number.
       * @return Order number.
       */
    /**
     * @brief RecorderIndex.
     * @return [ [ nodiscard ] ] virtual int64_t.
     */
    [ [ nodiscard ] ] virtual int64_t RecorderIndex () const;

      /** \brief Sets the absolute measurement time for the file.
       *
       * Sets the absolute start time for the measurement file.
       * @param ns_since_1970 Nanoseconds since 1970.
       */
      /**
       * @brief StartTime.
       * @param ns_since_1970 ns_since_1970.
       * @return virtual void.
       */
      virtual void StartTime ( uint64_t ns_since_1970 ) = 0;

      /** \brief Sets the absolute measurement time for the file.
       *
       * Sets the absolute start time for the measurement file using an ITimestamp
       * object.
       * @param timestamp An ITimestamp object representing the start time.
       */
      /**
       * @brief StartTime.
       * @param timestamp timestamp.
       * @return virtual void.
       */
      virtual void StartTime ( ITimestamp& timestamp ) = 0;

      /** \brief Returns the absolute measurement time for the file.
       *
       * Returns the absolute start time for the measurement file.
       * @return Nanoseconds since 1970.
       */
    /**
     * @brief StartTime.
     * @return [ [ nodiscard ] ] virtual uint64_t.
     */
    [ [ nodiscard ] ] virtual uint64_t StartTime () const = 0;

      /** \brief Returns the start timestamp of the measurement.
       *
       * This function returns the start timestamp of the measurement as a pointer
       * to an IMdfTimestamp object.
       * @return Pointer to an IMdfTimestamp object representing the start
       * timestamp.
       */
    /**
     * @brief StartTimestamp.
     * @return [ [ nodiscard ] ] virtual IMdfTimestamp*.
     */
    [ [ nodiscard ] ] virtual const IMdfTimestamp* StartTimestamp () const = 0;

      /** \brief Returns meta data information object.
       *
       * Returns meta data as a text string typically as an XML snippets.
       * Note that this function also creates the MD block if it is missing.
       * @return Returns meta data.
       */
    /**
     * @brief CreateMetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData ();

      /** \brief Returns meta data information object.
       *
       * Returns meta data as a text string typically as an XML snippets.
       * @return Returns meta data or a null pointer if no MD block.
       */
    /**
     * @brief MetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* MetaData () const;

      /** \brief Create a new attachment block.
       *
       * Creates a new attachment block (AT) that reference an external file. This
       * file can be just referenced or embedded into the MDF file. If it is
       * embedded, the file may be compressed as well. Note that MDF3 doesn't
       * support attachments.
       * @return An attachment interface pointer.
       */
    /**
     * @brief CreateAttachment.
     * @return [ [ nodiscard ] ] virtual IAttachment*.
     */
    [ [ nodiscard ] ] virtual IAttachment* CreateAttachment ();

      /** \brief Returns a list of attachments.
       *
       * Returns a list of attachments in the measurement file.
       * @return list of attachments
       */
    /**
     * @brief Attachments.
     * @return [ [ nodiscard ] ] virtual std::vector<IAttachment*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IAttachment*> Attachments () const;

      /** \brief Create a new file history block.
       *
       * Creates a new file history (FH) block that reference a change/update of the
       * MDF file.
       * @return A file history  interface pointer.
       */
    /**
     * @brief CreateFileHistory.
     * @return [ [ nodiscard ] ] virtual IFileHistory*.
     */
    [ [ nodiscard ] ] virtual IFileHistory* CreateFileHistory ();

      /** \brief Returns a list of file history blocks.
       *
       * Returns a list of file history blocks in the measurement file.
       * @return List of event interface pointers.
       */
    /**
     * @brief FileHistories.
     * @return [ [ nodiscard ] ] virtual std::vector<IFileHistory*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IFileHistory*> FileHistories () const;

#undef CreateEvent
      /** \brief Creates a new event block.
       *
       * Creates a new event (EV) block.
       * @return An event interface pointer.
       */
    /**
     * @brief CreateEvent.
     * @return [ [ nodiscard ] ] virtual IEvent*.
     */
    [ [ nodiscard ] ] virtual IEvent* CreateEvent ();

      /** \brief Returns a list events.
       *
       * Returns a list of event blocks in the measurement file.
       * @return List of event interface pointers.
       */
    /**
     * @brief Events.
     * @return [ [ nodiscard ] ] virtual std::vector<IEvent*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IEvent*> Events () const;

      /** \brief Creates a new channel hierarchy block.
       *
       * Creates a new channel hierarchy (CH) block.
       * @return Returns a channel hierarchy interface pointer.
       */
    /**
     * @brief CreateChannelHierarchy.
     * @return [ [ nodiscard ] ] virtual IChannelHierarchy*.
     */
    [ [ nodiscard ] ] virtual IChannelHierarchy* CreateChannelHierarchy ();

      /** \brief Returns a list of channel hierarchy blocks.
       *
       * Returns a list of channel hierarchy blocks in the measurement file.
       * @return List of interface pointers.
       */
    /**
     * @brief ChannelHierarchies.
     * @return [ [ nodiscard ] ] virtual std::vector<IChannelHierarchy*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IChannelHierarchy*> ChannelHierarchies ()
      const;

      /** \brief Creates a new data group block.
       *
       * Creates a new data group (DG) block.
       * @return Returns a data group interface pointer.
       */
    /**
     * @brief CreateDataGroup.
     * @return [ [ nodiscard ] ] virtual IDataGroup*.
     */
    [ [ nodiscard ] ] virtual IDataGroup* CreateDataGroup () = 0;

      /** \brief Returns a list of measurements.
       *
       * Returns a list of measurements in the file also known as DG blocks.
       * @return List of measurements.
       */
    /**
     * @brief DataGroups.
     * @return [ [ nodiscard ] ] virtual std::vector<IDataGroup*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IDataGroup*> DataGroups () const = 0;

      /** \brief Returns the last measurement in the file.
       *
       * Returns the last measurement in the file.
       * @return Last DG block.
       */
    /**
     * @brief LastDataGroup.
     * @return [ [ nodiscard ] ] virtual IDataGroup*.
     */
    [ [ nodiscard ] ] virtual IDataGroup* LastDataGroup () const = 0;

      /** \brief Sets the start angle for the measurements.
       *
       * Sets the start angle for the measurements in radians.
       * @param angle Start angle.
       */
      /**
       * @brief StartAngle.
       * @param angle angle.
       * @return virtual void.
       */
      virtual void StartAngle ( double angle );

      /** Returns the start angle.
       *
       * Returns the start angle of the measurement in radians.
       * @return Start angle in radians.
       */
    /**
     * @brief StartAngle.
     * @return [ [ nodiscard ] ] virtual std::optional<double>.
     */
    [ [ nodiscard ] ] virtual std::optional<double> StartAngle () const;

      /** \brief Sets the start distance.
       *
       * Sets the start distance in meter for all measurements.
       * @param distance Start distance in meters.
       */
      /**
       * @brief StartDistance.
       * @param distance distance.
       * @return virtual void.
       */
      virtual void StartDistance ( double distance );

      /** \brief Returns the start distance in meters.
       *
       * Sets the start distance in meters.
       * @return Start distance in meters.
       */
    /**
     * @brief StartDistance.
     * @return [ [ nodiscard ] ] virtual std::optional<double>.
     */
    [ [ nodiscard ] ] virtual std::optional<double> StartDistance () const;

      /** \brief Sets the header comment block.
       * @param hd_comment HD comment object.
       */
      /**
       * @brief SetHdComment.
       * @param hd_comment hd_comment.
       */
      void SetHdComment ( const HdComment& hd_comment );
      /** \brief Retrieves the header comment block.
       * @param hd_comment Receives the HD comment object.
       */
      /**
       * @brief GetHdComment.
       * @param hd_comment hd_comment.
       */
      void GetHdComment ( HdComment& hd_comment ) const;

    protected:
      /**
       * @brief ~IHeader.
       */
      ~IHeader () override = default; ///< Default destructor
  };

  }  // end namespace mdf