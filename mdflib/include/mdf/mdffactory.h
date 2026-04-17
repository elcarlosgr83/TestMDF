/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <functional>
#include <cstdint>
#include <string>
#include <memory>

#include "mdf/mdfwriter.h"
#include "mdf/ichannelobserver.h"

namespace mdf {


  /** \brief MDF file type. */
  enum class MdfFileType : int {
    Mdf3FileType = 0, ///< MDF version 3 file.
    Mdf4FileType = 1  ///< MDF version 4 file.
  };

  /** \brief Defines the log severity level. */
  enum class MdfLogSeverity : uint8_t {
    kTrace = 0,  ///< Trace or listen message
    kDebug,      ///< Debug message
    kInfo,       ///< Informational message
    kNotice,     ///< Notice message. Notify the user.
    kWarning,    ///< Warning message
    kError,      ///< Error message
    /**
     * @brief message.
     * @param error error.
     * @return kCritical, ///< Critical.
     */
    kCritical,   ///< Critical message (device error)
    kAlert,      ///< Alert or alarm message
    kEmergency   ///< Fatal error message
  };

  /** \brief MDF logging function definition. */
  using MdfLogFunction2 = std::function<void ( MdfLogSeverity severity,
                          const std::string& function, const std::string& text ) >;

  /**
   * @brief MdfWriter class definition.
   */
  class MdfWriter;
  /**
   * @brief MdfFile class definition.
   */
  class MdfFile;
  /**
   * @brief IChannelObserver class definition.
   */
  class IChannelObserver;

  /** \brief MDF factory class. */
  class MdfFactory {
  public:
    /** \brief Creates an MDF writer object.
     * @param type Writer type to create.
     * @return Unique pointer to the created writer.
     */
    /**
     * @brief CreateMdfWriter.
     * @param type type.
     * @return static std::unique_ptr<MdfWriter>.
     */
    static std::unique_ptr<MdfWriter> CreateMdfWriter ( MdfWriterType type );
    /** \brief Create an MDF file object.
     * @param type File type to create.
     * @return Unique pointer to the created file object.
     */
    /**
     * @brief CreateMdfFile.
     * @param type type.
     * @return static std::unique_ptr<MdfFile>.
     */
    static std::unique_ptr<MdfFile> CreateMdfFile ( MdfFileType type );

    /** \brief Creates an MDF writer object.
     * @param type Writer type to create.
     * @return Pointer to the created writer.
     */
    /**
     * @brief CreateMdfWriterEx.
     * @param type type.
     * @return static MdfWriter*.
     */
    static MdfWriter* CreateMdfWriterEx ( MdfWriterType type );
    /** \brief Create an MDF file object.
     * @param type File type to create.
     * @return Pointer to the created file object.
     */
    /**
     * @brief CreateMdfFileEx.
     * @param type type.
     * @return static MdfFile*.
     */
    static MdfFile* CreateMdfFileEx ( MdfFileType type );

    /** \brief Sets the log function.
     * @param func Log callback function.
     */
    /**
     * @brief SetLogFunction2.
     * @param func func.
     * @return static void.
     */
    static void SetLogFunction2 ( const MdfLogFunction2& func );

    /** \brief Creates a channel observer.
     * @param data_group Data group containing the channel.
     * @param channel_group Channel group containing the channel.
     * @param channel Channel to observe.
     * @return Smart pointer to the created observer.
     */
    /**
     * @brief CreateChannelObserver.
     * @param data_group data_group.
     * @param channel_group channel_group.
     * @param channel channel.
     * @return static std::unique_ptr<IChannelObserver>.
     */
    static std::unique_ptr<IChannelObserver> CreateChannelObserver (
      const IDataGroup& data_group, const IChannelGroup& channel_group,
      const IChannel& channel );

  };

}  // namespace mdf