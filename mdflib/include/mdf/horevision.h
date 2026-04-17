/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace mdf {

  /**
   * @brief HoRevision class definition.
   */
  class HoRevision;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using HoRevisionList = std::vector<HoRevision>;

  /**
   * @brief HoCompanyRevision struct definition.
   */
  struct HoCompanyRevision {
    std::string DataReference;
    std::string Label;
    std::string State;
  };
  using HoCompanyRevisionList = std::vector<HoCompanyRevision>;

  /**
   * @brief HoModification struct definition.
   */
  struct HoModification {
    std::string Change;
    std::string Reason;
  };
  using HoModificationList = std::vector<HoModification>;

  /**
   * @brief HoRevision class definition.
   */
  class HoRevision {
  public:
    /**
     * @brief TeamMemberReference.
     * @param team_member team_member.
     */
    void TeamMemberReference ( std::string team_member );
    /**
     * @brief TeamMemberReference.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& TeamMemberReference () const;

      /**
       * @brief RevisionLabel.
       * @param label label.
       */
      void RevisionLabel ( std::string label );
    /**
     * @brief RevisionLabel.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& RevisionLabel () const;

      /**
       * @brief State.
       * @param state state.
       */
      void State ( std::string state );
    /**
     * @brief State.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& State () const;

      /**
       * @brief Date.
       * @param date date.
       */
      void Date ( std::string date );
    /**
     * @brief Date.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Date () const;

      /**
       * @brief DateNs.
       * @param ns1970 ns1970.
       */
      void DateNs ( uint64_t ns1970 );
    /**
     * @brief DateNs.
     * @return [ [ nodiscard ] ] uint64_t.
     */
    [ [ nodiscard ] ] uint64_t DateNs () const;

      /**
       * @brief AddCompanyRevision.
       * @param revision revision.
       */
      void AddCompanyRevision ( HoCompanyRevision revision );
    /**
     * @brief CompanyRevisions.
     * @return [ [ nodiscard ] ] HoCompanyRevisionList&.
     */
    [ [ nodiscard ] ] const HoCompanyRevisionList& CompanyRevisions () const;
    /**
     * @brief CompanyRevisions.
     * @return [ [ nodiscard ] ] HoCompanyRevisionList&.
     */
    [ [ nodiscard ] ] HoCompanyRevisionList& CompanyRevisions ();


      /**
       * @brief AddModification.
       * @param modification modification.
       */
      void AddModification ( HoModification modification );
    /**
     * @brief Modifications.
     * @return [ [ nodiscard ] ] HoModificationList&.
     */
    [ [ nodiscard ] ] const HoModificationList& Modifications () const;
    /**
     * @brief Modifications.
     * @return [ [ nodiscard ] ] HoModificationList&.
     */
    [ [ nodiscard ] ] HoModificationList& Modifications ();

      /**
       * @brief ToXml.
       * @param root_node root_node.
       */
      void ToXml ( IXmlNode& root_node ) const;
      /**
       * @brief FromXml.
       * @param revision_node revision_node.
       */
      void FromXml ( const IXmlNode& revision_node );

    private:
      std::string team_member_ref_;
      std::string revision_label_;
      std::string state_;
      std::string date_; ///< ISO date time string

      HoCompanyRevisionList company_revision_list_;
      HoModificationList modification_list_;

  };

  }  // namespace mdf