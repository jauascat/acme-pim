#include "pim.h"

bool PIM::productCreate(const ProductNew& product) {
  return db.productInsert(product);
}

std::optional<Product> PIM::productGetByName(const std::string& name) {
  return db.productGetByName(name);
}

bool PIM::productUpdate(const Product& product) {
  return db.productUpdate(product);
}

bool PIM::productDelete(int productId) {
  return db.productDelete(productId);
}

bool PIM::categoryAdd(const Category& category) {
  return db.categoryInsert(category);
}

bool PIM::categoryUpdate(const Category& category) {
  return db.categoryUpdate(category);
}

bool PIM::categoryDelete(int categoryId) {
  return db.categoryDelete(categoryId);
}
