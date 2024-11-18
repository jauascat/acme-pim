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
  bool productCreate(const ProductNew &product, int categoryId);
  std::optional<Product> productGetByName(const std::string &name);
  std::optional<Product> productGetById(int productId);
  std::vector<Product> productGetAll();
  std::vector<Product> productGetByCategory(std:: string category);
  std::vector<Product> productGetByPriceRange(double firstRange, double lastRange);
  bool productUpdate(const Product &product);
  bool productDelete(int productId);

  // Category CRUD
  bool categoryCreate(const Category &category);
  std::optional<Category> categoryGetById(int categoryId);
    std::optional<Category> categoryGetByProductId(int productId);
  std::vector<Category> categoryGetAll();
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
