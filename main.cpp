#include <iostream>
#include <vector>
#include "LinkedList.h"

int main() {
    LinkedList list;

    // Insertar algunos elementos
    list.insert(21);
    list.insert(34);
    list.insert(55);
    list.insert(89);
    list.insert(144);
    list.insert(233);
    list.insert(377);
    list.insert(610);
    list.insert(987);
    list.insert(1597);

    // Mostrar la lista
    std::cout << "Recursivamente: después de las inserciones:\n";
    list.display();

    // Eliminar nodos
    auto toEliminate = std::vector<int>{1597, 987, 610, 377, 233, 144};
    for (auto value : toEliminate) {
      list.remove(value);
    }

    // Mostrar la lista después de eliminar
    std::cout << "Iterativamente: después de eliminar nodos con tres digitos:\n";
    list.display_recursive();

    std::cout << "\n\n" << "prueba finalizada! \n\n";
    return 0;
}
