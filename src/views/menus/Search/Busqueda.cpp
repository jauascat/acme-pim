#include "Busqueda.h"

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