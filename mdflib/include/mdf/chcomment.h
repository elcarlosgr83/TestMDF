/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

/**
 * \file chcomment.h
 * \brief MDF core API header for comment block definitions.
 *
 * @ingroup mdf
 */

/**
 * \file chcomment.h
 * \brief MDF core API header for comment block definitions.
 *
 * @ingroup mdf
 */

#pragma once

#include "mdf/mdcomment.h"


namespace mdf {

  class ChComment : public MdComment {
  public:
    ChComment ();
    explicit ChComment ( std::string comment );
  private:

  };

}  // namespace mdf

