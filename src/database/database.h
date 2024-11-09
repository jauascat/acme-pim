#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <sqlite3.h>
#include <vector>
#include <functional>
#include <optional>

#include "../models/product.h"
#include "../models/category.h"

class Database
{
private:
  sqlite3 *db;

  bool executeSQL(const std::string &sql);

  template <typename T>
  std::vector<T> executeQuery(const std::string &sql, std::function<T(char **)> transformCallback)
  {
    std::vector<T> results;
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
      while (sqlite3_step(stmt) == SQLITE_ROW)
      {
        int columnCount = sqlite3_column_count(stmt);
        char **row = new char *[columnCount];
        for (int i = 0; i < columnCount; ++i)
        {
          row[i] = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
        }
        T rowValue = transformCallback(row);
        results.push_back(rowValue);
        delete[] row;
      }
    }
    else
    {
      std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return results;
  }

public:
  Database(const std::string &dbName);
  ~Database();
  void buildDB(const std::string &name);

  bool productInsert(const ProductNew &product);
  std::optional<Product> productGetByName(const std::string &name);
  bool productUpdate(const ProductNew &product);
  bool productDelete(int productId);

  bool categoryInsert(const Category &category);
  bool categoryUpdate(const Category &category);
  bool categoryDelete(int categoryId);
};