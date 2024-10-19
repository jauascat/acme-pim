#pragma once

#include <sqlite3.h>
#include <string>
#include <iostream>
#include "../models/product.h"
#include "../models/category.h"

class DBOperator {
private:
    sqlite3* db;

    bool executeSQL(const std::string& sql);

public:
    DBOperator(const std::string& dbName);
    ~DBOperator();

    bool addProduct(const Product& product);
    bool updateProduct(const Product& product);
    bool deleteProduct(int productId);

    bool addCategory(const Category& category);
    bool updateCategory(const Category& category);
    bool deleteCategory(int categoryId);
};
