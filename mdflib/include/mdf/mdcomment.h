/**
 * @file mdcomment.h
 * @brief MDF header declarations for mdcomment.
 */

/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/



#pragma once
#include <string>
#include <memory>
#include <functional>

#include "mdf/mdalternativename.h"
#include "mdf/mdstandardattribute.h"
#include "mdf/mdstring.h"
#include "mdf/mdlist.h"
#include "mdf/mdformula.h"
#include "mdf/mdextension.h"

namespace mdf {

  /**
   * @brief IXmlFile class definition.
   */
  class IXmlFile;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using MdExtensionCreator = std::function<MdExtensionPtr () >;

  /**
   * @brief MdComment class definition.
   */
  class MdComment {
  public:

    /**
     * @brief MdComment.
     * @param block_name block_name.
     * @return explicit.
     */
    explicit MdComment ( std::string block_name );
    /**
     * @brief ~MdComment.
     */
    virtual ~MdComment () = default;

    /**
     * @brief Comment.
     * @param comment comment.
     */
    void Comment ( std::string comment );
    /**
     * @brief Comment.
     * @param comment comment.
     */
    void Comment ( MdString comment );
    /**
     * @brief Comment.
     * @return [ [ nodiscard ] ] MdString&.
     */
    [ [ nodiscard ] ] const MdString& Comment () const;

      /**
       * @brief AddProperty.
       * @param property property.
       */
      void AddProperty ( MdProperty property );
      /**
       * @brief AddProperty.
       * @param key key.
       * @param value value.
       */
      void AddProperty ( std::string key, std::string value );
      /**
       * @brief AddTree.
       * @param tree tree.
       */
      void AddTree ( MdList tree );
      /**
       * @brief AddList.
       * @param list list.
       */
      void AddList ( MdList list );
      /**
       * @brief AddEnumerate.
       * @param enumerate enumerate.
       */
      void AddEnumerate ( MdEnumerate enumerate );

    /**
     * @brief Properties.
     * @return [ [ nodiscard ] ] MdPropertyList&.
     */
    [ [ nodiscard ] ] const MdPropertyList& Properties () const;
    /**
     * @brief Properties.
     * @return [ [ nodiscard ] ] MdPropertyList&.
     */
    [ [ nodiscard ] ] MdPropertyList& Properties ();

    /**
     * @brief GetProperty.
     * @param name name.
     * @return [ [ nodiscard ] ] MdProperty*.
     */
    [ [ nodiscard ] ] const MdProperty* GetProperty ( const std::string& name )
      const;

      template< typename T>
    /**
     * @brief GetPropertyValue.
     * @param name name.
     * @return [ [ nodiscard ] ] T.
     */
    [ [ nodiscard ] ] T GetPropertyValue ( const std::string& name ) const;

    /**
     * @brief GetEnumerate.
     * @param name name.
     * @return [ [ nodiscard ] ] MdEnumerate*.
     */
    [ [ nodiscard ] ] const MdEnumerate* GetEnumerate ( const std::string& name )
      const;

    /**
     * @brief Trees.
     * @return [ [ nodiscard ] ] MdListList&.
     */
    [ [ nodiscard ] ] const MdListList& Trees () const;
    /**
     * @brief Trees.
     * @return [ [ nodiscard ] ] MdListList&.
     */
    [ [ nodiscard ] ] MdListList& Trees ();

    /**
     * @brief Lists.
     * @return [ [ nodiscard ] ] MdListList&.
     */
    [ [ nodiscard ] ] const MdListList& Lists () const;
    /**
     * @brief Lists.
     * @return [ [ nodiscard ] ] MdListList&.
     */
    [ [ nodiscard ] ] MdListList& Lists ();

    /**
     * @brief Enumerates.
     * @return [ [ nodiscard ] ] MdEnumerateList&.
     */
    [ [ nodiscard ] ] const MdEnumerateList& Enumerates () const;
    /**
     * @brief Enumerates.
     * @return [ [ nodiscard ] ] MdEnumerateList&.
     */
    [ [ nodiscard ] ] MdEnumerateList& Enumerates ();

    /**
     * @brief Names.
     * @return [ [ nodiscard ] ] MdAlternativeName&.
     */
    [ [ nodiscard ] ] const MdAlternativeName& Names () const;
    /**
     * @brief Names.
     * @return [ [ nodiscard ] ] MdAlternativeName&.
     */
    [ [ nodiscard ] ] MdAlternativeName& Names ();

    /**
     * @brief Formula.
     * @return [ [ nodiscard ] ] MdFormula&.
     */
    [ [ nodiscard ] ] const MdFormula& Formula () const;
    /**
     * @brief Formula.
     * @return [ [ nodiscard ] ] MdFormula&.
     */
    [ [ nodiscard ] ] MdFormula& Formula ();

      /**
       * @brief SetExtensionCreator.
       * @param creator creator.
       */
      void SetExtensionCreator ( MdExtensionCreator creator );
      /**
       * @brief AddExtension.
       * @param extension extension.
       */
      void AddExtension ( MdExtensionPtr extension );
    /**
     * @brief Extensions.
     * @return [ [ nodiscard ] ] MdExtensionList&.
     */
    [ [ nodiscard ] ] const MdExtensionList& Extensions () const;
    /**
     * @brief Extensions.
     * @return [ [ nodiscard ] ] MdExtensionList&.
     */
    [ [ nodiscard ] ] MdExtensionList& Extensions ();

    /**
     * @brief ToXml.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string ToXml () const;
      /**
       * @brief FromXml.
       * @param xml_snippet xml_snippet.
       * @return virtual void.
       */
      virtual void FromXml ( const std::string& xml_snippet );
    protected:
      std::string block_name_; ///< Block name as "HD".
      MdString comment_; ///< TX tag in XML
      MdList common_property_;
      MdAlternativeName alternative_name_;
      MdFormula formula_;
      MdExtensionList extension_list_;
      MdExtensionCreator extension_creator_;

    /**
     * @brief CreateRootNode.
     * @param xml_file xml_file.
     * @param init_ho_namespace init_ho_namespace.
     * @return [ [ nodiscard ] ] virtual IXmlNode&.
     */
    [ [ nodiscard ] ] virtual IXmlNode& CreateRootNode ( IXmlFile& xml_file,
      bool init_ho_namespace ) const;
      /**
       * @brief ToXml.
       * @param root_node root_node.
       */
      void ToXml ( IXmlNode& root_node ) const;
      /**
       * @brief ToTx.
       * @param root_node root_node.
       */
      void ToTx ( IXmlNode& root_node ) const;
      /**
       * @brief ToFormula.
       * @param root_node root_node.
       */
      void ToFormula ( IXmlNode& root_node ) const;
      /**
       * @brief ToNames.
       * @param root_node root_node.
       */
      void ToNames ( IXmlNode& root_node ) const;
      /**
       * @brief ToCommonProp.
       * @param root_node root_node.
       */
      void ToCommonProp ( IXmlNode& root_node ) const;
      /**
       * @brief FromXml.
       * @param root_node root_node.
       */
      void FromXml ( const IXmlNode& root_node );

  };

  template< typename T>
  /**
   * @brief MdComment::GetPropertyValue.
   * @param name name.
   * @return T.
   */
  T MdComment::GetPropertyValue ( const std::string& name ) const {
    return common_property_.GetPropertyValue<T> ( name );
    }
}  // namespace mdf