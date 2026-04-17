/**
 * @file mdfwriter.h
 * @brief MDF header declarations for mdfwriter.
 */

/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <deque>
#include <string>
#include <map>
#include <ios>
#include <atomic>
#include <memory>
#include <streambuf>

#include "mdf/mdfenumerates.h"
#include "mdf/mdffile.h"
#include "mdf/canmessage.h"
#include "mdf/linmessage.h"
#include "mdf/ethmessage.h"

/** \file mdfwriter.h
 * \brief Interface against an MDF writer object.
 */
namespace mdf {

  /** \brief MDF writer types. */
  enum class MdfWriterType : int {
    Mdf3Basic = 0, ///< Basic MDF version 3 writer.
    Mdf4Basic = 1,  ///< Basic MDF version 4 writer.
    MdfBusLogger = 2, ///< Specialized bus logger writer.
    MdfConverter = 3, ///< MDF writer for MDF 4 conversion applications.
  };

  /**
   * @brief enum class WriteState enumeration.
   */
  enum class WriteState : uint8_t {
    Create,     ///< Only at first measurement
    Init,       ///< Start work thread and start collecting samples
    StartMeas,  ///< Start saving samples to file
    StopMeas,   ///< Stop saving samples. OK to
    Finalize    ///< OK to add new DG and CG blocks
  };

  /**
   * @brief IChannelGroup class definition.
   */
  class IChannelGroup;
  /**
   * @brief IChannel class definition.
   */
  class IChannel;
  /**
   * @brief IChannelConversion class definition.
   */
  class IChannelConversion;
  /**
   * @brief IDataGroup class definition.
   */
  class IDataGroup;
  /**
   * @brief IMostEvent class definition.
   */
  class IMostEvent;
  /**
   * @brief IFlexRayEvent class definition.
   */
  class IFlexRayEvent;

  namespace detail {
    /**
     * @brief SampleQueue class definition.
     */
    class SampleQueue;
    /**
     * @brief Writer4SampleQueue class definition.
     */
    class Writer4SampleQueue;
    /**
     * @brief ConverterSampleQueue class definition.
     */
    class ConverterSampleQueue;
  }

  /** \brief Interface against an MDF writer object.
   *
   * The MDF writer purpose is to create MDF files. It simplifies the writing
   * into some steps.
   *
   * The first is to create type of writer. This is done by using the
   * MdfFactory::CreateMdfWriter() function.
   *
   * The next step is to call the Init() function with a filename with valid path.
   * The Init function will create the actual MDF file object and check if it
   * exist or not. If it exist, it reads in the existing file content so it can
   * be appended.
   *
   * The next step is to prepare the file for a new measurement. This is done
   * by creating the DG/CG/CN/CC blocks that defines the measurement. Note that
   * it is the last DG block that is the target.
   *
   * Next step is to call the InitMeasurement() function. This create a thread
   * that handle the queue of samples. The function also write the configuration
   * to the file and closes it.
   *
   * The user shall now start adding samples to the queue by first setting
   * the current channel value to each channel and then call the SaveSample()
   * function for each channel group (CG). Note that no samples are saved to the
   * file yet. The max queue size is set to the pre-trig time, see PreTrigTime().
   *
   * At some point the user shall call the StartMeasurement() function. The
   * sample queue is now saved onto the file. The save rate is actually dependent
   * if CompressData() is enabled or not. If compression is used the data is
   * saved at the 4MB size or a 10 minute max. If not using compression, the
   * samples are saved each 10 second.
   *
   * The user shall now call StopMeasurement() which flush out the remaining
   * sample queue. After stopping the queue, the user may add some extra block
   * as event (EV) and attachment (AT) blocks.
   *
   * The FinalizeMeasurement() function. Stops the thread and write all
   * unwritten blocks to the file.
   *
   */

  class MdfWriter {
    friend class detail::SampleQueue;
    friend class detail::Writer4SampleQueue;
    friend class detail::ConverterSampleQueue;
  public:

    /**
     * @brief ~MdfWriter.
     */
    virtual ~MdfWriter () = default; ///< Default destructor.

    /**
     * @brief MdfWriter.
     * @param writer writer.
     */
    MdfWriter ( const MdfWriter& writer ) = delete;
    /**
     * @brief operator=.
     * @param writer writer.
     * @return MdfWriter&.
     */
    MdfWriter& operator= ( const MdfWriter& writer ) = delete;

    /** \brief Returns the filename without extension and path (stem). */
    [ [ nodiscard ] ] std::string Name () const;

    /**
     * @brief TypeOfWriter.
     * @return [ [ nodiscard ] ] MdfWriterType.
     */
    [ [ nodiscard ] ] MdfWriterType TypeOfWriter () const {
        return type_of_writer_;
    }

    /**
     * @brief State.
     * @param state state.
     */
    void State ( WriteState state ) {
      write_state_ = state;
      }
    /**
     * @brief State.
     * @return [ [ nodiscard ] ] WriteState.
     */
    [ [ nodiscard ] ] WriteState State () const {
        return write_state_;
    }

    /** \brief Init the writer against a file.
     *
     * Initiate the writer by defining which file it shall work with. Note that
     * appending an existing file is supported.
     *
     * @param filename Filename with full path.
     * @return Returns true if the function was successful.
     */
    /**
     * @brief Init.
     * @param filename filename.
     * @return bool.
     */
    bool Init ( const std::string& filename );

    /** \brief Initialize the writer against a generic stream buffer.
     *
     * Attaches an existing stream buffer for writing MDF output.
     * @param buffer Shared pointer to the target stream buffer.
     * @return `true` if initialization succeeded.
     */
    /**
     * @brief Init.
     * @param buffer buffer.
     * @return bool.
     */
    bool Init ( const std::shared_ptr<std::streambuf>& buffer );

    /** \brief Returns true if this is a new file. */
    [ [ nodiscard ] ] bool IsFileNew () const {
        return write_state_ == WriteState::Create;
    };

    /** \brief Sets the pre-trig time (s) of the writer.
     *
     * Sets the pre-trig time (note seconds). This defines the maximum number of
     * samples the writer holds internally, before the measurement is started.
     * @param pre_trig_time Pre-trig time in seconds.
     */
    /**
     * @brief PreTrigTime.
     * @param pre_trig_time pre_trig_time.
     */
    void PreTrigTime ( double pre_trig_time );
    /**
     * @brief PreTrigTime.
     * @param s s.
     * @return [ [ nodiscard ] ] double.
     */
    [ [ nodiscard ] ] double PreTrigTime () const; ///< Pre-trig time (s).
    /**
     * @brief PreTrigTimeNs.
     * @param ns ns.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t PreTrigTimeNs () const; ///< Pre-trig time (ns).
      /** \brief Returns start time in nano-seconds since 1970. */
    [ [ nodiscard ] ] uint64_t StartTime () const { return start_time_; }
    /** \brief Returns stop time in nano-seconds since 1970. */
    [ [ nodiscard ] ] uint64_t StopTime () const { return stop_time_; }

    /** \brief Returns the MDF file interface.
     *
     * Returns the MDF file interface. The user may change the file version and
     * the finalize status of the file. By default is the MDF 4.2 or 3.2 version
     * of the file used.
     * @return Pointer to the MDF file interface.
     */
    MdfFile* GetFile () const { return mdf_file_.get (); }

    /**
     * @brief Header.
     * @param HD HD.
     * @return [ [ nodiscard ] ] IHeader*.
     */
    [ [ nodiscard ] ] IHeader* Header () const; ///< Returns the header block (HD).

      /** \brief Creates a bus logger configuration.
       *
       * Creates data groups, channel groups, source information and channels for
       * a typical bus logger setup.
       * @return `true` if the configuration was created successfully.
       */
      /**
       * @brief CreateBusLogConfiguration.
       * @return bool.
       */
      bool CreateBusLogConfiguration ();

      /** \brief Create a new data group (DG) block.
       * @return Pointer to the newly created data group.
       */
    /**
     * @brief CreateDataGroup.
     * @return [ [ nodiscard ] ] IDataGroup*.
     */
    [ [ nodiscard ] ] IDataGroup* CreateDataGroup ();
      /** \brief Create a new channel group (CG) block.
       * @param parent Parent data group.
       * @return Pointer to the new channel group.
       */
    /**
     * @brief CreateChannelGroup.
     * @param parent parent.
     * @return [ [ nodiscard ] ] static IChannelGroup*.
     */
    [ [ nodiscard ] ] static IChannelGroup* CreateChannelGroup (
      IDataGroup* parent );
      /** \brief Creates a new channel (CN) block.
       * @param parent Parent channel group.
       * @return Pointer to the new channel.
       */
    /**
     * @brief CreateChannel.
     * @param parent parent.
     * @return [ [ nodiscard ] ] static IChannel*.
     */
    [ [ nodiscard ] ] static IChannel* CreateChannel ( IChannelGroup* parent );
      /** \brief Create a new channel conversion (CC) block.
       * @param parent Parent channel.
       * @return Pointer to the newly created conversion.
       */
      /**
       * @brief CreateChannelConversion.
       * @param parent parent.
       * @return virtual IChannelConversion*.
       */
      virtual IChannelConversion* CreateChannelConversion ( IChannel* parent ) = 0;

      /** \brief Initialize the sample queue and write any unwritten block to the
       * file.
       * @return `true` if the measurement initialization succeeded.
       */
      /**
       * @brief InitMeasurement.
       * @return virtual bool.
       */
      virtual bool InitMeasurement ();

      /** \brief Saves a sample record for a channel group.
       *
       * Call this function after all channel values have been updated with
       * the latest value. The function creates the a record byte buffer and
       * puts the buffer onto an internal sample buffer.
       *
       * The time shall be absolute time (nano-seconds since 1970-01-01). Note
       * that the function or actually the internal queue, assume that the
       * samples are added in chronological order. The time will be converted
       * to a relative time before it is stored onto the disc. The will be relative
       * to the start time, see StartMeasurement() function.
       * @param group Channel group that owns the sample values.
       * @param time Absolute timestamp in nanoseconds since 1970.
       */
      /**
       * @brief SaveSample.
       * @param group group.
       * @param time time.
       * @return virtual void.
       */
      virtual void SaveSample ( const IChannelGroup& group, uint64_t time ) = 0;

      /** \brief Saves a sample record for a channel group inside a data group.
       * @param data_group Parent data group.
       * @param channel_group Channel group that owns the sample values.
       * @param time Absolute timestamp in nanoseconds since 1970.
       */
      /**
       * @brief SaveSample.
       * @param data_group data_group.
       * @param channel_group channel_group.
       * @param time time.
       * @return virtual void.
       */
      virtual void SaveSample ( const IDataGroup& data_group,
      const IChannelGroup& channel_group,
      uint64_t time ) = 0;
      /** \brief Saves a CAN message into a bus logger channel group.
       *
       * This function replace the normal SaveSample() function. It shall be used
       * when logging CAN/CAN-FD messages into a standard ASAM bus logger
       * configuration.
       *
       * As before the function creates a record byte array and puts it onto an
       * internal sample buffer. The time shall be absolute time (ns since 1970).
       * @param group Reference to the channel group (CG).
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The CAN message to store.
       */
      /**
       * @brief SaveCanMessage.
       * @param group group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveCanMessage ( const IChannelGroup& group, uint64_t time,
      const CanMessage& msg ) = 0;
      /** \brief Saves a CAN message into a bus logger channel group.
       *
       * This overload saves a CAN message with an explicit data group context.
       * @param data_group Parent data group.
       * @param channel_group Channel group that owns the message.
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The CAN message to store.
       */
      /**
       * @brief SaveCanMessage.
       * @param data_group data_group.
       * @param channel_group channel_group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveCanMessage ( const IDataGroup& data_group,
      const IChannelGroup& channel_group, uint64_t time,
      const CanMessage& msg ) = 0;
      /** \brief Saves a LIN message into a bus logger channel group.
       *
       * This function replaces the normal SaveSample() function. It should be used
       * when logging LIN messages into a standard ASAM bus logger configuration.
       *
       * As before, the function creates a record byte array and puts it onto an
       * internal sample buffer. The time shall be absolute time (ns since 1970).
       * @param group Reference to the channel group (CG).
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The LIN message to store.
       */
      /**
       * @brief SaveLinMessage.
       * @param group group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveLinMessage ( const IChannelGroup& group, uint64_t time,
      const LinMessage& msg ) = 0;
      /** \brief Saves a LIN message into a bus logger channel group.
       *
       * This overload saves a LIN message with an explicit data group context.
       * @param data_group Parent data group.
       * @param channel_group Channel group that owns the message.
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The LIN message to store.
       */
      /**
       * @brief SaveLinMessage.
       * @param data_group data_group.
       * @param channel_group channel_group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveLinMessage ( const IDataGroup& data_group,
      const IChannelGroup& channel_group, uint64_t time,
      const LinMessage& msg ) = 0;
      /** \brief Saves an Ethernet message into a bus logger channel group.
       *
       * This function replaces the normal SaveSample() function. It should be used
       * when logging Ethernet messages into a standard ASAM bus logger
       * configuration.
       *
       * As before, the function creates a record byte array and puts it onto an
       * internal sample buffer. The time shall be absolute time (ns since 1970).
       * @param group Reference to the channel group (CG).
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The Ethernet message to store.
       */
      /**
       * @brief SaveEthMessage.
       * @param group group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveEthMessage ( const IChannelGroup& group, uint64_t time,
      const EthMessage& msg ) = 0;

      /** \brief Saves an Ethernet message into a bus logger channel group.
       *
       * This overload saves an Ethernet message with an explicit data group context.
       * @param data_group Parent data group.
       * @param channel_group Channel group that owns the message.
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The Ethernet message to store.
       */
      /**
       * @brief SaveEthMessage.
       * @param data_group data_group.
       * @param channel_group channel_group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveEthMessage ( const IDataGroup& data_group,
      const IChannelGroup& channel_group, uint64_t time,
      const EthMessage& msg ) = 0;

      /** \brief Saves a MOST message into a bus logger channel group.
       *
       * This function saves a MOST event message into the supplied channel group.
       * @param data_group Parent data group.
       * @param channel_group Channel group that owns the message.
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The MOST event to store.
       */
      /**
       * @brief SaveMostMessage.
       * @param data_group data_group.
       * @param channel_group channel_group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveMostMessage ( const IDataGroup& data_group,
      const IChannelGroup& channel_group,
      uint64_t time,
      const IMostEvent& msg ) = 0;

      /** \brief Saves a FlexRay message into a bus logger channel group.
       *
       * This function saves a FlexRay event message into the supplied channel
       * group.
       * @param data_group Parent data group.
       * @param channel_group Channel group that owns the message.
       * @param time Absolute time nano-seconds since 1970.
       * @param msg The FlexRay event to store.
       */
      /**
       * @brief SaveFlexRayMessage.
       * @param data_group data_group.
       * @param channel_group channel_group.
       * @param time time.
       * @param msg msg.
       * @return virtual void.
       */
      virtual void SaveFlexRayMessage ( const IDataGroup& data_group,
      const IChannelGroup& channel_group,
      uint64_t time,
      const IFlexRayEvent& msg ) = 0;
      /** \brief Starts the measurement.
       * @param start_time Start timestamp in nanoseconds since 1970.
       */
      /**
       * @brief StartMeasurement.
       * @param start_time start_time.
       * @return virtual void.
       */
      virtual void StartMeasurement ( uint64_t start_time );

      /** \brief Starts the measurement using a timestamp object.
       * @param start_time Timestamp object.
       */
      /**
       * @brief StartMeasurement.
       * @param start_time start_time.
       * @return virtual void.
       */
      virtual void StartMeasurement ( ITimestamp &start_time );
      /** \brief Stops the measurement.
       * @param stop_time Stop timestamp in nanoseconds since 1970.
       */
      /**
       * @brief StopMeasurement.
       * @param stop_time stop_time.
       * @return virtual void.
       */
      virtual void StopMeasurement ( uint64_t stop_time );
      /** \brief Stops the measurement using a timestamp object.
       * @param stop_time Timestamp object.
       */
      /**
       * @brief StopMeasurement.
       * @param stop_time stop_time.
       * @return virtual void.
       */
      virtual void StopMeasurement ( ITimestamp &stop_time );

      /** \brief Stop the sample queue and write all unwritten blocks to
       * the file.
       * @return `true` if the finalization succeeded.
       */
      /**
       * @brief FinalizeMeasurement.
       * @return virtual bool.
       */
      virtual bool FinalizeMeasurement ();

      /** \brief Only used when doing bus logging. It defines the default
       * channel and channel group names when doing bus logging.
       *
       * When using the MDF writer as a bus logger, the naming of channel groups
       * and channels are defined in an ASAM standard. The naming is depending on
       * the basic low level protocol.
       * @param type Type of basic protocols on the bus.
       */
      /**
       * @brief BusType.
       * @param type type.
       */
      void BusType ( uint16_t type ) {
        bus_type_ = type;
    }

    /** \brief Returns the type of bus the MDF file is associated with. Only
     * used when doing bus logging.
     * @return Type of bus.
     */
    [ [ nodiscard ] ] uint16_t BusType () const { return bus_type_; }

    /** \brief Returns the bus type as text.
     * @return Human-readable bus type name.
     */
    /**
     * @brief BusTypeAsString.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string BusTypeAsString () const;

      /** \brief Only used when doing bus logging. It defines how raw data is
       * stored.
       *
       * Defines how the raw data (payload) is stored. Only used when doing bus
       * logging.
       *
       * By default the fixed length storage is used. This means that the data
       * records have fixed length. This is the traditional way of storage.
       * Variable length channels as strings, are stored in separate signal data
       * blocks (SD).
       *
       * The Variable Length Signal Data (VLSD) is stored in the data block. In
       * practice this option is only used when doing bus logging.
       *
       * The Maximum Length Signal Data is typically used when logging CAN bus
       * traffic.
       * @param type Type of storage.
       */
    /**
     * @brief StorageType.
     * @param type type.
     */
    void StorageType ( MdfStorageType type ) { storage_type_ = type; }

    /** \brief Returns the type of data storage the MDF file is associated with.
     * Only used when doing bus logging.
     * @return Type of data storage.
     */
    [ [ nodiscard ] ] MdfStorageType StorageType () const { return storage_type_; }

    /** \brief Sets max number of payload data bytes.
     *
     * Number of payload data bytes is default set to  8 bytes. Standard CAN
     * may have max 8 byte of data while CAN FD can have up to 64 bytes data
     * bytes. If you should store CAN FD data, you should set the max length to
     * 64 bytes.
     * @param max_length Maximum number of payload data bytes.
     */
    /**
     * @brief MaxLength.
     * @param max_length max_length.
     */
    void MaxLength ( uint32_t max_length ) {max_length_ = max_length;};

    /** \brief Returns maximum number of payload data bytes. */
    [ [ nodiscard ] ] uint32_t MaxLength () const { return max_length_; }

    /** \brief If set to true, the data block will be compressed. */
    void CompressData ( bool compress ) {compress_data_ = compress;}

    /** \brief Returns true if the data block is compressed. */
    [ [ nodiscard ] ] bool CompressData () const { return compress_data_;}

    /**
     * @brief SavePeriodic.
     * @param periodic periodic.
     */
    void SavePeriodic ( bool periodic ) { periodic_save_ = periodic; }
    [ [ nodiscard ] ] bool IsSavePeriodic () const { return periodic_save_; }

    /** \brief Define only mandatory members.
     *
     * This option defines if only mandatory members should be automatic
     * generated.
     * This property is only used for bus configurations.
     * When the property is true, only data frames are saved.
     *
     * It's questionable if this property should be used for on-line
     * loggers but if only correct data frames are of interest, the
     * property can be set to true.
     * @param mandatory_only If set true, only mandatory members are created.
     */
    /**
     * @brief MandatoryMembersOnly.
     * @param mandatory_only mandatory_only.
     */
    void MandatoryMembersOnly ( bool mandatory_only ) {
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
    MdfWriterType type_of_writer_ = MdfWriterType::Mdf4Basic;
    /** \brief Smart pointer to a stream buffer.
     *
     * The smart pointer to a stream buffer is normally set to
     * a std::filebuf but can be assigned to a generic stream
     * buffer.
     */
    std::shared_ptr<std::streambuf> file_;


    std::unique_ptr<MdfFile> mdf_file_;  ///< Holds the actual file object.
    std::string filename_;  ///< Full name of file with path and extension.

    std::atomic<uint64_t> pre_trig_time_ = 0;  ///< Nanoseconds difference.
    std::atomic<uint64_t> start_time_ = 0;     ///< Nanoseconds since 1970.
    std::atomic<uint64_t> stop_time_ = 0;      ///< Nanoseconds since 1970.
    std::atomic<WriteState> write_state_ =
    WriteState::Create;  ///< Keeps track of the worker thread state.

    /**
     * @brief MdfWriter.
     */
    MdfWriter () = default; ///< Default constructor.

    /**
     * @brief CreateMdfFile.
     * @return virtual void.
     */
    virtual void CreateMdfFile () = 0; ///< Creates an MDF file

    /**
     * @brief PrepareForWriting.
     * @return virtual bool.
     */
    virtual bool PrepareForWriting () = 0; ///< Prepare for writing.

    /**
     * @brief WriteSignalData.
     * @param file file.
     * @return virtual bool.
     */
    virtual bool WriteSignalData ( std::streambuf& file ); ///< Write an SD block.

    /** \brief Set the last file position. */


    void Open ( std::ios_base::openmode mode );
    /**
     * @brief IsOpen.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsOpen () const;
      /**
       * @brief Close.
       */
      void Close ();

      /**
       * @brief InitWriteCache.
       * @return virtual void.
       */
      virtual void InitWriteCache () = 0;
      /**
       * @brief ExitWriteCache.
       * @return virtual void.
       */
      virtual void ExitWriteCache () = 0;
      /**
       * @brief RecalculateTimeMaster.
       * @return virtual void.
       */
      virtual void RecalculateTimeMaster () = 0;
      /**
       * @brief NotifySample.
       * @return virtual void.
       */
      virtual void NotifySample () = 0;

      //void SetDataPosition();

    private:
      bool compress_data_ = false; ///< True if the data shall be compressed.
      bool periodic_save_ = true; ///< If set to false, save first at stop.
      uint16_t bus_type_ = 0; ///< Defines protocols.
      MdfStorageType storage_type_ = MdfStorageType::FixedLengthStorage;
      uint32_t max_length_ = 8; ///< Max data byte storage
      bool mandatory_members_only_ = false;

    /**
     * @brief IsFirstMeasurement.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsFirstMeasurement () const;


  };

  }  // namespace mdf