/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

/**
 * \file atcomment.h
 * \brief MDF core API header for comment block definitions.
 *
 * @ingroup mdf
 */

/**
 * \file atcomment.h
 * \brief MDF core API header for comment block definitions.
 *
 * @ingroup mdf
 */

#pragma once

#include "mdf/mdcomment.h"

namespace mdf {

  class AtComment : public MdComment {
  public:
    AtComment ();
    explicit AtComment ( std::string comment );
  private:
  };

}  // namespace mdf

