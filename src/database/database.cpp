#include "database.h"

Database::Database(const std::string &dbName)
{
  int rc = sqlite3_open(dbName.c_str(), &db);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    db = nullptr;
  }
  else
  {
    buildDB(dbName);
  }
}

Database::~Database()
{
  if (db)
  {
    sqlite3_close(db);
  }
}

bool Database::executeSQL(const std::string &sql)
{
  char *errMsg = nullptr;
  int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

  if (rc != SQLITE_OK)
  {
    std::cerr << "SQL error (" << rc << "): " << (errMsg ? errMsg : "Unknown error") << std::endl;
    if (errMsg)
      sqlite3_free(errMsg);
    return false;
  }
  return true;
}

bool Database::productInsert(const ProductNew &product)
{
  std::string sql = "INSERT INTO Products (name, description, price) VALUES ('" +
                    product.name + "', '" + product.description + "', " +
                    std::to_string(product.price) + ");";
  return executeSQL(sql);
}

std::optional<Product> Database::productGetByName(const std::string &name)
{
  std::string sql = "SELECT * FROM Products WHERE name = '" + name + "';";
  std::vector<Product> query_results = executeQuery<Product>(sql, [](char **row) -> Product {
    return Product(atoi(row[0]), std::string(row[1]), std::string(row[2]), atof(row[3]));
  });
  if(query_results.empty())
  {
    return std::nullopt;
  }
  return query_results[0];
}

bool Database::productUpdate(const Product &product)
{
  std::string sql = "UPDATE Products SET name = '" + product.name + "', description = '" +
                    product.description + "', price = " + std::to_string(product.price) +
                    " WHERE id = " + std::to_string(product.id) + ";";
  return executeSQL(sql);
}

bool Database::productDelete(int productId)
{
  std::string sql = "DELETE FROM Products WHERE id = " + std::to_string(productId) + ";";
  return executeSQL(sql);
}

bool Database::categoryInsert(const Category &category)
{
  std::string sql = "INSERT INTO Categories (name, description) VALUES ('" +
                    category.name + "', '" + category.description + "');";
  return executeSQL(sql);
}

bool Database::categoryUpdate(const Category &category)
{
  std::string sql = "UPDATE Categories SET name = '" + category.name + "', description = '" +
                    category.description + "' WHERE id = " + std::to_string(category.id) + ";";
  return executeSQL(sql);
}

bool Database::categoryDelete(int categoryId)
{
  std::string sql = "DELETE FROM Categories WHERE id = " + std::to_string(categoryId) + ";";
  return executeSQL(sql);
}

void Database::buildDB(const std::string &name)
{
  if (!db)
    return;

  executeSQL(R"(
    CREATE TABLE IF NOT EXISTS Products (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      name TEXT NOT NULL,
      description TEXT,
      price REAL,
      UNIQUE(name)
    );
  )");

  executeSQL(R"(
    CREATE TABLE IF NOT EXISTS Categories (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      name TEXT NOT NULL,
      description TEXT,
      UNIQUE(name)
    );
  )");

  executeSQL(R"(
    CREATE TABLE IF NOT EXISTS ProductCategories (
      product_id INTEGER,
      category_id INTEGER,
      PRIMARY KEY (product_id, category_id),
      FOREIGN KEY (product_id) REFERENCES Products(id) ON DELETE CASCADE,
      FOREIGN KEY (category_id) REFERENCES Categories(id) ON DELETE CASCADE
    );
  )");
}