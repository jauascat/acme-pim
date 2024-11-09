#include "pim.h"

PIM::PIM(const std::string& dbName) : db(dbName) {}

bool PIM::addProduct(const ProductNew& product) {
  return db.addProduct(product);
}

bool PIM::updateProduct(const ProductNew& product) {
  return db.updateProduct(product);
}

bool PIM::deleteProduct(int productId) {
  return db.deleteProduct(productId);
}

bool PIM::addCategory(const Category& category) {
  return db.addCategory(category);
}

bool PIM::updateCategory(const Category& category) {
  return db.updateCategory(category);
}

bool PIM::deleteCategory(int categoryId) {
  return db.deleteCategory(categoryId);
}
