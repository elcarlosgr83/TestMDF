/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>

#include "mdf/ichannel.h"
#include "mdf/ichannelgroup.h"
#include "mdf/idatagroup.h"
#include "mdf/iblock.h"
#include "mdf/chcomment.h"

namespace mdf {

  /** \brief Support structure that holds a DG/CG/CN relation. */
  struct ElementLink {
    const IDataGroup* data_group = nullptr; ///< Pointer to a DG block.
    const IChannelGroup* channel_group = nullptr; ///< Pointer to a CG block.
    const IChannel* channel = nullptr; ///< Pointer to a CN block.
  };

  /** \brief Block type */
  enum class ChType : uint8_t {
    Group = 0, ///< Define a group.
    Function = 1, ///< Define a function.
    Structure = 2, ///< Define a structure.
    MapList = 3, ///< Define a map list.
    InputVariable = 4, ///< Define input variables.
    OutputVariable = 5, ///< Define output variables.
    LocalVariable = 6, ///< Define local variables.
    CalibrationDefinition = 7, ///< Define calibration define objects.
    CalibrationObject = 8 ///< Define calibration reference objects.
  };

  /** \brief Channel hierarchy (CH) block. */
  class IChannelHierarchy : public IBlock {
  public:

    /**
     * @brief Name.
     * @param name name.
     * @return virtual void.
     */
    virtual void Name ( const std::string& name ) = 0; ///< Sets name.
    /**
     * @brief Name.
     * @return [ [ nodiscard ] ] virtual std::string&.
     */
    [ [ nodiscard ] ] virtual const std::string& Name () const = 0; ///< Name.

      /**
       * @brief Type.
       * @param type type.
       * @return virtual void.
       */
      virtual void Type ( ChType type ) = 0; ///< Sets the block type.
    /**
     * @brief Type.
     * @return [ [ nodiscard ] ] virtual ChType.
     */
    [ [ nodiscard ] ] virtual ChType Type () const = 0; ///< Block type.
    /**
     * @brief TypeToString.
     * @return [ [ nodiscard ] ] std::string.
     */
    [ [ nodiscard ] ] std::string TypeToString () const; ///< Block type as text.

      /**
       * @brief Description.
       * @param description description.
       * @return virtual void.
       */
      virtual void Description ( const std::string& description )
      = 0; ///< Sets the descriptive text.
    /**
     * @brief Description.
     * @return [ [ nodiscard ] ] virtual std::string.
     */
    [ [ nodiscard ] ] virtual std::string Description () const =
      0; ///< Description.

      /** \brief Returns an interface against an MD4 block
       *
       * @return Pointer to a meta data block.
       */
    /**
     * @brief CreateMetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual IMetaData* CreateMetaData () = 0;

      /** \brief Returns an constant interface against a MD4 block
       *
       * @return Pointer to a meta data block.
       */
    /**
     * @brief MetaData.
     * @return [ [ nodiscard ] ] virtual IMetaData*.
     */
    [ [ nodiscard ] ] virtual const IMetaData* MetaData () const = 0;

      /** \brief Adds an element link.
       * @param element Element link to add.
       */
      /**
       * @brief AddElementLink.
       * @param element element.
       * @return virtual void.
       */
      virtual void AddElementLink ( const ElementLink& element ) = 0;

      /** \brief Returns a list of element links.
       * @return Element link list.
       */
    /**
     * @brief ElementLinks.
     * @return [ [ nodiscard ] ] virtual std::vector<ElementLink>&.
     */
    [ [ nodiscard ] ] virtual const std::vector<ElementLink>& ElementLinks ()
      const = 0;

      /** \brief Create a CH block.
       * @return New channel hierarchy block.
       */
    /**
     * @brief CreateChannelHierarchy.
     * @return [ [ nodiscard ] ] virtual IChannelHierarchy*.
     */
    [ [ nodiscard ] ] virtual IChannelHierarchy* CreateChannelHierarchy () = 0;

      /** \brief Returns a list of CH blocks.
       * @return List of channel hierarchy blocks.
       */
    /**
     * @brief ChannelHierarchies.
     * @return [ [ nodiscard ] ] virtual std::vector<IChannelHierarchy*>.
     */
    [ [ nodiscard ] ] virtual std::vector<IChannelHierarchy*> ChannelHierarchies ()
      const = 0;

      /** \brief Sets the channel hierarchy comment.
       * @param ch_comment Channel hierarchy comment object.
       */
      /**
       * @brief SetChComment.
       * @param ch_comment ch_comment.
       */
      void SetChComment ( const ChComment& ch_comment );
      /** \brief Retrieves the channel hierarchy comment.
       * @param ch_comment Receives the channel hierarchy comment object.
       */
      /**
       * @brief GetChComment.
       * @param ch_comment ch_comment.
       */
      void GetChComment ( ChComment& ch_comment ) const;
  };
  }  // namespace mdf