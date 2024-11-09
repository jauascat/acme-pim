#pragma once

#include "menu.h"
#include "../models/pim.h"

#include "menus/products.h"

class App final : public Menu
{
public:
  App(PIM* pim);
};
