/**
 * @file cncomment.h
 * @brief MDF header declarations for cncomment.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <optional>

#include "mdf/mdcomment.h"
#include "mdf/mdstring.h"
#include "mdf/mdnumber.h"
#include "mdf/hounit.h"

namespace mdf {

  /**
   * @brief enum class MdMonotony enumeration.
   */
  enum class MdMonotony : int {
    MonDecrease = 0,
    MonIncrease,
    StrictDecrease,
    StrictIncrease,
    Monotonous,
    StrictMon,
    NotMono,
  };

  /**
   * @brief MdMonotonyToString.
   * @param monotony monotony.
   * @return std::string_view.
   */
  std::string_view MdMonotonyToString ( MdMonotony monotony );
  /**
   * @brief StringToMdMonotony.
   * @param mon_text mon_text.
   * @return MdMonotony.
   */
  MdMonotony StringToMdMonotony ( const std::string& mon_text );

  /**
   * @brief CnComment class definition.
   */
  class CnComment : public MdComment {
  public:
    /**
     * @brief CnComment.
     */
    CnComment ();
    /**
     * @brief CnComment.
     * @param comment comment.
     * @return explicit.
     */
    explicit CnComment ( std::string comment );

    /**
     * @brief LinkerName.
     * @param linker_name linker_name.
     */
    void LinkerName ( MdString linker_name );
    /**
     * @brief LinkerName.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& LinkerName () const;

      /**
       * @brief LinkerAddress.
       * @param linker_address linker_address.
       */
      void LinkerAddress ( MdNumber linker_address );
    /**
     * @brief LinkerAddress.
     * @return [ [ nodiscard ] ] MdNumber&.
     */
    [ [ nodiscard ] ] const MdNumber& LinkerAddress () const;

      /**
       * @brief AxisMonotony.
       * @param axis_monotony axis_monotony.
       */
      void AxisMonotony ( MdMonotony axis_monotony );
    /**
     * @brief AxisMonotony.
     * @return [ [ nodiscard ] ] MdMonotony.
     */
    [ [ nodiscard ] ] MdMonotony AxisMonotony () const;

      /**
       * @brief Raster.
       * @param raster raster.
       */
      void Raster ( MdNumber raster );
    /**
     * @brief Raster.
     * @return [ [ nodiscard ] ] MdNumber&.
     */
    [ [ nodiscard ] ] const MdNumber& Raster () const;

      /**
       * @brief Address.
       * @param address address.
       */
      void Address ( MdNumber address );
    /**
     * @brief Address.
     * @return [ [ nodiscard ] ] MdNumber&.
     */
    [ [ nodiscard ] ] const MdNumber& Address () const;

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

    private:
      MdString linker_name_;
      MdNumber linker_address_;
      std::optional<MdMonotony> axis_monotony_;
      MdNumber raster_;
      MdNumber address_;

  };

  }  // namespace mdf