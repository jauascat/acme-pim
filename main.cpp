#include <utility>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "src/logic.h"


template <typename... Args>
void _print(Args &&...args)
{
  ((std::cout << std::forward<Args>(args)), ...);
}
template <typename T>
T _getTerminalInput()
{
  T value;
  std::cin >> value;
  return value;
}


class TerminalOperation
{
public:
  std::unordered_map<std::string, std::string> _dictionary;
  virtual ~TerminalOperation() = default;
  virtual void execute() = 0;
  std::string getDescription() const {
    return _dictionary.at("description");
  }
};



template <typename Child, typename... InputTypes>
class TerminalOp : public TerminalOperation
{
public:
  using Operate = std::function<void(InputTypes..., const std::unordered_map<std::string, std::string> &)>;
  Operate _operate;
  TerminalOp() = default;

  Child &withDictionary(const std::unordered_map<std::string, std::string> &newDictionary)
  {
    _dictionary = newDictionary;
    return static_cast<Child &>(*this);
  }

  Child& onInput(Operate callback)
  {
    _operate = callback;
    return static_cast<Child &>(*this);
  }
  void executeSafetly(std::function<void()> onPrompt)
  {
    try
    {
      _print(this->_dictionary.at("prompt"));
      onPrompt();
    }
    catch (const std::exception &e)
    {
      _print("Error at", this->_dictionary.at("error"), ":\n", e.what(), "\n");
    }
  }
};



template <typename T>
class UnaryOperation final : public TerminalOp<UnaryOperation<T>, T>
{
public:
  void execute() override
  {
    this->executeSafetly([&]() {
      T value1 = _getTerminalInput<T>();
      this->_operate(value1, this->_dictionary);
    });
  }
};




template <typename T, typename U>
class BinaryOperation final : public TerminalOp<BinaryOperation<T, U>, T, U>
{
public:
  void execute() override
  {
    this->executeSafetly([&]() {
      T value1 = _getTerminalInput<T>();
      U value2 = _getTerminalInput<U>();
      this->_operate(value1, value2, this->_dictionary);
    });   
  }
};




class TerminalApp : public TerminalOp<TerminalApp>
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
      const int option = _getTerminalInput<int>();
      if (option == static_cast<int>(_operations.size()) + 1)
      {
        _print(_dictionary.at("exit"));
        break;
      }
      if (option > 0 && static_cast<int>(option) <= _operations.size())
      {
        _operations[option - 1]->execute();
      }
      else
      {
        _print(_dictionary.at("invalid_option"));
      }
    }
  }

  void _showOptions() const
  {
    _print("\n===== ", _dictionary.at("title"), " =====\n");
    for (size_t i = 0; i < _operations.size(); ++i)
    {
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

  template <typename T, typename... Args>
  Builder& withOperation(Args &&...args)
  {
    _app._operations.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return *this;
  }

  TerminalApp build()
  {
    return std::move(_app);
  }
};

TerminalApp getSubmenuProductos()
{
  auto crearProducto = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el nombre del producto: "},
      {"description", "Crear un producto"},
      {"result", "Producto creado con exito!\n"},
      {"error", "Error al crear el producto.\n"}
    })
    .onInput([](int nombre, const auto &dict) {
      // Productos::crearProducto(nombre);
      _print(dict.at("result"));
    });

    auto modificarProducto = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id del producto: "},
      {"description", "Modificar un producto"},
      {"result", "Producto modificado con exito!\n"},
      {"error", "Error al modificar el producto.\n"}
    })
    .onInput([](int id, const auto &dict) {
      // Productos::modificarProducto(id, precio);
      _print(dict.at("result"));
    });

    auto eliminarProducto = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id del producto: "},
      {"description", "Eliminar un producto"},
      {"result", "Producto eliminado con exito!\n"},
      {"error", "Error al eliminar el producto.\n"}
    })
    .onInput([](int id, const auto &dict) {
      // Productos::eliminarProducto(id);
      _print(dict.at("result"));
    });

    auto listarProductos = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id del producto: "},
      {"description", "Listar todos los productos"},
      {"result", "Productos:\n"},
      {"error", "Error al listar los productos.\n"}
    })
    .onInput([](int id, const auto &dict) {
      // Productos::listarProductos();
      _print(dict.at("result"));
    });

  auto menuProductos = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Productos"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<int>>(crearProducto)
    .withOperation<UnaryOperation<int>>(modificarProducto)
    .withOperation<UnaryOperation<int>>(eliminarProducto)
    .withOperation<UnaryOperation<int>>(listarProductos)
    .build();

  return menuProductos;
}

TerminalApp getSubmenuCategorias()
{
  auto crearCategoria = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el nombre de la categoria: "},
      {"description", "Crear una categoria"},
      {"result", "Categoria creada con exito!\n"},
      {"error", "Error al crear la categoria.\n"}
    })
    .onInput([](int nombre, const auto &dict) {
      // Categorias::crearCategoria(nombre);
      _print(dict.at("result"));
    });

    auto modificarCategoria = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id de la categoria: "},
      {"description", "Modificar una categoria"},
      {"result", "Categoria modificada con exito!\n"},
      {"error", "Error al modificar la categoria.\n"}
    })
    .onInput([](int id, const auto &dict) {
      // Categorias::modificarCategoria(id);
      _print(dict.at("result"));
    });

    auto eliminarCategoria = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id de la categoria: "},
      {"description", "Eliminar una categoria"},
      {"result", "Categoria eliminada con exito!\n"},
      {"error", "Error al eliminar la categoria.\n"}
    })
    .onInput([](int id, const auto &dict) {
      // Categorias::eliminarCategoria(id);
      _print(dict.at("result"));
    });

    auto visualizarCategoria = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id de la categoria: "},
      {"description", "Visualizar una categoria"},
      {"result", "Categoria visualizada con exito!\n"},
      {"error", "Error al visualizar la categoria.\n"}
    })
    .onInput([](int id, const auto &dict) {
      // Categorias::visualizarCategoria(id);
      _print(dict.at("result"));
    });

    auto submenuCategorias = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Categorias"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<int>>(crearCategoria)
    .withOperation<UnaryOperation<int>>(modificarCategoria)
    .withOperation<UnaryOperation<int>>(eliminarCategoria)
    .withOperation<UnaryOperation<int>>(visualizarCategoria)
    .build();

  return submenuCategorias;
}



TerminalApp GetAppInstance()
{
  auto app = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<TerminalApp>(getSubmenuProductos())
    .withOperation<TerminalApp>(getSubmenuCategorias())
    .build();


  return app;
}

int main()
{
  auto app = GetAppInstance();
  app.execute();
  return 0;
}


