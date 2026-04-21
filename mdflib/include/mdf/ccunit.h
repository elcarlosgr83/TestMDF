/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/mdcomment.h"
#include "mdf/mdstring.h"

namespace mdf {

  /**
   * @brief CcUnit class definition.
   */
  class CcUnit : public MdComment {
  public:
    /**
     * @brief CcUnit.
     */
    CcUnit ();
    /**
     * @brief CcUnit.
     * @param unit unit.
     */
    explicit CcUnit ( std::string unit );

    /**
     * @brief Unit.
     * @param unit unit.
     */
    void Unit ( MdString unit );
    /**
     * @brief Unit.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& Unit () const;

      /**
       * @brief UnitRef.
       * @param unit_ref unit_ref.
       */
      void UnitRef ( MdString unit_ref );
    /**
     * @brief UnitRef.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& UnitRef () const;

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
    /**
     * @brief CreateRootNode.
     * @param xml_file xml_file.
     * @param init_ho_namespace init_ho_namespace.
     * @return [ [ nodiscard ] ] IXmlNode&.
     */
    [ [ nodiscard ] ] IXmlNode& CreateRootNode ( IXmlFile& xml_file,
      bool init_ho_namespace ) const override;
    private:
      MdString unit_ref_;
  };

  } // end namespace