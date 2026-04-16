/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>
#include <string>

#include "MdfExport.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @file MdfETag.h
   * @brief Wrapper for MDF metadata tags.
   *
   * `MdfETag` wraps a single metadata tag and provides typed access to its value,
   * type, unit and language properties.
   *
   * @ingroup mdflibrary
   */
  class MdfETag {
  private:
    bool isNew = false;
    mdf::ETag* eTag;

  public:
    /**
     * @brief Wrap an existing ETag handle.
     * @param eTag Low-level ETag pointer.
     */
    MdfETag ( mdf::ETag* eTag ) : eTag ( eTag ) {
      if ( eTag == nullptr ) {
        throw std::runtime_error ( "MdfETag Init failed" );
      }
    }

    /**
     * @brief Wrap a const ETag handle.
     * @param eTag Low-level const ETag pointer.
     */
    MdfETag ( const mdf::ETag* eTag ) : MdfETag ( const_cast<mdf::ETag*>
          ( eTag ) ) {}

    /**
     * @brief Create a new ETag.
     */
    MdfETag () : MdfETag ( MdfETagInit () ) { isNew = true; }

    /**
     * @brief Destroy the ETag wrapper.
     */
    ~MdfETag () {
      if ( isNew ) {
        MdfETagUnInit ( eTag );
      }

      eTag = nullptr;
    }

    MdfETag ( const MdfETag& ) = delete;

    /**
     * @brief Move constructor.
     */
    MdfETag ( MdfETag&& eTag ) {
      if ( isNew ) {
        MdfETagUnInit ( this->eTag );
      }

      this->isNew = eTag.isNew;
      this->eTag = eTag.eTag;
      eTag.isNew = false;
      eTag.eTag = nullptr;
    }

    /**
     * @brief Returns the underlying ETag pointer.
     * @return Raw `mdf::ETag` pointer.
     */
    mdf::ETag* GetETag () const { return eTag; }

    /**
     * @brief Returns the tag name.
     * @return Tag name string.
     */
    std::string GetName () const {
      std::string str ( MdfETagGetName ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetName ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tag name.
     * @param name Tag name.
     */
    void SetName ( const char* name ) { MdfETagSetName ( eTag, name ); }

    /**
     * @brief Returns the tag description.
     * @return Description string.
     */
    std::string GetDescription () const {
      std::string str ( MdfETagGetDescription ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetDescription ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tag description.
     * @param desc Description string.
     */
    void SetDescription ( const char* desc ) { MdfETagSetDescription ( eTag, desc ); }

    /**
     * @brief Returns the tag unit.
     * @return Unit string.
     */
    std::string GetUnit () const {
      std::string str ( MdfETagGetUnit ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetUnit ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tag unit.
     * @param unit Unit string.
     */
    void SetUnit ( const char* unit ) { MdfETagSetUnit ( eTag, unit ); }

    /**
     * @brief Returns the unit reference.
     * @return Unit reference string.
     */
    std::string GetUnitRef () const {
      std::string str ( MdfETagGetUnitRef ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetUnitRef ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the unit reference.
     * @param unit Unit reference string.
     */
    void SetUnitRef ( const char* unit ) { MdfETagSetUnitRef ( eTag, unit ); }

    /**
     * @brief Returns the tag type.
     * @return Type string.
     */
    std::string GetType () const {
      std::string str ( MdfETagGetType ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetType ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tag type.
     * @param type Type string.
     */
    void SetType ( const char* type ) { MdfETagSetType ( eTag, type ); }

    /**
     * @brief Returns the tag data type.
     * @return Data type enum.
     */
    ETagDataType GetDataType () const { return MdfETagGetDataType ( eTag ); }

    /**
     * @brief Set the tag data type.
     * @param type Data type.
     */
    void SetDataType ( ETagDataType type ) { MdfETagSetDataType ( eTag, type ); }

    /**
     * @brief Returns the language.
     * @return Language string.
     */
    std::string GetLanguage () const {
      std::string str ( MdfETagGetLanguage ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetLanguage ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the language.
     * @param language Language string.
     */
    void SetLanguage ( const char* language ) { MdfETagSetLanguage ( eTag, language ); }

    /**
     * @brief Returns whether the tag is read-only.
     * @return `true` when read-only.
     */
    bool GetReadOnly () const { return MdfETagGetReadOnly ( eTag ); }

    /**
     * @brief Set the read-only flag.
     * @param read_only Read-only flag.
     */
    void SetReadOnly ( bool read_only ) { MdfETagSetReadOnly ( eTag, read_only ); }

    /**
     * @brief Returns the tag value as string.
     * @return Value string.
     */
    std::string GetValueAsString () const {
      std::string str ( MdfETagGetValueAsString ( eTag, nullptr ) + 1, '\0' );
      str.resize ( MdfETagGetValueAsString ( eTag, str.data () ) );
      return str;
    }

    /**
     * @brief Set the tag value as string.
     * @param value Value string.
     */
    void SetValueAsString ( const char* value ) {
      MdfETagSetValueAsString ( eTag, value );
    }

    /**
     * @brief Returns the tag value as float.
     * @return Floating point value.
     */
    double GetValueAsFloat () const { return MdfETagGetValueAsFloat ( eTag ); }

    /**
     * @brief Set the tag value as float.
     * @param value Floating point value.
     */
    void SetValueAsFloat ( double value ) { MdfETagSetValueAsFloat ( eTag, value ); }

    /**
     * @brief Returns the tag value as boolean.
     * @return Boolean value.
     */
    bool GetValueAsBoolean () const { return MdfETagGetValueAsBoolean ( eTag ); }

    /**
     * @brief Set the tag value as boolean.
     * @param value Boolean value.
     */
    void SetValueAsBoolean ( bool value ) { MdfETagSetValueAsBoolean ( eTag, value ); }

    /**
     * @brief Returns the tag value as signed integer.
     * @return Signed value.
     */
    int64_t GetValueAsSigned () const { return MdfETagGetValueAsSigned ( eTag ); }

    /**
     * @brief Set the tag value as signed integer.
     * @param value Signed value.
     */
    void SetValueAsSigned ( int64_t value ) { MdfETagSetValueAsSigned ( eTag, value ); }

    /**
     * @brief Returns the tag value as unsigned integer.
     * @return Unsigned value.
     */
    uint64_t GetValueAsUnsigned () const {
      return MdfETagGetValueAsUnsigned ( eTag );
    }

    /**
     * @brief Set the tag value as unsigned integer.
     * @param value Unsigned value.
     */
    void SetValueAsUnsigned ( uint64_t value ) {
      MdfETagSetValueAsUnsigned ( eTag, value );
    }
  };
}  // namespace MdfLibrary