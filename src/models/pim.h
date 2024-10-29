#pragma once

#include <string>
#include "../database/database.h"
#include "../models/product.h"
#include "../models/category.h"

class PIM {
private:
  Database db;

public:
  PIM(const std::string& dbName);

  bool addProduct(const ProductNew& product);
  bool updateProduct(const ProductNew& product);
  bool deleteProduct(int productId);

  bool addCategory(const Category& category);
  bool updateCategory(const Category& category);
  bool deleteCategory(int categoryId);
};