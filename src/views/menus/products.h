#pragma once

#include <string>
#include <utility>
#include "../../views/operation.h"
#include "../../models/pim.h"

namespace products
{
  class Add final : public Operation
  {
  public:
    Add(PIM *pim);
    void execute() override;
  };
}
