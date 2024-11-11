#pragma once

#include <string>
#include <utility>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <optional>
#include <variant>
#include <any>

#include "../../views/operation.h"
#include "../../views/menu.h"
#include "../../models/pim.h"

namespace products
{
  class Submenu final : public Menu {
    public:
      Submenu(PIM *pim);
  };

  class Create final : public Operation
  {
  public:
    Create(PIM *pim);
    void execute() override;
  };

  class Update final : public Operation
  {
  public:
    Update(PIM *pim);
    void execute() override;
  };

  class Delete final : public Operation
  {
  public:
    Delete(PIM *pim);
    void execute() override;
  };
}
