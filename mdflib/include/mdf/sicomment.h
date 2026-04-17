/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/mdcomment.h"
#include "mdf/mdalternativename.h"
#include "mdf/mdstring.h"

namespace mdf {

  /**
   * @brief SiComment class definition.
   */
  class SiComment : public MdComment {
  public:
    /**
     * @brief SiComment.
     */
    SiComment ();
    /**
     * @brief SiComment.
     * @param comment comment.
     * @return explicit.
     */
    explicit SiComment ( std::string comment );

    /**
     * @brief Path.
     * @return [ [ nodiscard ] ] MdAlternativeName&.
     */
    [ [ nodiscard ] ] const MdAlternativeName& Path () const;
    /**
     * @brief Path.
     * @return [ [ nodiscard ] ] MdAlternativeName&.
     */
    [ [ nodiscard ] ] MdAlternativeName& Path ();

    /**
     * @brief Bus.
     * @return [ [ nodiscard ] ] MdAlternativeName&.
     */
    [ [ nodiscard ] ] const MdAlternativeName& Bus () const;
    /**
     * @brief Bus.
     * @return [ [ nodiscard ] ] MdAlternativeName&.
     */
    [ [ nodiscard ] ] MdAlternativeName& Bus ();

      /**
       * @brief Protocol.
       * @param protocol protocol.
       */
      void Protocol ( MdString protocol );
    /**
     * @brief Protocol.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& Protocol () const;

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
      // names is defined in MdComment class
      MdAlternativeName path_;
      MdAlternativeName bus_;
      MdString protocol_;
  };

  }  // namespace mdf