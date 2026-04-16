/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

/**
 * \file dgcomment.h
 * \brief MDF core API header for comment block definitions.
 *
 * @ingroup mdf
 */

/**
 * \file dgcomment.h
 * \brief MDF core API header for comment block definitions.
 *
 * @ingroup mdf
 */

#pragma once

#include <string>

#include "mdf/mdcomment.h"

namespace mdf {

  class DgComment : public MdComment {
  public:
    DgComment ();
    explicit DgComment ( std::string comment );
  };

}  // namespace mdf

