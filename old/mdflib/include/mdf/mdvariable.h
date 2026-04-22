/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include <mdf/mdstring.h>

namespace mdf {

  /**
   * @brief MdVariable class definition.
   */
  class MdVariable;

  using MdVariableList = std::map<std::string, MdVariable>;
  using MdArrayIndexList = std::vector<uint64_t>;

  /**
   * @brief MdVariable class definition.
   */
  class MdVariable : public MdString {
  public:
    /**
     * @brief Variable.
     * @param variable variable.
     */
    void Variable ( std::string variable );
    /**
     * @brief Variable.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& Variable () const;

      /**
       * @brief CnBlockName.
       * @param name name.
       */
      void CnBlockName ( std::string name );
    /**
     * @brief CnBlockName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& CnBlockName () const;

      /**
       * @brief CnSourceName.
       * @param name name.
       */
      void CnSourceName ( std::string name );
    /**
     * @brief CnSourceName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& CnSourceName () const;

      /**
       * @brief CnSourcePath.
       * @param path path.
       */
      void CnSourcePath ( std::string path );
    /**
     * @brief CnSourcePath.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& CnSourcePath () const;

      /**
       * @brief CgBlockName.
       * @param name name.
       */
      void CgBlockName ( std::string name );
    /**
     * @brief CgBlockName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& CgBlockName () const;

      /**
       * @brief CgSourceName.
       * @param name name.
       */
      void CgSourceName ( std::string name );
    /**
     * @brief CgSourceName.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& CgSourceName () const;

      /**
       * @brief CgSourcePath.
       * @param path path.
       */
      void CgSourcePath ( std::string path );
    /**
     * @brief CgSourcePath.
     * @return [ [ nodiscard ] ] std::string&.
     */
    [ [ nodiscard ] ] const std::string& CgSourcePath () const;

      /**
       * @brief AddArrayIndex.
       * @param index index.
       */
      void AddArrayIndex ( uint64_t index );
    /**
     * @brief ArrayIndexes.
     * @return [ [ nodiscard ] ] MdArrayIndexList&.
     */
    [ [ nodiscard ] ] const MdArrayIndexList& ArrayIndexes () const;
    /**
     * @brief ArrayIndexes.
     * @return [ [ nodiscard ] ] MdArrayIndexList&.
     */
    [ [ nodiscard ] ] MdArrayIndexList& ArrayIndexes ();

      /**
       * @brief Raw.
       * @param raw raw.
       */
      void Raw ( bool raw );
    /**
     * @brief Raw.
     * @return [ [ nodiscard ] ] bool.
     */
    [ [ nodiscard ] ] bool Raw () const;

      /**
       * @brief ToXml.
       * @param root_node root_node.
       * @param tag_name tag_name.
       */
      void ToXml ( IXmlNode& root_node, const std::string& tag_name ) const override;
      /**
       * @brief FromXml.
       * @param var_node var_node.
       */
      void FromXml ( const IXmlNode& var_node ) override;
    private:
      std::string cn_; ///< CN block name.
      std::string cs_; ///< CN source (SI) name.
      std::string cp_; ///< CN source (SI) path.
      std::string gn_; ///< CG block name.
      std::string gs_; ///< CG source (SI) name.
      std::string gp_; ///< CG source (SI) path.

      std::vector<uint64_t> index_list_; // CA array index

      bool raw_ = false;
  };

  }  // namespace mdf