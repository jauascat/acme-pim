#include "pim.h"

// Product CRUD
bool PIM::productCreate(const ProductNew &product) {
  return db.productInsert(product);
}

std::optional<Product> PIM::productGetByName(const std::string &name) {
  return db.productGetByName(name);
}

std::optional<Product> PIM::productGetById(int productId) {
  return db.productGetById(productId);
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
