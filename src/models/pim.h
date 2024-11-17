#pragma once

#include <string>
#include <optional>
#include "../database/database.h"
#include "../models/product.h"
#include "../models/category.h"
#include "../models/variant.h"

class PIM {
private:
  Database db;

public:
  PIM(const std::string &dbName = std::string("pim_v2.db"))
      : db(dbName) {}

  // Product CRUD
  bool productCreate(const ProductNew &product);
  std::optional<Product> productGetByName(const std::string &name);
  std::optional<Product> productGetById(int productId);
  bool productUpdate(const Product &product);
  bool productDelete(int productId);

  // Category CRUD
  bool categoryCreate(const Category &category);
  std::optional<Category> categoryGetById(int categoryId);
  bool categoryUpdate(const Category &category);
  bool categoryDelete(int categoryId);
  bool categoryHasProducts(int categoryId);
  void categoryRemoveProducts(int categoryId);

  // Variant CRUD
  std::vector<Variant> getVariantsByProductId(int productId);
  std::optional<Variant> getVariantById(int variantId);
  bool addVariant(const Variant &variant);
  bool updateVariant(const Variant &variant);
  bool deleteVariant(int variantId);
};
