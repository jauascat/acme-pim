#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include <limits>
#include <sqlite3.h>

#include "src/models/product.h"
#include "src/models/category.h"

class Database
{
private:
  sqlite3 *db;

  bool executeSQL(const std::string &sql)
  {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error (" << rc << "): " << (errMsg ? errMsg : "Unknown error") << std::endl;
      if (errMsg) sqlite3_free(errMsg);
      return false;
    }
    return true;
  }

public:
  Database(const std::string &dbName)
  {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      db = nullptr;
    } else {
      buildDB(dbName);
    }
  }

  ~Database()
  {
    if (db)
    {
      sqlite3_close(db);
    }
  }

  bool addProduct(const ProductNew &product)
  {
    std::string sql = "INSERT INTO Products (name, description, price) VALUES ('" +
                      product.name + "', '" + product.description + "', " +
                      std::to_string(product.price) + ");";
    return executeSQL(sql);
  }

  bool updateProduct(const ProductNew &product)
  {
    std::string sql = "UPDATE Products SET name = '" + product.name + "', description = '" +
                      product.description + "', price = " + std::to_string(product.price) +
                      " WHERE id = " + std::to_string(product.id) + ";";
    return executeSQL(sql);
  }

  bool deleteProduct(int productId)
  {
    std::string sql = "DELETE FROM Products WHERE id = " + std::to_string(productId) + ";";
    return executeSQL(sql);
  }

  bool addCategory(const Category &category)
  {
    std::string sql = "INSERT INTO Categories (name, description) VALUES ('" +
                      category.name + "', '" + category.description + "');";
    return executeSQL(sql);
  }

  bool updateCategory(const Category &category)
  {
    std::string sql = "UPDATE Categories SET name = '" + category.name + "', description = '" +
                      category.description + "' WHERE id = " + std::to_string(category.id) + ";";
    return executeSQL(sql);
  }

  bool deleteCategory(int categoryId)
  {
    std::string sql = "DELETE FROM Categories WHERE id = " + std::to_string(categoryId) + ";";
    return executeSQL(sql);
  }

  void buildDB(const std::string& name)
  {
    if(!db) {
      return;
    }
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
};

class PIM {
private:
  Database db;
public:
  PIM(const std::string &dbName) : db(dbName) {

  }

  bool addProduct(const ProductNew& product) {
    return db.addProduct(product);
  }

  bool updateProduct(const ProductNew& product) {
    return db.updateProduct(product);
  }

  bool deleteProduct(int productId) {
    return db.deleteProduct(productId);
  }

  bool addCategory(const Category& category) {
    return db.addCategory(category);
  }

  bool updateCategory(const Category& category) {
    return db.updateCategory(category);
  }

  bool deleteCategory(int categoryId) {
    return db.deleteCategory(categoryId);
  }
};

class TerminalOperation
{
public:
  virtual void execute() = 0;
  virtual ~TerminalOperation() {}
  std::string getDictionaryDescription() const
  {
    return _dictionaryDescription;
  }
private:

protected:
  PIM *_pim;
  std::string _dictionaryDescription;
  std::string _dictionaryTitle;
  std::string _dictionaryPrompt;

  template <typename... Args>
  void _print(Args &&...args)
  {
    ((std::cout << std::forward<Args>(args)), ...);
  }

  template <typename T>
  T _getUserInput(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate)
  {
    T value;
    while (true)
    {
      try
      {
        _print(prompt);
        std::cin >> value;

        if (std::cin.fail())
        {
          throw std::invalid_argument("read input error");
        }

        auto [isValid, validationMsg] = validate(value);
        if (!isValid)
        {
          throw std::invalid_argument(validationMsg);
        }

        break;
      }
      catch (const std::exception &e)
      {
        _print(e.what(), "\n");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    return value;
  }

  void _setPIM(PIM *pim)
  {
    _pim = pim;
  }


  PIM* _getPIM()
  {
    return _pim;
  }

  void _setDictionaryDescription(const std::string &description)
  {
    _dictionaryDescription = description;
  }

  void _setDictionaryTitle(const std::string &title)
  {
    _dictionaryTitle = title;
  }

  void _setDictionaryPrompt(const std::string &prompt)
  {
    _dictionaryPrompt = prompt;
  }

  std::string _getDictionaryTitle() const
  {
    return _dictionaryTitle;
  }

  std::string _getDictionaryPrompt() const
  {
    return _dictionaryPrompt;
  }
};

class TerminalMenu : public TerminalOperation
{
private:
  std::vector<std::unique_ptr<TerminalOperation>> _menuOptions;
  std::string _dictionaryInvalidOption;
  std::string _dictionaryExit;

protected:
  void _setDictionaryInvalidOption(const std::string &invalidOptionMessage)
  {
    _dictionaryInvalidOption = invalidOptionMessage;
  }

  void _setDictionaryExit(const std::string &exitMessage)
  {
    _dictionaryExit = exitMessage;
  }

  std::string _getDictionaryInvalidOption() const
  {
    return _dictionaryInvalidOption;
  }

  std::string _getDictionaryExit() const
  {
    return _dictionaryExit;
  }

  int _getOptionsQuantity() const
  {
    return static_cast<int>(_menuOptions.size());
  }

  template <typename T>
  void _setMenuOption(T &&operation)
  {
    _menuOptions.push_back(std::make_unique<T>(operation));
  }

  void _showMenuOptions()
  {
    int optionsQuantity = _getOptionsQuantity();
    _print("\n===== ", _getDictionaryTitle(), " =====\n");
    for (size_t i = 0; i < optionsQuantity; ++i)
    {
      _print(i + 1, ". ", _menuOptions[i]->getDictionaryDescription(), "\n");
    }
    _print(optionsQuantity + 1, ". Exit\n");
  }

  int _getUserInputOption()
  {
    return _getUserInput<int>(
      _getDictionaryPrompt(),
      [this](const int &inputOption) -> std::pair<bool, std::string>
      {
        if (inputOption < 1 || inputOption > _getOptionsQuantity() + 1)
        {
          return std::make_pair(false, _getDictionaryInvalidOption());
        }
        return std::make_pair(true, std::string());
      }
      );
  }

public:
  void execute()
  {
    while (true)
    {
      _showMenuOptions();
      int selectedOption = _getUserInputOption();

      if (selectedOption == selectedOption + 1)
      {
        _print(_getDictionaryExit());
        break;
      }
      _menuOptions[selectedOption - 1]->execute();
    }
  }
};

class FormProductAdd final : public TerminalOperation
{
public:
  FormProductAdd(PIM* pim)
  {
    _setPIM(pim);
    _setDictionaryDescription("Crear un producto");
    _setDictionaryPrompt("Ingrese el nombre del producto:");
  }
  void execute() override
  {
    _print(_getDictionaryPrompt());
    std::string name = _getNewProductName();
    std::string description = _getNewProductDescription();
    double price = _getNewProductPrice();
    const ProductNew product(name, description, price);
    _pim->addProduct(product);
  }

private:
  std::string _getNewProductName()
  {
    return _getUserInput<std::string>(
        "Ingrese el nombre del producto: ",
        [](const std::string &value)
        {
          bool isValid = !value.empty();
          if (!isValid)
          {
            return std::make_pair(isValid, "El nombre del producto no puede estar vacio.");
          }
          return std::make_pair(isValid, "");
        });
  }
  std::string _getNewProductDescription()
  {
    return _getUserInput<std::string>(
        "Ingrese la descripcion del producto: ",
        [](const std::string &value)
        {
          bool isValid = !value.empty();
          if (!isValid)
          {
            return std::make_pair(isValid, "La descripcion del producto no puede estar vacia.");
          }
          return std::make_pair(isValid, "");
        });
  }
  double _getNewProductPrice()
  {
    return _getUserInput<double>(
        "Ingrese el precio del producto: ",
        [](const double &value)
        {
          bool isValid = value > 0;
          if (!isValid)
          {
            return std::make_pair(isValid, "El precio del producto debe ser mayor a cero.");
          }
          return std::make_pair(isValid, "");
        });
  }
};

// class FormProductEdit final : public TerminalOperation
// {
// public:
//   FormProductEdit(PIM* pim)
//   {
//     _setPIM(pim);
//     _setDictionaryDescription("Editar un producto");
//     _setDictionaryPrompt("Ingrese el nombre del producto:");
//   }
//   void execute() override
//   {
//     _print(_getDictionaryPrompt());
//     Product productToEdit = _getProductToEditByName();
//     std::string description = _getNewProductDescription();
//     double price = _getNewProductPrice();
//     const ProductNew product(name, description, price);
//     _pim->updateProduct(product);
//   }

// private:
//   Product _getProductToEditByName()
//   {
//     return _getUserInput<Product>(
//         "Ingrese el nombre del producto: ",
//         [this](const Product &value)
//         {
//           bool isValid = !value.name.empty();
//           Product product = this->_pim->getProductByName(value.name);
//           if (!isValid)
//           {
//             return std::make_pair(isValid, "El nombre del producto no puede estar vacio.");
//           }
//           return std::make_pair(isValid, "");
//         });
//   }
// };

class App final : public TerminalMenu
{
public:
  App(PIM* pim)
  {
    _setPIM(pim);
    _setDictionaryTitle("Proyecto!");
    _setDictionaryPrompt("Elija una opcion: ");
    _setDictionaryExit("Saliendo...\n");
    _setDictionaryInvalidOption("Opcion invalida, por favor intentalo de nuevo.\n");

    _setMenuOption<FormProductAdd>(FormProductAdd(pim));
    _setMenuOption<FormProductAdd>(FormProductAdd(pim));
  };
};

int main()
{
  PIM *pim = new PIM("pim.db");
  App app(pim);
  app.execute();
  return 0;
}