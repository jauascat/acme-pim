//
// Created by rolor on 19/10/2024.
//

#include "Categorias.h"

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
