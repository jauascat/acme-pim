#include "terminal_implementations.h"

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

TerminalApp getSubmenuBusqueda()
{
  auto buscarNombre = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Buscar por Nombre: "},
      {"description", "Busqueda por nombre"},
      {"result", "Buscando nombre...\n"},
      {"error", "Error al buscar.\n"}
    })
    .onInput([](int nombre, const auto &dict) {
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
    .withOperation<UnaryOperation<int>>(buscarNombre)
    .withOperation<UnaryOperation<int>>(buscarCategoria)
    .withOperation<UnaryOperation<int>>(buscarAtributos)
    .withOperation<UnaryOperation<int>>(buscarRangoPrecios)
    .build();

  return submenuBusqueda;
}