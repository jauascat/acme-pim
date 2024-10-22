#include "setup.h"

void executeSQL(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created or already exists!" << std::endl;
    }
}

int buildDB() {
    sqlite3 *db;
    int exit = sqlite3_open("store.db", &db);
    
    if (exit) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }

    // SQL statement to create Products table
    const char *createProductsTable = R"(
        CREATE TABLE IF NOT EXISTS Products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            price REAL,
            UNIQUE(name)
        );
    )";

    // SQL statement to create Categories table
    const char *createCategoriesTable = R"(
        CREATE TABLE IF NOT EXISTS Categories (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            UNIQUE(name)
        );
    )";

    // SQL statement to create ProductCategories (N-N) table
    const char *createProductCategoriesTable = R"(
        CREATE TABLE IF NOT EXISTS ProductCategories (
            product_id INTEGER,
            category_id INTEGER,
            PRIMARY KEY (product_id, category_id),
            FOREIGN KEY (product_id) REFERENCES Products(id) ON DELETE CASCADE,
            FOREIGN KEY (category_id) REFERENCES Categories(id) ON DELETE CASCADE
        );
    )";

    executeSQL(db, createProductsTable);
    executeSQL(db, createCategoriesTable);
    executeSQL(db, createProductCategoriesTable);

    sqlite3_close(db);
    return 0;
}