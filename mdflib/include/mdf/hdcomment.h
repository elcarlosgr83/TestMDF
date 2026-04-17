/**
 * @file hdcomment.h
 * @brief MDF header declarations for hdcomment.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <map>
#include <string>
#include <cstdint>

#include "mdf/mdcomment.h"
#include "mdf/mdstring.h"
#include "mdf/hounitspecification.h"

namespace mdf {

  using MdConstantList = std::map<MdString, std::string>;

  /**
   * @brief HdComment class definition.
   */
  class HdComment : public MdComment {
  public:
    /**
     * @brief HdComment.
     */
    HdComment ();
    /**
     * @brief HdComment.
     * @param comment comment.
     * @return explicit.
     */
    explicit HdComment ( std::string comment );

    /**
     * @brief Author.
     * @param author author.
     */
    void Author ( std::string author );
    /**
     * @brief Author.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Author () const;

      /**
       * @brief Department.
       * @param department department.
       */
      void Department ( std::string department );
    /**
     * @brief Department.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Department () const;

      /**
       * @brief Project.
       * @param project project.
       */
      void Project ( std::string project );
    /**
     * @brief Project.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Project () const;

      /**
       * @brief Subject.
       * @param subject subject.
       */
      void Subject ( std::string subject );
    /**
     * @brief Subject.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string Subject () const;

      /**
       * @brief MeasurementUuid.
       * @param uuid uuid.
       */
      void MeasurementUuid ( std::string uuid );
    /**
     * @brief MeasurementUuid.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string MeasurementUuid () const;

      /**
       * @brief RecorderUuid.
       * @param uuid uuid.
       */
      void RecorderUuid ( std::string uuid );
    /**
     * @brief RecorderUuid.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string RecorderUuid () const;

      /**
       * @brief RecorderFileIndex.
       * @param index index.
       */
      void RecorderFileIndex ( int64_t index );
    /**
     * @brief RecorderFileIndex.
     * @return [ [ nodiscard ] ] int64_t.
     */
    [ [ nodiscard ] ] int64_t RecorderFileIndex () const;

      /**
       * @brief TimeSource.
       * @param time_source time_source.
       */
      void TimeSource ( MdString time_source );
    /**
     * @brief TimeSource.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& TimeSource () const;

      /**
       * @brief AddConstant.
       * @param constant constant.
       * @param expression expression.
       */
      void AddConstant ( MdString constant, std::string expression );
    /**
     * @brief Constants.
     * @return [ [ nodiscard ] ] MdConstantList&.
     */
    [ [ nodiscard ] ] const MdConstantList& Constants () const;
    /**
     * @brief Constants.
     * @return [ [ nodiscard ] ] MdConstantList&.
     */
    [ [ nodiscard ] ] MdConstantList& Constants ();

    /**
     * @brief UnitSpecification.
     * @return [ [ nodiscard ] ] HoUnitSpecification&.
     */
    [ [ nodiscard ] ] const HoUnitSpecification& UnitSpecification () const;
    /**
     * @brief UnitSpecification.
     * @return [ [ nodiscard ] ] HoUnitSpecification&.
     */
    [ [ nodiscard ] ] HoUnitSpecification& UnitSpecification ();

    /**
     * @brief ToXml.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string ToXml () const override;
      /**
       * @brief FromXml.
       * @param xml_snippet xml_snippet.
       */
      void FromXml ( const std::string& xml_snippet ) override;
    protected:
      MdString time_source_;
      MdConstantList constant_list_;
      HoUnitSpecification unit_spec_;
  };

  }  // namespace mdf