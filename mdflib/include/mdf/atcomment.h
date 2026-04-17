/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/mdcomment.h"

namespace mdf {

  /**
   * @brief AtComment class definition.
   */
  class AtComment : public MdComment {
  public:
    /**
     * @brief AtComment.
     */
    AtComment ();
    /**
     * @brief AtComment.
     * @param comment comment.
     * @return explicit.
     */
    explicit AtComment ( std::string comment );
  private:
  };

}  // namespace mdf