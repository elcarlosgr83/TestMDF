/**
 * @file MdfAttachment.h
 * @brief Wrapper for MDF attachment objects.
 *
 * The `MdfAttachment` class exposes attachment metadata and content properties.
 * Attachments may represent embedded or external files associated with an MDF
 * file.
 *
 * @ingroup mdflibrary
 */
#pragma once
#include "MdfMetaData.h"

using namespace MdfLibrary::ExportFunctions;

namespace MdfLibrary {
  /**
   * @class MdfAttachment
   * @brief MDF file attachment wrapper.
   */
  class MdfAttachment {
  private:
    mdf::IAttachment* attachment;

  public:
    /**
     * @brief Wrap an existing attachment handle.
     * @param attachment Low-level attachment pointer.
     */
    MdfAttachment ( mdf::IAttachment* attachment ) : attachment ( attachment ) {
      if ( attachment == nullptr )
      { throw std::runtime_error ( "MdfAttachment Init failed" ); }
    }

    /**
     * @brief Wrap a const attachment handle.
     * @param attachment Low-level const attachment pointer.
     */
    MdfAttachment ( const mdf::IAttachment* attachment )
      : MdfAttachment ( const_cast<mdf::IAttachment*> ( attachment ) ) {}

    ~MdfAttachment () { attachment = nullptr; }

    /**
     * @brief Returns the underlying attachment pointer.
     * @return Raw `mdf::IAttachment` pointer.
     */
    mdf::IAttachment* GetAttachment () const { return attachment; }

    /**
     * @brief Returns the attachment index.
     * @return Attachment index.
     */
    int64_t GetIndex () const { return MdfAttachmentGetIndex ( attachment ); }

    /**
     * @brief Returns the creator index.
     * @return Creator identifier index.
     */
    uint16_t GetCreatorIndex () const {
      return MdfAttachmentGetCreatorIndex ( attachment );
    }

    /**
     * @brief Set the creator index.
     * @param index Creator index to assign.
     */
    void SetCreatorIndex ( uint16_t index ) {
      MdfAttachmentSetCreatorIndex ( attachment, index );
    }

    /**
     * @brief Returns if the attachment is embedded.
     * @return `true` when the attachment is embedded.
     */
    bool GetEmbedded () const { return MdfAttachmentGetEmbedded ( attachment ); }

    /**
     * @brief Mark the attachment as embedded or external.
     * @param embedded `true` to mark as embedded.
     */
    void SetEmbedded ( bool embedded ) {
      MdfAttachmentSetEmbedded ( attachment, embedded );
    }

    /**
     * @brief Returns if the attachment content is compressed.
     * @return `true` when compression is enabled.
     */
    bool GetCompressed () const { return MdfAttachmentGetCompressed ( attachment ); }

    /**
     * @brief Enable or disable attachment compression.
     * @param compressed `true` to compress the attachment.
     */
    void SetCompressed ( bool compressed ) {
      MdfAttachmentSetCompressed ( attachment, compressed );
    }

    /**
     * @brief Returns the MD5 checksum of the attachment.
     * @return MD5 string.
     */
    std::string GetMd5 () {
      char str [ 32 + 1 ];
      MdfAttachmentGetMd5 ( attachment, str );
      return std::string ( str );
    }

    /**
     * @brief Returns the attachment file name.
     * @return File name string.
     */
    std::string GetFileName () const {
      std::string str ( MdfAttachmentGetFileName ( attachment, nullptr ) + 1, '\0' );
      str.resize ( MdfAttachmentGetFileName ( attachment, str.data () ) );
      return str;
    }

    /**
     * @brief Set the attachment file name.
     * @param name File name string.
     */
    void SetFileName ( const char* name ) {
      MdfAttachmentSetFileName ( attachment, name );
    }

    /**
     * @brief Returns the attachment file type.
     * @return File type string.
     */
    std::string GetFileType () const {
      std::string str ( MdfAttachmentGetFileType ( attachment, nullptr ) + 1, '\0' );
      str.resize ( MdfAttachmentGetFileType ( attachment, str.data () ) );
      return str;
    }

    /**
     * @brief Set the attachment file type.
     * @param type File type string.
     */
    void SetFileType ( const char* type ) {
      MdfAttachmentSetFileType ( attachment, type );
    }

    /**
     * @brief Returns the attachment metadata wrapper.
     * @return `MdfMetaData` wrapper object.
     */
    const MdfMetaData GetMetaData () const {
      return MdfAttachmentGetMetaData ( attachment );
    }

    /**
     * @brief Create new metadata for the attachment.
     * @return Newly created `MdfMetaData` wrapper.
     */
    MdfMetaData CreateMetaData () {
      return MdfAttachmentCreateMetaData ( attachment );
    }
  };
}  // namespace MdfLibrary