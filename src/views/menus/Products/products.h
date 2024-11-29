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

#include "../../../views/operation.h"
#include "../../../views/menu.h"
#include "../../../models/pim.h"

namespace products
{
  class Submenu final : public Menu {
    public:
      Submenu(PIM *pim);
  };

  class GetAll final : public Operation
  {
  public:
    GetAll(PIM *pim);
    void execute() override;
  };

  class GetByName final : public Operation
  {
  public:
    GetByName(PIM *pim);
    void execute() override;
  };

  class GetById final : public Operation
  {
  public:
    GetById(PIM *pim);
    void execute() override;
  };

  class GetByCategory final : public Operation
  {
  public:
    GetByCategory(PIM *pim);
    void execute() override;
  };

  class GetByVariant final : public Operation
  {
  public:
    GetByVariant(PIM *pim);
    void execute() override;
  };

  class GetByPriceRange final : public Operation
  {
  public:
    GetByPriceRange(PIM *pim);
    void execute() override;
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
