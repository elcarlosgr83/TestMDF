/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/mdsyntax.h"
#include "mdf/mdvariable.h"
#include "mdf/mdstandardattribute.h"

namespace mdf {

  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  /**
   * @brief MdFormula class definition.
   */
  class MdFormula : public MdStandardAttribute {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const override;

      /**
       * @brief Syntax.
       * @param syntax syntax.
       */
      void Syntax ( MdSyntax syntax );
    /**
     * @brief Syntax.
     * @return [ [ nodiscard ] ] MdSyntax&.
     */
    [ [ nodiscard ] ] const MdSyntax& Syntax () const;

      /**
       * @brief AddCustomSyntax.
       * @param syntax syntax.
       */
      void AddCustomSyntax ( MdSyntax syntax );
    /**
     * @brief CustomSyntaxes.
     * @return [ [ nodiscard ] ] MdSyntaxList&.
     */
    [ [ nodiscard ] ] const MdSyntaxList& CustomSyntaxes () const;
    /**
     * @brief CustomSyntaxes.
     * @return [ [ nodiscard ] ] MdSyntaxList&.
     */
    [ [ nodiscard ] ] MdSyntaxList& CustomSyntaxes ();

      /**
       * @brief AddVariable.
       * @param variable variable.
       */
      void AddVariable ( MdVariable variable );
    /**
     * @brief Variables.
     * @return [ [ nodiscard ] ] MdVariableList&.
     */
    [ [ nodiscard ] ] const MdVariableList& Variables () const;
    /**
     * @brief Variables.
     * @return [ [ nodiscard ] ] MdVariableList&.
     */
    [ [ nodiscard ] ] MdVariableList& Variables ();

      /**
       * @brief ToXml.
       * @param formula_node formula_node.
       */
      void ToXml ( IXmlNode& formula_node ) const override;
      /**
       * @brief FromXml.
       * @param formula_node formula_node.
       */
      void FromXml ( const IXmlNode& formula_node ) override;

    private:
      MdSyntax syntax_;
      MdSyntaxList custom_syntax_list_;
      MdVariableList variable_list_;
  };

  }  // namespace mdf