#include "pim.h"

// Product CRUD
bool PIM::productCreate(const ProductNew &product, int categoryId) {
  return db.productInsert(product, categoryId);
}

std::optional<Product> PIM::productGetByName(const std::string &name) {
  return db.productGetByName(name);
}

std::optional<Product> PIM::productGetById(int productId) {
  return db.productGetById(productId);
}

std::vector<Product> PIM::productGetByCategory(std::string category) {
  return db.productGetByCategory(category);
}

std::vector<Product> PIM::productGetByPriceRange(double firstRange, double lastRange) {
  return db.productGetByPriceRange(firstRange, lastRange);
}

std::vector<Product> PIM::productGetAll() {
  return db.productGetAll();
}

bool PIM::productUpdate(const Product &product) {
  return db.productUpdate(product);
}

bool PIM::productDelete(int productId) {
  return db.productDelete(productId);
}

// Category CRUD
bool PIM::categoryCreate(const Category &category) {
  return db.categoryInsert(category);
}

std::optional<Category> PIM::categoryGetById(int categoryId) {
  return db.categoryGetById(categoryId);
}

std::optional<Category> PIM::categoryGetByProductId(const int productId) {
  return db.categoryGetByProductId(productId);
}

std::vector<Category> PIM::categoryGetAll() {
  return db.categoryGetAll();
}

bool PIM::categoryUpdate(const Category &category) {
  return db.categoryUpdate(category);
}

bool PIM::categoryDelete(int categoryId) {
  return db.categoryDelete(categoryId);
}

bool PIM::categoryHasProducts(int categoryId) {
  return db.categoryHasProducts(categoryId);
}

void PIM::categoryRemoveProducts(int categoryId) {
  db.categoryRemoveProducts(categoryId);
}

// Variant CRUD
std::vector<Variant> PIM::getVariantsByProductId(int productId) {
  return db.getVariantsByProductId(productId);
}

std::optional<Variant> PIM::getVariantById(int variantId) {
  return db.getVariantById(variantId);
}

bool PIM::addVariant(const Variant &variant) {
  return db.variantInsert(variant);
}

bool PIM::updateVariant(const Variant &variant) {
  return db.variantUpdate(variant);
}

bool PIM::deleteVariant(int variantId) {
  return db.variantDelete(variantId);
}
