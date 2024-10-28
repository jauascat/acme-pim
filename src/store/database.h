#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <sqlite3.h>

#include "../models/product.h"
#include "../models/category.h"

class Database {
private:
  sqlite3* db;

  bool executeSQL(const std::string& sql);

public:
  Database(const std::string& dbName);
  ~Database();

  bool addProduct(const ProductNew& product);
  bool updateProduct(const ProductNew& product);
  bool deleteProduct(int productId);

  bool addCategory(const Category& category);
  bool updateCategory(const Category& category);
  bool deleteCategory(int categoryId);

  void buildDB(const std::string& name);
};