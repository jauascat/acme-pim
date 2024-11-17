#pragma once

#include "menu.h"
#include "../models/pim.h"

#include "menus/Products/products.h"
#include "menus/Variants/variants.h"

class App final : public Menu
{
public:
  App(PIM* pim);
};
