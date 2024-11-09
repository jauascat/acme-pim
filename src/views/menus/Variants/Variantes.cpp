#include "Variantes.h"

TerminalApp getSubmenuVariantes()
{
    auto crearVariante = UnaryOperation<int>()
        .withDictionary({
            {"prompt", "Ingrese el ID del producto al que desea agregar una variante: "},
            {"description", "Crear una variante"},
            {"result", "Variante creada con exito!\n"},
            {"error", "Error al crear la variante.\n"}
        })
        .onInput([](int idProducto, const auto &dict) {
            std::string color, talla;
            _print("Ingrese el color de la variante: ");
            std::cin >> color;
            _print("Ingrese la talla de la variante: ");
            std::cin >> talla;
            // Aquí iría la lógica para crear la variante con los atributos dados
            _print(dict.at("result"));
        });

    auto modificarVariante = UnaryOperation<int>()
        .withDictionary({
            {"prompt", "Ingrese el ID de la variante que desea modificar: "},
            {"description", "Modificar una variante"},
            {"result", "Variante modificada con exito!\n"},
            {"error", "Error al modificar la variante.\n"}
        })
        .onInput([](int idVariante, const auto &dict) {
            std::string nuevoColor, nuevaTalla;
            _print("Ingrese el nuevo color de la variante: ");
            std::cin >> nuevoColor;
            _print("Ingrese la nueva talla de la variante: ");
            std::cin >> nuevaTalla;
            // Aquí iría la lógica para modificar la variante con el nuevo color y talla
            _print(dict.at("result"));
        });

    auto eliminarVariante = UnaryOperation<int>()
        .withDictionary({
            {"prompt", "Ingrese el ID de la variante que desea eliminar: "},
            {"description", "Eliminar una variante"},
            {"result", "Variante eliminada con exito!\n"},
            {"error", "Error al eliminar la variante.\n"}
        })
        .onInput([](int idVariante, const auto &dict) {
            // Aquí iría la lógica para eliminar la variante por su ID
            _print(dict.at("result"));
        });

    auto listarVariantes = UnaryOperation<int>()
        .withDictionary({
            {"prompt", "Ingrese el ID del producto para ver sus variantes: "},
            {"description", "Listar todas las variantes de un producto"},
            {"result", "Listando variantes:\n"},
            {"error", "Error al listar las variantes.\n"}
        })
        .onInput([](int idProducto, const auto &dict) {
            // Aquí iría la lógica para obtener y mostrar las variantes del producto por su ID
            _print(dict.at("result"));
            // Por ejemplo, podrías iterar sobre las variantes del producto y mostrarlas
            _print("Variante 1: Color - Rojo, Talla - M\n");
            _print("Variante 2: Color - Azul, Talla - L\n");
        });


    auto menuVariantes = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Variantes"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<int>>(crearVariante)
    .withOperation<UnaryOperation<int>>(modificarVariante)
    .withOperation<UnaryOperation<int>>(eliminarVariante)
    .withOperation<UnaryOperation<int>>(listarVariantes)
    .build();

    return menuVariantes;
}

