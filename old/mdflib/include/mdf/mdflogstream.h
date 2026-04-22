/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <sstream>
#include <string>

/** \brief This is a replacement for the std::source_location library.
 * The standard source_location library cannot be used due to user requirement
 * of C++ 17 version.
 */

struct MdfLocation {
  int line = 0;      ///< Source code line.
  int column = 0;    ///< Source code column.
  std::string file;  ///< Source code file name (avoid path).
  std::string function; ///< Source code function.
};

#include "mdf/mdffactory.h"

namespace mdf {


#define MDF_TRACE() \
  MdfLogStream({__LINE__,0,__FILE__,__func__}, \
  MdfLogSeverity::kTrace)  ///< Trace log message
#define MDF_DEBUG() \
  MdfLogStream({__LINE__,0,__FILE__,__func__}, \
  MdfLogSeverity::kDebug)  ///< Debug log message
#define MDF_INFO() \
  MdfLogStream({__LINE__,0,__FILE__,__func__}, \
  MdfLogSeverity::kInfo)  ///< Info log message
#define MDF_ERROR() \
  MdfLogStream({__LINE__,0,__FILE__,__func__}, \
  MdfLogSeverity::kError)  ///< Error log message

  /** \brief MDF log function definition. */
  using MdfLogFunction1 = std::function<void ( const MdfLocation &location,
                          MdfLogSeverity severity, const std::string &text ) >;

  /** \brief MDF log stream interface.
   *
   *
   */

  class MdfLogStream : public std::ostringstream {
  public:
    /** \brief Creates a log stream for a location and severity.
     * @param location Source location of the log message.
     * @param severity Severity level of the log message.
     */
    MdfLogStream ( MdfLocation location, MdfLogSeverity severity );
    /** \brief Destructor that flushes the log stream. */
    ~MdfLogStream () override;

    /**
     * @brief MdfLogStream.
     */
    MdfLogStream () = delete;
    /**
     * @brief MdfLogStream.
     */
    MdfLogStream ( const MdfLogStream& ) = delete;
    /**
     * @brief MdfLogStream.
     */
    MdfLogStream ( MdfLogStream&& ) = delete;
    /**
     * @brief operator=.
     * @return MdfLogStream&.
     */
    MdfLogStream& operator= ( const MdfLogStream& ) = delete;
    /**
     * @brief operator=.
     * @return MdfLogStream&.
     */
    MdfLogStream& operator= ( MdfLogStream&& ) = delete;

    /** \brief Sets a log function.
     * @param func Log callback.
     */
    static void SetLogFunction1 ( const MdfLogFunction1& func );
    /** \brief Sets a log function.
     * @param func Log callback.
     */
    static void SetLogFunction2 ( const MdfLogFunction2& func );
    /** \brief Resets the current log function to the default behavior. */
    static void ResetLogFunction ();
    /** \brief Writes a log message directly to the console.
     * @param location Source location of the log message.
     * @param severity Severity level.
     * @param text Message text.
     */
    static void LogToConsole ( const MdfLocation& location,
                               MdfLogSeverity severity,
                               const std::string& text );
  protected:
    MdfLocation location_;     ///< File and function location.
    MdfLogSeverity severity_;  ///< Log level of the stream

    /** \brief Defines the logging function. */
    virtual void LogString ( const MdfLocation& location, MdfLogSeverity severity,
                             const std::string& text );
  };

}  // namespace mdf