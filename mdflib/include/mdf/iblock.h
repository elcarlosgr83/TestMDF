/*
 * * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

/** \file iblock.h
 * \brief All MDF blocks inherits from the IBlock class. The interface class
 * is used internally in lists. The user should not use this class.
 */
#pragma once
#include <cstdint>
#include <string>


namespace mdf {
  /** \brief Base class for all MDF blocks.
   *
   */
  class IBlock {
  public:
    virtual ~IBlock () = default; ///< Default destructor

    /** \brief File position within the file.
     *
     * The Index() function returns the block's file position. The position
     * gives each block a unique index/identity.
     *
     * If the file position is 0, the block has not been written yet. This is
     * frequently used to detect if the block should be written or updated.
     * @return File position of the block.
     */
    [ [ nodiscard ] ] virtual int64_t Index () const = 0;

      /** \brief Returns the block type.
       *
       * The block type is a 2-character string, for example 'AT' or 'DT'. In MDF
       * 4, the block type is actually 4 characters but this function removes the
       * first two characters.
       * @return Block type string (2 characters).
       */
    [ [ nodiscard ] ] virtual std::string BlockType () const = 0;

  };

  }  // namespace mdf
