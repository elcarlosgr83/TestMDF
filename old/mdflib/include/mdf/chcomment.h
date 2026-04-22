/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include "mdf/mdcomment.h"


namespace mdf {

  /**
   * @brief ChComment class definition.
   */
  class ChComment : public MdComment {
  public:
    /**
     * @brief ChComment.
     */
    ChComment ();
    /**
     * @brief ChComment.
     * @param comment comment.
     */
    explicit ChComment ( std::string comment );
  private:

  };

}  // namespace mdf