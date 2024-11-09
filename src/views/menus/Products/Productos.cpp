#include "Productos.h"

#include <limits>

TerminalApp getSubmenuProductos()
{
  auto crearProducto = UnaryOperation<std::string>()
    .withDictionary({
      {"prompt", "Ingrese el nombre del producto: "},
      {"description", "Crear un producto"},
      {"result", "Producto creado con exito!\n"},
      {"error", "Error al crear el producto.\n"}
    })
    .onInput([](std::string nombre, const auto &dict) {
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

  auto menuProductos = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"description", "Submenu Productos"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<std::string>>(crearProducto)
    .withOperation<UnaryOperation<int>>(modificarProducto)
    .withOperation<UnaryOperation<int>>(eliminarProducto)
    .withOperation<UnaryOperation<int>>(listarProductos)
    .withOperation<UnaryOperation<int>>(administrarVariantes)
    .build();

  return menuProductos;
}
