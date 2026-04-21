/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */



#pragma once
#include <string>

#include "mdf/ccunit.h"


namespace mdf {

  /**
   * @brief CnUnit class definition.
   */
  class CnUnit : public CcUnit {
  public:
    /**
     * @brief CnUnit.
     */
    CnUnit ();
    /**
     * @brief CnUnit.
     * @param unit unit.
     */
    explicit CnUnit ( std::string unit );
  };

}  // namespace mdf