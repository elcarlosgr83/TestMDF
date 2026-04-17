/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/horevision.h"

namespace mdf {
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief HoAdminData class definition.
   */
  class HoAdminData {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const;
      /**
       * @brief AddRevision.
       * @param revision revision.
       */
      void AddRevision ( HoRevision revision );
    /**
     * @brief Revisions.
     * @return [ [ nodiscard ] ] HoRevisionList&.
     */
    [ [ nodiscard ] ] const HoRevisionList& Revisions () const;
    /**
     * @brief Revisions.
     * @return [ [ nodiscard ] ] HoRevisionList&.
     */
    [ [ nodiscard ] ] HoRevisionList& Revisions ();

      /**
       * @brief ToXml.
       * @param root_node root_node.
       */
      void ToXml ( IXmlNode& root_node ) const;
      /**
       * @brief FromXml.
       * @param admin_node admin_node.
       */
      void FromXml ( const IXmlNode& admin_node );

    private:
      HoRevisionList revision_list_;
  };

  }  // namespace mdf