/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <string>

#include "mdf/mdcomment.h"
#include "mdf/hocompumethod.h"

namespace mdf {

  /**
   * @brief CcComment class definition.
   */
  class CcComment : public MdComment {
  public:
    /**
     * @brief CcComment.
     */
    CcComment ();
    /**
     * @brief CcComment.
     * @param comment comment.
     */
    explicit CcComment ( std::string comment );

    /**
     * @brief CompuMethod.
     * @return [ [ nodiscard ] ] HoCompuMethod&.
     */
    [ [ nodiscard ] ] const HoCompuMethod& CompuMethod () const;
    /**
     * @brief CompuMethod.
     * @return [ [ nodiscard ] ] HoCompuMethod&.
     */
    [ [ nodiscard ] ] HoCompuMethod& CompuMethod ();

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
      HoCompuMethod method_;
  };

  }  // namespace mdf