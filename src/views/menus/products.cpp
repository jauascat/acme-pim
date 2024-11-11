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
  _setDictionaryDescription("Submenu Productos");
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
    .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "El nombre del producto no puede estar vacío."); })
    .withExceptionHandler([](const std::exception &e){ std::cout << "Error: " << e.what() << "\nPor favor, intente nuevamente.\n"; })
    .withParseFailureMessage("El formato del nombre no es válido.")
    .withExitHandler([]() { std::cout << "Operación cancelada.\n"; })
    .execute();

  if (!nameInput)
  {
    return;
  }
  auto name = nameInput.value();

  auto descriptionInput = _GetUserInput<std::string, std::string>()
    .withPrompt("Ingrese la descripcion del producto: ")
    .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "La descripción del producto no puede estar vacía."); })
    .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\nPor favor, intente nuevamente.\n"; })
    .withParseFailureMessage("El formato de la descripción no es válido.")
    .withExitHandler([]() { std::cout << "Operación cancelada.\n"; })
    .execute();

  if (!descriptionInput)
  {
    return;
  }
  auto description = descriptionInput.value();

  auto priceInput = _GetUserInput<double, double>()
    .withPrompt("Ingrese el precio del producto: ")
    .withValidator([](const double &value) { return std::make_pair(value > 0, "El precio debe ser mayor que cero."); })
    .withExceptionHandler([](const std::exception &e) { std::cout << "Error: " << e.what() << "\nPor favor, ingrese un número válido.\n"; })
    .withParseFailureMessage("El precio debe ser un número válido.")
    .withParseFailureHandler([]() { std::cout << "Por favor ingrese un número (ejemplo: 99.99)\n"; })
    .withExitHandler([]() { std::cout << "Operación cancelada.\n"; })
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
    .withPrompt("Ingrese el nombre del producto para editar")
    .withValidator([this](const std::string& value) {
      auto product = _pim->productGetByName(value);
      if (!product) {
        return std::make_pair(false, "El producto no existe en el sistema.");
      }
      return std::make_pair(true, "");
    })
    .withMapper([this](const std::string& value) -> Product {
      auto product = _pim->productGetByName(value);
      if (!product) {
        throw std::runtime_error("El producto no existe en el sistema.");
      }
      return product.value();
    })
    .withExceptionHandler([](const std::exception& e) { std::cout << "Error al procesar el nombre del producto: " << e.what() << "\n"; })
    .execute();

  if (!productResult) { 
    _print("Operación de actualización cancelada.\n");
    return;
  }

  const Product currentProduct = productResult.value();
  _print("\nProducto encontrado:\n  Nombre: ", currentProduct.name, "\n  Descripción: ", currentProduct.description, "\n  Precio: $", currentProduct.price, "\n\n");

  auto newDescription = _GetUserInput<std::string, std::string>()
    .withPrompt("Nueva descripción")
    .withExitClause("")
    .withValidator([](const std::string& value) { 
      return std::make_pair(!value.empty(), "La descripción no puede estar vacía.");
    })
    .withExitHandler([]() { std::cout << "Se mantendrá la descripción actual.\n"; })
    .execute();

  auto newPrice = _GetUserInput<double, double>()
    .withPrompt("Nuevo precio")
    .withValidator([](const double& value) { 
      return std::make_pair(value > 0, "El precio debe ser mayor que cero.");
    })
    .withParseFailureHandler([]() { std::cout << "Por favor ingrese un número válido (ejemplo: 99.99)\n"; })
    .withExitHandler([]() { std::cout << "Se mantendrá el precio actual.\n"; })
    .execute();

  const Product updatedProduct(
    currentProduct.id,
    currentProduct.name,
    newDescription.has_value() ? newDescription.value() : currentProduct.description,
    newPrice.has_value() ? newPrice.value() : currentProduct.price
  );

  if (updatedProduct.description != currentProduct.description || updatedProduct.price != currentProduct.price) {
      _pim->productUpdate(updatedProduct);
      _print("\nProducto actualizado exitosamente.\n  Descripción: ", updatedProduct.description, "\n  Precio: $", updatedProduct.price, "\n");
  } else {
      _print("\nNo se realizaron cambios al producto.\n");
  }
}