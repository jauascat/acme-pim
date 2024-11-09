#include "Atributos.h"

TerminalApp getSubmenuAtributos()
{
  auto crearAtributo = UnaryOperation<std::string>()
    .withDictionary({
      {"prompt", "Ingrese el nombre del atributo: "},
      {"description", "Crear un atributo"},
      {"result", "Atributo creado con exito!\n"},
      {"error", "Error al crear el atributo.\n"}
    })
    .onInput([](std::string nombre, const auto &dict) {
      _print(dict.at("result"));
    });

    auto modificarAtributo = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id del atributo: "},
      {"description", "Modificar un atributo"},
      {"result", "atributo modificado con exito!\n"},
      {"error", "Error al modificar el atributo.\n"}
    })
    .onInput([](int id, const auto &dict) {
      _print(dict.at("result"));
    });

    auto eliminarAtributo = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id del atributo: "},
      {"description", "Eliminar un atributo"},
      {"result", "atributo eliminado con exito!\n"},
      {"error", "Error al eliminar el atributo.\n"}
    })
    .onInput([](int id, const auto &dict) {
      _print(dict.at("result"));
    });

    auto listarAtributos = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Ingrese el id del atributo: "},
      {"description", "Listar todos los atributo"},
      {"result", "atributo:\n"},
      {"error", "Error al listar los atributo.\n"}
    })
    .onInput([](int id, const auto &dict) {
      _print(dict.at("result"));
    });

  auto menuAtributos = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Productos"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<std::string>>(crearAtributo)
    .withOperation<UnaryOperation<int>>(modificarAtributo)
    .withOperation<UnaryOperation<int>>(eliminarAtributo)
    .withOperation<UnaryOperation<int>>(listarAtributos)
    .build();

  return menuAtributos;
}
