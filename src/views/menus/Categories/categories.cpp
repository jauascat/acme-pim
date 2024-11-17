#include "categories.h"
#include <iostream>

categories::Submenu::Submenu(PIM *pim) {
    _setPIM(pim);
    _setDictionaryDescription("Gestionar Categorias");
    _setMenuOption<Create>(Create(pim));
    _setMenuOption<Update>(Update(pim));
    _setMenuOption<Delete>(Delete(pim));
}

categories::Create::Create(PIM *pim) {
    _setPIM(pim);
    _setDictionaryDescription("Agregar una categoria");
}

void categories::Create::execute() {
    auto nameInput = _GetUserInput<std::string, std::string>()
        .withPrompt("Ingrese el nombre de la categoria: ")
        .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "El nombre no puede estar vacio."); })
        .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\n"; })
        .withParseFailureMessage("El nombre no es valido.")
        .withMapper([](const std::string &input) { return input; })
        .execute();

    if (!nameInput) {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    auto descriptionInput = _GetUserInput<std::string, std::string>()
        .withPrompt("Ingrese la descripcion de la categoria: ")
        .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "La descripcion no puede estar vacia."); })
        .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\n"; })
        .withParseFailureMessage("La descripcion no es valida.")
        .withMapper([](const std::string &input) { return input; })
        .execute();

    if (!descriptionInput) {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    Category newCategory(0, nameInput.value(), descriptionInput.value());
    if (_pim->categoryCreate(newCategory)) {
        std::cout << "Categoria creada exitosamente.\n";
    } else {
        std::cout << "Error al crear la categoria.\n";
    }
}

categories::Update::Update(PIM *pim) {
    _setPIM(pim);
    _setDictionaryDescription("Actualizar una categoria");
}

void categories::Update::execute() {
    auto categoryIdInput = _GetUserInput<int, int>()
        .withPrompt("Ingrese el ID de la categoria a actualizar: ")
        .withValidator([](const int &value) { return std::make_pair(value > 0, "El ID debe ser mayor que 0."); })
        .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\n"; })
        .withParseFailureMessage("El ID no es valido.")
        .withMapper([](const int &input) { return input; })
        .execute();

    if (!categoryIdInput) {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    auto category = _pim->categoryGetById(categoryIdInput.value());
    if (!category) {
        std::cout << "Categoria no encontrada.\n";
        return;
    }

    std::cout << "Categoria encontrada:\n"
              << "  Nombre: " << category->name << "\n"
              << "  Descripcion: " << category->description << "\n";

    auto newNameInput = _GetUserInput<std::string, std::string>()
        .withPrompt("Ingrese el nuevo nombre (deje vacio para mantener el actual): ")
        .withExitClause("")
        .withMapper([](const std::string &input) { return input; })
        .execute();

    auto newDescriptionInput = _GetUserInput<std::string, std::string>()
        .withPrompt("Ingrese la nueva descripcion (deje vacio para mantener la actual): ")
        .withExitClause("")
        .withMapper([](const std::string &input) { return input; })
        .execute();

    if (newNameInput.has_value()) category->name = newNameInput.value();
    if (newDescriptionInput.has_value()) category->description = newDescriptionInput.value();

    if (_pim->categoryUpdate(*category)) {
        std::cout << "Categoria actualizada exitosamente.\n";
    } else {
        std::cout << "Error al actualizar la categoria.\n";
    }
}

categories::Delete::Delete(PIM *pim) {
    _setPIM(pim);
    _setDictionaryDescription("Eliminar una categoria");
}

void categories::Delete::execute() {
    auto categoryIdInput = _GetUserInput<int, int>()
        .withPrompt("Ingrese el ID de la categoria a eliminar: ")
        .withValidator([](const int &value) { return std::make_pair(value > 0, "El ID debe ser mayor que 0."); })
        .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\n"; })
        .withParseFailureMessage("El ID no es valido.")
        .withMapper([](const int &input) { return input; })
        .execute();

    if (!categoryIdInput) {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    if (_pim->categoryHasProducts(categoryIdInput.value())) {
        std::cout << "La categoria tiene productos asociados. Eliminando asociaciones...\n";
        _pim->categoryRemoveProducts(categoryIdInput.value());
    }

    if (_pim->categoryDelete(categoryIdInput.value())) {
        std::cout << "Categoria eliminada exitosamente.\n";
    } else {
        std::cout << "Error al eliminar la categoria.\n";
    }
}
