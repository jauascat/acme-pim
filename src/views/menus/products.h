#pragma once

#include <string>
#include <utility>
#include "../../views/operation.h"
#include "../../views/menu.h"
#include "../../models/pim.h"

namespace products
{
  class Submenu final : public Menu {
    public:
      Submenu(PIM *pim);
  };

  class Add final : public Operation
  {
  public:
    Add(PIM *pim);
    void execute() override;
  };

  class Update final : public Operation
  {
  public:
    Update(PIM *pim);
    void execute() override;
  };
}
