#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include <limits>

#include "src/store/setup.h"

template <typename... Args>
void _print(Args &&...args)
{
  ((std::cout << std::forward<Args>(args)), ...);
}

class NewProduct {
public:
    std::string name;
    std::string description;
    double price;

    NewProduct(const std::string& name, const std::string& description, double price)
      : name(name), description(description), price(price) {}
};


template <typename T>
T _getTerminalInput2(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate)
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


class TerminalOperation
{
public:
  std::unordered_map<std::string, std::string> _dictionary;
  virtual ~TerminalOperation() = default;
  virtual void execute() = 0;
  std::string getDescription() const
  {
    return _dictionary.at("description");
  }
};


template <typename Child>
class TerminalOperation2 : public TerminalOperation
{
public:
  Child &withDictionary(const std::unordered_map<std::string, std::string> &newDictionary)
  {
    _dictionary = newDictionary;
    return static_cast<Child &>(*this);
  }
};

class TeOpProductAdd final : public TerminalOperation2<TeOpProductAdd>
{
public:
  TeOpProductAdd() {
    this->withDictionary({{"description", "Agregar un producto"}});
  };
  void execute() override
  {
    auto name = _getTerminalInput2<std::string>(
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
    auto description = _getTerminalInput2<std::string>(
        "Ingrese la descripcion del producto: ",
        [](const std::string &value)
        {
          bool isValid = !value.empty();
          if (!isValid)
          {
            return std::make_pair(isValid, "La descripcion del producto no puede estar vacia.");
          }
          return std::make_pair(isValid, "");
        }
      );
    double price = _getTerminalInput2<double>(
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
    NewProduct newProduct(name, description, price);
    _print("Producto añadido con exito!\n");
    _print("Nombre: ", newProduct.name, "\n");
    _print("Descripcion: ", newProduct.description, "\n");
    _print("Precio: ", newProduct.price, "\n");
  }
};

class TerminalApp : public TerminalOperation2<TerminalApp>
{
private:
  std::vector<std::unique_ptr<TerminalOperation>> _operations;

public:
  class Builder;

  void execute()
  {
    while (true)
    {
      _showOptions();

      std::string input;
      std::getline(std::cin, input);

      std::stringstream ss(input);
      int option;
      if (!(ss >> option) || !(ss.eof()))
      {
        _print(_dictionary.at("invalid_option"));
        continue;
      }

      if (option == static_cast<int>(_operations.size()) + 1)
      {
        _print(_dictionary.at("exit"));
        break;
      }

      if (option > 0 && static_cast<int>(option) <= _operations.size())
      {
        _operations[option - 1]->execute();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else
      {
        _print(_dictionary.at("invalid_option"));
      }
    }
  }
  void _showOptions() const {
      _print("\n===== ", _dictionary.at("title"), " =====\n");
      for (size_t i = 0; i < _operations.size(); ++i) {
          _print(i + 1, ". ", _operations[i]->getDescription(), "\n");
      }
      _print(_operations.size() + 1, ". Exit\n");
      _print(_dictionary.at("prompt"));
  }

};

class TerminalApp::Builder
{
  TerminalApp _app;

public:
  Builder() : _app() {}

  Builder& withDictionary(const std::unordered_map<std::string, std::string> &dictionary)
  {
    _app._dictionary = dictionary;
    return *this;
  }

  template <typename T>
  Builder& withOperation(T &operation)
  {
    _app._operations.push_back(std::make_unique<T>(operation));
    return *this;
  }

  TerminalApp build()
  {
    return std::move(_app);
  }
};

int main()
{
  auto addProduct = TeOpProductAdd();
  auto app = TerminalApp::Builder()
                 .withDictionary({{"title", "Proyecto!"},
                                  {"prompt", "Elija una opcion: "},
                                  {"exit", "Saliendo...\n"},
                                  {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}})
                 .withOperation<TeOpProductAdd>(addProduct)
                 .withOperation<TeOpProductAdd>(addProduct)
                 .build();
  app.execute();
  // buildDB();
  return 0;
}