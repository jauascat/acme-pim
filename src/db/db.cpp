#include "db.h"

DBOperator::DBOperator(const std::string& dbName) {
  if (sqlite3_open(dbName.c_str(), &db)) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    db = nullptr;
  } else {
    std::cout << "Opened database successfully!" << std::endl;
  }
}

DBOperator::~DBOperator() {
  if (db) {
    sqlite3_close(db);
    std::cout << "Closed database successfully!" << std::endl;
  }
}

bool DBOperator::executeSQL(const std::string& sql) {
  char* errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return false;
  }
  return true;
}

bool DBOperator::addProduct(const Product& product) {
  std::string sql = "INSERT INTO Products (name, description, price) VALUES ('" +
    product.name + "', '" + product.description + "', " + 
    std::to_string(product.price) + ");";
  return executeSQL(sql);
}

bool DBOperator::updateProduct(const Product& product) {
  std::string sql = "UPDATE Products SET name = '" + product.name + "', description = '" + 
    product.description + "', price = " + std::to_string(product.price) +
    " WHERE id = " + std::to_string(product.id) + ";";
  return executeSQL(sql);
}

bool DBOperator::deleteProduct(int productId) {
  std::string sql = "DELETE FROM Products WHERE id = " + std::to_string(productId) + ";";
  return executeSQL(sql);
}

bool DBOperator::addCategory(const Category& category) {
  std::string sql = "INSERT INTO Categories (name, description) VALUES ('" +
    category.name + "', '" + category.description + "');";
  return executeSQL(sql);
}

bool DBOperator::updateCategory(const Category& category) {
  std::string sql = "UPDATE Categories SET name = '" + category.name + "', description = '" +
    category.description + "' WHERE id = " + std::to_string(category.id) + ";";
  return executeSQL(sql);
}

bool DBOperator::deleteCategory(int categoryId) {
  std::string sql = "DELETE FROM Categories WHERE id = " + std::to_string(categoryId) + ";";
  return executeSQL(sql);
}
