#include "terminal_implementations.h"
#include <limits>
#include <thread>

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
    .withOperation<TerminalApp>(getSubmenuBusqueda())
    .build();

  return app;
}

TerminalApp getSubmenuProductos()
{
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

  // Operación para administrar variantes (crear, eliminar, editar, visualizar)
  auto administrarVariantes = UnaryOperation<int>()
      .withDictionary({
        {"prompt", "Ingrese el ID del producto para administrar sus variantes: "},
        {"description", "Administrar variantes de un producto"},
        {"result", "Mantenimiento de variantes:\n 1. Crear\n 2. Editar\n 3. Eliminar\n 4. Visualizar\n"},
        {"error", "Error al administrar variantes.\n"}
      })
      .onInput([](int productoID, const auto &dict) {
        // Placeholder para futuras funciones de variantes
        _print(dict.at("result"));
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string input;
        std::getline(std::cin, input);
        int option;
        std::stringstream ss(input);
        ss >> option;


        switch (option) {
            case 1: { // Crear
                _print("Ingrese el nombre de la nueva variante: ");
                std::string nombreVariante;
                std::getline(std::cin, nombreVariante);
                // Lógica para crear variante
                _print("Variante \"" + nombreVariante + "\" creada correctamente.\n");
                break;
            }
            case 2: { // Editar
                _print("Ingrese el nuevo nombre de la variante: ");
                std::string nuevoNombreVariante;
                std::getline(std::cin, nuevoNombreVariante);
                // Lógica para editar variante
                _print("Variante actualizada a \"" + nuevoNombreVariante + "\" correctamente.\n");
                break;
            }
            case 3: { // Eliminar
                // Lógica para eliminar variante
                _print("Variante eliminada correctamente.\n");
                break;
            }
            case 4: {
                _print("Visualizando variantes...\n");
                break;
            }
            default:
              _print("Opcion invalida. Intente de nuevo.\n");
              break;
        }
      });

  auto addProduct = TeOpProductAdd()
    .withDictionary({
      {"description", "Crear un producto"}
      // {"result", "Producto creado con exito!\n"},
      // {"error", "Error al crear el producto.\n"}
    });
  auto menuProductos = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Productos"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<TeOpProductAdd>(addProduct)
    .withOperation<UnaryOperation<int>>(modificarProducto)
    .withOperation<UnaryOperation<int>>(eliminarProducto)
    .withOperation<UnaryOperation<int>>(listarProductos)
    .withOperation<UnaryOperation<int>>(administrarVariantes)
    .build();

  return menuProductos;
}

TerminalApp getSubmenuCategorias()
{
  auto crearCategoria = UnaryOperation<std::string>()
    .withDictionary({
      {"prompt", "Ingrese el nombre de la categoria: "},
      {"description", "Crear una categoria"},
      {"result", "Categoria creada con exito!\n"},
      {"error", "Error al crear la categoria.\n"}
    })
    .onInput([](std::string nombre, const auto &dict) {
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
    .withOperation<UnaryOperation<std::string>>(crearCategoria)
    .withOperation<UnaryOperation<int>>(modificarCategoria)
    .withOperation<UnaryOperation<int>>(eliminarCategoria)
    .withOperation<UnaryOperation<int>>(visualizarCategoria)
    .build();

  return submenuCategorias;
}

TerminalApp getSubmenuBusqueda()
{
  auto buscarNombre = UnaryOperation<std::string>()
    .withDictionary({
      {"prompt", "Buscar por Nombre: "},
      {"description", "Busqueda por nombre"},
      {"result", "Buscando nombre...\n"},
      {"error", "Error al buscar.\n"}
    })
    .onInput([](std::string nombre, const auto &dict) {
      _print(dict.at("result"));
    });

    auto buscarCategoria = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Buscar por Categoría: "},
      {"description", "Busqueda por Categoría"},
      {"result", "Buscando categoria...\n"},
      {"error", "Error al buscar.\n"}
    })
    .onInput([](int id, const auto &dict) {
      _print(dict.at("result"));
    });

    auto buscarAtributos = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Buscar por Atributos: "},
      {"description", "Busqueda por Atributos"},
      {"result", "Buscando Atributos...\n"},
      {"error", "Error al buscar.\n"}
    })
    .onInput([](int id, const auto &dict) {
      _print(dict.at("result"));
    });

    auto buscarRangoPrecios = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Buscar por Rango de Precios: "},
      {"description", "Busqueda por Rango de Precios"},
      {"result", "Buscando Rango de Precios...\n"},
      {"error", "Error al buscar.\n"}
    })
    .onInput([](int id, const auto &dict) {
      _print(dict.at("result"));
    });

    auto submenuBusqueda = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Busqueda"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<std::string>>(buscarNombre)
    .withOperation<UnaryOperation<int>>(buscarCategoria)
    .withOperation<UnaryOperation<int>>(buscarAtributos)
    .withOperation<UnaryOperation<int>>(buscarRangoPrecios)
    .build();

  return submenuBusqueda;
}