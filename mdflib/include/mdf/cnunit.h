/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

/**
 * \file cnunit.h
 * \brief MDF core API header for unit definitions.
 *
 * @ingroup mdf
 */

/**
 * \file cnunit.h
 * \brief MDF core API header for unit definitions.
 *
 * @ingroup mdf
 */

#pragma once
#include <string>

#include "mdf/ccunit.h"


namespace mdf {

  class CnUnit : public CcUnit {
  public:
    CnUnit ();
    explicit CnUnit ( std::string unit );
  };

}  // namespace mdf

