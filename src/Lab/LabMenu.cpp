#include "LabMenu.h"

TerminalApp getMenuGestionTurnos(Queue queue) {
    // Operación para insertar un turno
    auto insertarTurno = UnaryOperation<string>()
        .withDictionary({
            {"prompt", "Ingrese el turno alfanumerico (ej. A001): "},
            {"description", "Insertar un nuevo turno"},
            {"result", "Turno insertado con exito!\n"},
            {"error", "Error al insertar el turno.\n"}
        })
        .onInput([&queue](std::string turno, const auto &dict) {
            if (!queue.esVaciaCola()) {
                queue.insertarElem(turno);
            } else {
                queue.insertarElem(turno);  // Inserta el turno en la cola
                _print(dict.at("result"));
            }
        });

    // Operación para atender a un cliente
    auto atenderTurno = UnaryOperation<string>()
        .withDictionary({
            {"description", "Atender al proximo cliente en la cola"},
            {"result", "Cliente atendido!\n"},
            {"error", "No hay clientes en espera.\n"}
        })
        .onInput([&queue](std::string value,  auto &dict) {
            if (!queue.esVaciaCola()) {
                string turno;
                queue.atender(turno);
                _print("Turno atendido: ", turno, "\n", dict.at("result"));
            } else {
                _print(dict.at("error"));
            }
        });

    // Operación para listar los turnos
    auto listarTurnos = UnaryOperation<string>()
        .withDictionary({
            {"description", "Listar todos los turnos en la cola"},
            {"result", "Turnos en cola:\n"},
            {"error", "No hay turnos en la cola.\n"}
        })
        .onInput([&queue](std::string value, auto &dict) {
            if (!queue.esVaciaCola()) {
                queue.listarTurnos();
                _print(dict.at("result"));
            } else {
                _print(dict.at("error"));
            }
        });

    // Operación para eliminar un turno por su posición
    auto eliminarTurno = UnaryOperation<int>()
        .withDictionary({
            {"prompt", "Ingrese la posición del turno a eliminar: "},
            {"description", "Eliminar un turno por posicion"},
            {"result", "Turno eliminado con exito!\n"},
            {"error", "Error al eliminar el turno. Verifique la posicion.\n"}
        })
        .onInput([&queue](int posicion, const auto &dict) {
            if (posicion >= 0 && posicion < queue.getLongitud()) {
                queue.eliminarElem(posicion);
                _print(dict.at("result"));
            } else {
                _print(dict.at("error"));
            }
        });

    // Definicion del menú principal
    auto menuGestionTurnos = TerminalApp::Builder()
    .withDictionary({
          {"title", "Proyecto!"},
          {"description", "Submenu Laboratorio"},
          {"prompt", "Elija una opcion: "},
          {"exit", "Saliendo...\n"},
          {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    .withOperation<UnaryOperation<std::string>>(insertarTurno)
    .withOperation<UnaryOperation<std::string>>(atenderTurno)
    .withOperation<UnaryOperation<std::string>>(listarTurnos)
    .withOperation<UnaryOperation<int>>(eliminarTurno)
    .build();

    return menuGestionTurnos;
}
