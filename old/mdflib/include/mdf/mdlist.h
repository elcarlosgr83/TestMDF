/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <string>
#include <map>

#include "mdf/mdstandardattribute.h"
#include "mdf/mdproperty.h"
#include "mdf/mdenumerate.h"

namespace mdf {
  /**
   * @brief MdList class definition.
   */
  class MdList;
  /**
   * @brief IXmlNode class definition.
   */
  class IXmlNode;

  using MdListList = std::map<std::string, MdList>;

  /**
   * @brief MdList class definition.
   */
  class MdList : public MdStandardAttribute {
  public:
    /**
     * @brief IsActive.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsActive () const override;

      /**
       * @brief Name.
       * @param name name.
       */
      void Name ( std::string name );
    /**
     * @brief Name.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Name () const;

      /**
       * @brief Description.
       * @param description description.
       */
      void Description ( std::string description );
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Description () const;

      /**
       * @brief AddProperty.
       * @param property property.
       */
      void AddProperty ( MdProperty property );
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
       * @brief ToXml.
       * @param list_node list_node.
       */
      void ToXml ( IXmlNode& list_node ) const override;
      /**
       * @brief FromXml.
       * @param root_node root_node.
       */
      void FromXml ( const IXmlNode& root_node ) override;
    protected:
    /**
     * @brief IsDuplicateName.
     * @param name name.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool IsDuplicateName ( const std::string& name ) const;

    private:
      std::string name_;
      std::string desc_;

      MdPropertyList property_list_;
      MdListList tree_list_;
      MdListList list_list_;
      MdEnumerateList enumerate_list_;

  };

  template< typename T>
  T MdList::GetPropertyValue ( const std::string& name ) const {
    const MdProperty* prop = GetProperty ( name );
    return prop != nullptr ? prop->Value<T> () : T{};
    }

}  // namespace mdf