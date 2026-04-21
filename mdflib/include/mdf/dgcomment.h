/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once

#include <string>

#include "mdf/mdcomment.h"

namespace mdf {

  /**
   * @brief DgComment class definition.
   */
  class DgComment : public MdComment {
  public:
    /**
     * @brief DgComment.
     */
    DgComment ();
    /**
     * @brief DgComment.
     * @param comment comment.
     */
    explicit DgComment ( std::string comment );
  };

}  // namespace mdf