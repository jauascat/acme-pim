#include "variants.h"


variants::Submenu::Submenu(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Gestionar Variantes");
    _setMenuOption<Create>(Create(pim));
    _setMenuOption<Update>(Update(pim));
    _setMenuOption<Delete>(Delete(pim));
}

variants::Create::Create(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Agregar una variante");
}

void variants::Create::execute()
{
    auto productNameInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el nombre del producto para agregar variantes:")
            .withValidator([this](const std::string &value){ return std::make_pair(_pim->productGetByName(value).has_value(), "El producto no existe."); })
            .withExceptionHandler([](const std::exception &e){ std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del nombre del producto no es valido.")
            .withExitHandler([](){ std::cout << "Operacion cancelada.\n"; })
            .withMapper([](const std::string &input){ return input; })
            .execute();

    if (!productNameInput)
    {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    auto product = _pim->productGetByName(productNameInput.value());
    int productId = product->id;

    auto keyInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el nombre del atributo: ")
            .withValidator([](const std::string &value){ return std::make_pair(!value.empty(), "El atributo no puede estar vacio."); })
            .withExceptionHandler([](const std::exception &e){ std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El nombre del atributo no es valido.")
            .withMapper([](const std::string &input){ return input; })
            .execute();

    if (!keyInput)
    {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    auto valueInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el valor para '" + keyInput.value() + "':")
            .withValidator([](const std::string &value){ return std::make_pair(!value.empty(), "El valor no puede estar vacio."); })
            .withExceptionHandler([](const std::exception &e){ std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del valor no es valido.")
            .withMapper([](const std::string &input){ return input; })
            .execute();

    if (!valueInput)
    {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    std::map<std::string, std::string> attributes;
    attributes[keyInput.value()] = valueInput.value();

    Variant newVariant(0, productId, attributes);

    if (_pim->addVariant(newVariant))
    {
        std::cout << "Variante agregada exitosamente.\n";
    }
    else
    {
        std::cout << "Error al agregar la variante.\n";
    }
}

variants::Update::Update(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Actualizar una variante");
}

void variants::Update::execute()
{
    auto productNameInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el nombre del producto asociado a la variante:")
            .withValidator([this](const std::string &value)
                { return std::make_pair(_pim->productGetByName(value).has_value(), "El producto no existe."); })
            .withExceptionHandler([](const std::exception &e)
                { std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del nombre del producto no es valido.")
            .withExitHandler([]()
                { std::cout << "Operacion cancelada.\n"; })
            .withMapper([](const std::string &input)
                { return input; })
            .execute();

    if (!productNameInput)
        return;

    auto product = _pim->productGetByName(productNameInput.value());
    int productId = product->id;

    auto variants = _pim->getVariantsByProductId(productId);
    if (variants.empty())
    {
        std::cout << "El producto no tiene variantes asociadas.\n";
        return;
    }

    std::cout << "Variantes disponibles:\n";
    for (const auto &variant : variants)
    {
        std::cout << "ID: " << variant.id << ", Atributos:\n";
        for (const auto &[key, value] : variant.attributes)
        {
            std::cout << "  " << key << ": " << value << "\n";
        }
    }

    auto variantIdInput = _GetUserInput<int, int>()
            .withPrompt("Ingrese el ID de la variante a actualizar:")
            .withValidator([](const int &value)
                { return std::make_pair(value > 0, "El ID debe ser mayor que 0."); })
            .withExceptionHandler([](const std::exception &e)
                { std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del ID no es valido.")
            .withMapper([](const int &input)
                { return input; })
            .execute();

    if (!variantIdInput)
        return;

    auto variant = _pim->getVariantById(variantIdInput.value());
    if (!variant)
    {
        std::cout << "La variante no existe.\n";
        return;
    }

    auto keyInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el nombre del atributo a actualizar:")
            .withValidator([](const std::string &value)
                { return std::make_pair(!value.empty(), "El atributo no puede estar vacio."); })
            .withExceptionHandler([](const std::exception &e)
                { std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El nombre del atributo no es valido.")
            .withMapper([](const std::string &input)
                { return input; })
            .execute();

    if (!keyInput)
        return;

    auto valueInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el nuevo valor para '" + keyInput.value() + "':")
            .withValidator([](const std::string &value)
                { return std::make_pair(!value.empty(), "El valor no puede estar vacio."); })
            .withExceptionHandler([](const std::exception &e)
                { std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del valor no es valido.")
            .withMapper([](const std::string &input)
                { return input; })
            .execute();

    if (valueInput)
    {
        variant->attributes[keyInput.value()] = valueInput.value();
    }

    if (_pim->updateVariant(*variant))
    {
        std::cout << "Variante actualizada exitosamente.\n";
    }
    else
    {
        std::cout << "Error al actualizar la variante.\n";
    }
}

variants::Delete::Delete(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Eliminar una variante");
}

void variants::Delete::execute()
{
    auto productNameInput = _GetUserInput<std::string, std::string>()
            .withPrompt("Ingrese el nombre del producto asociado a las variantes:")
            .withValidator([this](const std::string &value)
                { return std::make_pair(_pim->productGetByName(value).has_value(), "El producto no existe."); })
            .withExceptionHandler([](const std::exception &e)
                { std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del nombre del producto no es valido.")
            .withExitHandler([]()
                { std::cout << "Operacion cancelada.\n"; })
            .withMapper([](const std::string &input)
                { return input; })
            .execute();

    if (!productNameInput)
        return;

    auto product = _pim->productGetByName(productNameInput.value());
    int productId = product->id;

    auto variants = _pim->getVariantsByProductId(productId);
    if (variants.empty())
    {
        std::cout << "El producto no tiene variantes asociadas.\n";
        return;
    }

    std::cout << "Variantes disponibles:\n";
    for (const auto &variant : variants)
    {
        std::cout << "ID: " << variant.id << ", Atributos:\n";
        for (const auto &[key, value] : variant.attributes)
        {
            std::cout << "  " << key << ": " << value << "\n";
        }
    }

    auto variantIdInput = _GetUserInput<int, int>()
            .withPrompt("Ingrese el ID de la variante a eliminar:")
            .withValidator([](const int &value)
                { return std::make_pair(value > 0, "El ID debe ser mayor que 0."); })
            .withExceptionHandler([](const std::exception &e)
                { std::cout << "Error: " << e.what() << "Por favor, intente nuevamente.\n"; })
            .withParseFailureMessage("El formato del ID no es valido.")
            .withMapper([](const int &input)
                { return input; })
            .execute();

    if (!variantIdInput)
        return;

    if (_pim->deleteVariant(variantIdInput.value()))
    {
        std::cout << "Variante eliminada exitosamente.\n";
    }
    else
    {
        std::cout << "Error al eliminar la variante.\n";
    }
}
