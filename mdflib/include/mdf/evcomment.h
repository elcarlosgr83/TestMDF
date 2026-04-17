/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <string>
#include "mdf/mdcomment.h"
#include "mdf/mdnumber.h"

namespace mdf {

  /**
   * @brief EvComment class definition.
   */
  class EvComment : public MdComment {
  public:
    /**
     * @brief EvComment.
     */
    EvComment ();
    /**
     * @brief EvComment.
     * @param comment comment.
     * @return explicit.
     */
    explicit EvComment ( std::string comment );
    /**
     * @brief PreTriggerInterval.
     * @param interval interval.
     */
    void PreTriggerInterval ( MdNumber interval );
    /**
     * @brief PreTriggerInterval.
     * @return [ [ nodiscard ] ] MdNumber&.
     */
    [ [ nodiscard ] ] const MdNumber& PreTriggerInterval () const;

      /**
       * @brief PostTriggerInterval.
       * @param interval interval.
       */
      void PostTriggerInterval ( MdNumber interval );
    /**
     * @brief PostTriggerInterval.
     * @return [ [ nodiscard ] ] MdNumber&.
     */
    [ [ nodiscard ] ] const MdNumber& PostTriggerInterval () const;

      /**
       * @brief Timeout.
       * @param timeout timeout.
       */
      void Timeout ( MdNumber timeout );
    /**
     * @brief Timeout.
     * @return [ [ nodiscard ] ] MdNumber&.
     */
    [ [ nodiscard ] ] const MdNumber& Timeout () const;

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
      MdNumber pre_trigger_interval_;
      MdNumber post_trigger_interval_;
      MdNumber timeout_;
  };

  }  // namespace mdf