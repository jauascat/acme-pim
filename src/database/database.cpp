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

// PRODUCTS

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
  if (query_results.empty())
  {
    return std::nullopt;
  }
  return query_results[0];
}

std::optional<Product> Database::productGetById(int productId)
{
  std::string sql = "SELECT * FROM Products WHERE id = " + std::to_string(productId) + ";";
  auto query_results = executeQuery<Product>(sql, [](char **row) -> Product {
    return Product(atoi(row[0]), std::string(row[1]), std::string(row[2]), atof(row[3]));
  });

  if (query_results.empty())
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

// CATEGORIES

bool Database::categoryInsert(const Category &category) {
  std::string sql = "INSERT INTO Categories (name, description) VALUES ('" +
                    category.name + "', '" + category.description + "');";
  return executeSQL(sql);
}

std::optional<Category> Database::categoryGetById(int categoryId) {
  std::string sql = "SELECT * FROM Categories WHERE id = " + std::to_string(categoryId) + ";";
  auto query_results = executeQuery<Category>(sql, [](char **row) -> Category {
      return Category(atoi(row[0]), std::string(row[1]), std::string(row[2]));
  });

  if (query_results.empty()) {
    return std::nullopt;
  }
  return query_results[0];
}

bool Database::categoryUpdate(const Category &category) {
  std::string sql = "UPDATE Categories SET name = '" + category.name + "', description = '" +
                    category.description + "' WHERE id = " + std::to_string(category.id) + ";";
  return executeSQL(sql);
}

bool Database::categoryDelete(int categoryId) {
  std::string sql = "DELETE FROM Categories WHERE id = " + std::to_string(categoryId) + ";";
  return executeSQL(sql);
}

bool Database::categoryHasProducts(int categoryId) {
  std::string sql = "SELECT COUNT(*) FROM ProductCategories WHERE category_id = " + std::to_string(categoryId) + ";";
  auto results = executeQuery<int>(sql, [](char **row) -> int {
      return atoi(row[0]);
  });
  return !results.empty() && results[0] > 0;
}

bool Database::categoryRemoveProducts(int categoryId) {
  std::string sql = "DELETE FROM ProductCategories WHERE category_id = " + std::to_string(categoryId) + ";";
  return executeSQL(sql);
}


// VARIANTS

bool Database::variantInsert(const Variant &variant)
{
  // Insertar la variante en la tabla Variants
  std::string sql = "INSERT INTO Variants (product_id) VALUES (" + std::to_string(variant.productId) + ");";
  if (!executeSQL(sql))
    return false;

  // Obtener el ID de la variante recién insertada
  int variantId = sqlite3_last_insert_rowid(db);

  // Insertar cada atributo y su valor como una sola cadena en la tabla VariantAttributes
  for (const auto &[key, value] : variant.attributes)
  {
    std::string attrSQL = "INSERT INTO VariantAttributes (variant_id, key, value) VALUES (" +
                          std::to_string(variantId) + ", '" + key + "', '" + value + "');";
    if (!executeSQL(attrSQL))
      return false;
  }

  return true;
}

std::vector<Variant> Database::getVariantsByProductId(int productId)
{
  std::string sql = "SELECT id FROM Variants WHERE product_id = " + std::to_string(productId) + ";";
  auto variantIds = executeQuery<int>(sql, [](char **row) -> int {
    return atoi(row[0]); // Mapper para obtener el ID de la variante
  });

  std::vector<Variant> variants;
  for (int variantId : variantIds)
  {
    std::string attrSQL = "SELECT key, value FROM VariantAttributes WHERE variant_id = " + std::to_string(variantId) + ";";
    auto attributes = executeQuery<std::pair<std::string, std::string>>(attrSQL, [](char **row) {
      return std::make_pair(std::string(row[0]), std::string(row[1])); // Mapper para los atributos
    });

    // Crear un mapa con los atributos como strings
    std::map<std::string, std::string> attributesMap;
    for (const auto &attribute : attributes)
    {
      attributesMap[attribute.first] = attribute.second;
    }

    // Crear la variante y añadirla al vector
    variants.emplace_back(variantId, productId, attributesMap);
  }

  return variants;
}

std::optional<Variant> Database::getVariantById(int variantId)
{
  std::string sql = "SELECT product_id FROM Variants WHERE id = " + std::to_string(variantId) + ";";
  auto productIdResult = executeQuery<int>(sql, [](char **row) -> int {
    return atoi(row[0]); // Mapper para obtener el product_id
  });

  if (productIdResult.empty())
  {
    return std::nullopt;
  }

  int productId = productIdResult[0];

  // Consultar los atributos relacionados con la variante
  std::string attrSQL = "SELECT key, value FROM VariantAttributes WHERE variant_id = " + std::to_string(variantId) + ";";
  auto attributes = executeQuery<std::pair<std::string, std::string>>(attrSQL, [](char **row) {
    return std::make_pair(std::string(row[0]), std::string(row[1])); // Mapper para los atributos
  });

  // Crear un mapa con los atributos como strings
  std::map<std::string, std::string> attributesMap;
  for (const auto &attribute : attributes)
  {
    attributesMap[attribute.first] = attribute.second;
  }

  return Variant(variantId, productId, attributesMap);
}

bool Database::variantUpdate(const Variant &variant)
{
  // Eliminar todos los atributos existentes de la variante
  std::string deleteSQL = "DELETE FROM VariantAttributes WHERE variant_id = " + std::to_string(variant.id) + ";";
  if (!executeSQL(deleteSQL))
    return false;

  // Insertar los atributos actualizados como cadenas simples
  for (const auto &[key, value] : variant.attributes)
  {
    std::string attrSQL = "INSERT INTO VariantAttributes (variant_id, key, value) VALUES (" +
                          std::to_string(variant.id) + ", '" + key + "', '" + value + "');";
    if (!executeSQL(attrSQL))
      return false;
  }

  return true;
}

bool Database::variantDelete(int variantId)
{
  // Eliminar los atributos asociados
  std::string deleteAttrSQL = "DELETE FROM VariantAttributes WHERE variant_id = " + std::to_string(variantId) + ";";
  if (!executeSQL(deleteAttrSQL))
  {
    return false;
  }

  // Eliminar la variante
  std::string deleteVariantSQL = "DELETE FROM Variants WHERE id = " + std::to_string(variantId) + ";";
  return executeSQL(deleteVariantSQL);
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

  executeSQL(R"(
    CREATE TABLE IF NOT EXISTS Variants (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      product_id INTEGER NOT NULL,
      FOREIGN KEY (product_id) REFERENCES Products(id) ON DELETE CASCADE
    );
  )");

  executeSQL(R"(
    CREATE TABLE IF NOT EXISTS VariantAttributes (
      variant_id INTEGER NOT NULL,
      key TEXT NOT NULL,
      value TEXT NOT NULL,
      FOREIGN KEY (variant_id) REFERENCES Variants(id) ON DELETE CASCADE
    );
  )");
}
