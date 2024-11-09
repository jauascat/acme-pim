#pragma once

#include <string>
#include <optional>
#include "../database/database.h"
#include "../models/product.h"
#include "../models/category.h"

class PIM {
private:
  Database db;

public:
  PIM(const std::string& dbName = std::string("pim_v2.db"))
    : db(dbName) {}

  bool productAdd(const ProductNew& product);
  std::optional<Product> productGetByName(const std::string& name);
  bool productUpdate(const ProductNew& product);
  bool productDelete(int productId);

  bool categoryAdd(const Category& category);
  bool categoryUpdate(const Category& category);
  bool categoryDelete(int categoryId);
};