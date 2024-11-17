#include "products.h"
#include <optional>
#include <variant>
#include <iostream>
#include <string>
#include <any>
#include <tuple>

products::Submenu::Submenu(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Gestionar Productos");
  _setMenuOption<products::Create>(products::Create(pim));
  _setMenuOption<products::Update>(products::Update(pim));
}

products::Create::Create(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Crear producto");
}

void products::Create::execute()
{
  auto nameInput = _GetUserInput<std::string, std::string>()
    .withPrompt("Ingrese el nombre del producto: ")
    .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "El nombre del producto no puede estar vacio."); })
    .withExceptionHandler([](const std::exception &e){ std::cout << "Error: " << e.what() << "\nPor favor, intente nuevamente.\n"; })
    .withParseFailureMessage("El formato del nombre no es valido.")
    .withExitHandler([]() { std::cout << "Operacion cancelada.\n"; })
    .withMapper([](const std::string &input) { return input; })
    .execute();

  if (!nameInput)
  {
    return;
  }
  auto name = nameInput.value();

  auto descriptionInput = _GetUserInput<std::string, std::string>()
    .withPrompt("Ingrese la descripcion del producto: ")
    .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "La descripcion del producto no puede estar vacia."); })
    .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\nPor favor, intente nuevamente.\n"; })
    .withParseFailureMessage("El formato de la descripcion no es valido.")
    .withExitHandler([]() { std::cout << "Operacion cancelada.\n"; })
    .withMapper([](const std::string &input) { return input; })
    .execute();

  if (!descriptionInput)
  {
    return;
  }
  auto description = descriptionInput.value();

  auto priceInput = _GetUserInput<double, double>()
    .withPrompt("Ingrese el precio del producto: ")
    .withValidator([](const double &value) { return std::make_pair(value > 0, "El precio debe ser mayor que cero."); })
    .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\nPor favor, ingrese un numero valido.\n"; })
    .withParseFailureMessage("El precio debe ser un numero valido.")
    .withParseFailureHandler([]() { std::cout << "Por favor ingrese un numero (ejemplo: 99.99)\n"; })
    .withExitHandler([]() { std::cout << "Operacion cancelada.\n"; })
    .withMapper([](const double &input) { return input; })
    .execute();

  if (!priceInput)
  {
    return;
  }
  double price = static_cast<double>(priceInput.value());

  const ProductNew product(name, description, price);
  _pim->productCreate(product);
}

products::Update::Update(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Editar producto");
}

void products::Update::execute()
{
    auto productResult = _GetUserInput<std::string, Product>()
        .withPrompt("Ingrese el nombre del producto para editar: ")
        .withValidator([this](const std::string &value) {
            auto product = _pim->productGetByName(value);
            if (!product) {
                return std::make_pair(false, "El producto no existe en el sistema.");
            }
            return std::make_pair(true, "");
        })
        .withMapper([this](const std::string &value) -> Product {
            auto product = _pim->productGetByName(value);
            if (!product) {
                throw std::runtime_error("El producto no existe en el sistema.");
            }
            return product.value();
        })
        .withExceptionHandler([](const std::exception &e) {
            std::cout << "Error al procesar el nombre del producto: " << e.what() << "\n";
        })
        .execute();

    if (!productResult) {
        _print("Operacion de actualizacion cancelada.\n");
        return;
    }

    const Product currentProduct = productResult.value();
    _print("\nProducto encontrado:\n  Nombre: ", currentProduct.name,
           "\n  Descripcion: ", currentProduct.description,
           "\n  Precio: $", currentProduct.price, "\n\n");

    auto newDescription = _GetUserInput<std::string, std::string>()
        .withPrompt("Nueva descripcion: ")
        .withExitClause("")
        .withValidator([](const std::string &value) {
            return std::make_pair(!value.empty(), "La descripcion no puede estar vacia.");
        })
        .withMapper([](const std::string &value) {
            return value;
        })
        .withExitHandler([]() {
            std::cout << "Se mantendra la descripcion actual.\n";
        })
        .execute();

    auto newPrice = _GetUserInput<double, double>()
        .withPrompt("Nuevo precio: ")
        .withValidator([](const double &value) {
            return std::make_pair(value > 0, "El precio debe ser mayor que cero.");
        })
        .withMapper([](const double &value) {
            return value;
        })
        .withParseFailureHandler([]() {
            std::cout << "Por favor ingrese un numero valido (ejemplo: 99.99)\n";
        })
        .withExitHandler([]() {
            std::cout << "Se mantendra el precio actual.\n";
        })
        .execute();

    const Product updatedProduct(
        currentProduct.id,
        currentProduct.name,
        newDescription.has_value() ? newDescription.value() : currentProduct.description,
        newPrice.has_value() ? newPrice.value() : currentProduct.price);

    if (updatedProduct.description != currentProduct.description || updatedProduct.price != currentProduct.price) {
        _pim->productUpdate(updatedProduct);
        _print("\nProducto actualizado exitosamente.\n  Descripcion: ",
               updatedProduct.description, "\n  Precio: $", updatedProduct.price, "\n");
    } else {
        _print("\nNo se realizaron cambios al producto.\n");
    }
}
