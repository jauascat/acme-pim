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
  _setMenuOption<products::GetAll>(products::GetAll(pim));
  _setMenuOption<products::GetByName>(products::GetByName(pim));
  _setMenuOption<products::GetById>(products::GetById(pim));
  _setMenuOption<products::GetByCategory>(products::GetByCategory(pim));
  _setMenuOption<products::GetByPriceRange>(products::GetByPriceRange(pim));
  _setMenuOption<products::Create>(products::Create(pim));
  _setMenuOption<products::Update>(products::Update(pim));
}

products::GetAll::GetAll(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Listar todos los productos");
}

void products::GetAll::execute()
{
    auto productsList = _pim->productGetAll();

    if (productsList.empty()) {
        std::cout << "No hay productos para mostrar.\n";
        return;
    }

    std::cout << "Lista de productos:\n";
    for (const auto& product : productsList) {
        auto productCategory = _pim->categoryGetByProductId(int(product.getId()));

        std::cout << "Id: " << product.getId() << "\n"
                  << "Nombre: " << product.getName() << "\n"
                  << "Descripcion: " << product.getDescription() << "\n"
                  << "Precio: $" << product.getPrice() << "\n";

        if (productCategory) {
            std::cout << "Categoria: " << productCategory->getName() << "\n\n";
        } else {
            std::cout << "Categoria: No tiene categoria asignada\n\n";
        }
    }
}

products::GetByName::GetByName(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Buscar por nombre");
}

void products::GetByName::execute()
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

    auto productOpt = _pim->productGetByName(name);

    if (productOpt) {
        const Product& product = productOpt.value();
        auto productCategory = _pim->categoryGetByProductId(int(product.getId()));

        std::cout << "Id: " << product.getId() << "\n"
                  << "Nombre: " << product.getName() << "\n"
                  << "Descripcion: " << product.getDescription() << "\n"
                  << "Precio: $" << product.getPrice() << "\n";

        if (productCategory) {
            std::cout << "Categoria: " << productCategory->getName() << "\n\n";
        } else {
            std::cout << "Categoria: No tiene categoria asignada\n\n";
        }
    } else {
        std::cout << "No se encontró el producto.\n";
    }
}

products::GetById::GetById(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Buscar por id (SKU)");
}

void products::GetById::execute()
{
    auto productIdInput = _GetUserInput<int, int>()
      .withPrompt("Ingrese el id (SKU) del producto: ")
      .withExceptionHandler([](const std::exception &e) {
          std::cout << "Error: " << e.what() << "\nPor favor, ingrese un numero válido.\n";
      })
      .withParseFailureMessage("El id debe ser un número válido.")
      .withParseFailureHandler([]() {
          std::cout << "Por favor ingrese un número (ejemplo: 1)\n";
      })
      .withExitHandler([]() {
          std::cout << "Operación cancelada.\n";
      })
      .withMapper([&](const int &input) { return input; })
      .execute();

    if (!productIdInput)
    {
        return;
    }
    auto productId = productIdInput.value();
    auto productOpt = _pim->productGetById(productId);

    if (productOpt) {
        const Product& product = productOpt.value();
        auto productCategory = _pim->categoryGetByProductId(int(product.getId()));

        std::cout << "Id: " << product.getId() << "\n"
                  << "Nombre: " << product.getName() << "\n"
                  << "Descripcion: " << product.getDescription() << "\n"
                  << "Precio: $" << product.getPrice() << "\n";

        if (productCategory) {
            std::cout << "Categoria: " << productCategory->getName() << "\n\n";
        } else {
            std::cout << "Categoria: No tiene categoria asignada\n\n";
        }
    } else {
        std::cout << "No se encontró el producto.\n";
    }
}

products::GetByCategory::GetByCategory(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Buscar por categoria");
}

void products::GetByCategory::execute()
{
    auto categoryInput = _GetUserInput<std::string, std::string>()
    .withPrompt("Ingrese el nombre de la categoria: ")
    .withValidator([](const std::string &value) { return std::make_pair(!value.empty(), "El nombre del producto no puede estar vacio."); })
    .withExceptionHandler([](const std::exception &e){ std::cout << "Error: " << e.what() << "\nPor favor, intente nuevamente.\n"; })
    .withParseFailureMessage("El formato del nombre no es valido.")
    .withExitHandler([]() { std::cout << "Operacion cancelada.\n"; })
    .withMapper([](const std::string &input) { return input; })
    .execute();

    if (!categoryInput)
    {
        return;
    }
    auto category = categoryInput.value();

    auto productsList = _pim->productGetByCategory(category);

    if (productsList.empty()) {
        std::cout << "No hay productos para mostrar.\n";
        return;
    }

    std::cout << "Lista de productos:\n";
    for (const auto& product : productsList) {
        std::cout << "Id: " << product.getId() << "\n"
                  << "Nombre: " << product.getName() << "\n"
                  << "Descripcion: " << product.getDescription() << "\n"
                  << "Precio: $" << product.getPrice() << "\n"
                  << "Categoria: " << category << "\n\n";;
    }
}

products::GetByPriceRange::GetByPriceRange(PIM *pim)
{
    _setPIM(pim);
    _setDictionaryDescription("Buscar por rango de precio");
}

void products::GetByPriceRange::execute()
{
    auto priceFirstInput = _GetUserInput<double, double>()
      .withPrompt("Ingrese el precio mas bajo para el producto: ")
      .withExceptionHandler([](const std::exception &e) {
          std::cout << "Error: " << e.what() << "\nPor favor, ingrese un numero válido.\n";
      })
      .withParseFailureMessage("El precio debe ser un número válido.")
      .withParseFailureHandler([]() {
          std::cout << "Por favor ingrese un número (ejemplo: 1.0 o 1)\n";
      })
      .withExitHandler([]() {
          std::cout << "Operación cancelada.\n";
      })
      .withMapper([&](const double &input) { return input; })
      .execute();

    auto priceSecondInput = _GetUserInput<double, double>()
      .withPrompt("Ingrese el precio mas bajo para el producto: ")
      .withExceptionHandler([](const std::exception &e) {
          std::cout << "Error: " << e.what() << "\nPor favor, ingrese un numero válido.\n";
      })
      .withParseFailureMessage("El precio debe ser un número válido.")
      .withParseFailureHandler([]() {
          std::cout << "Por favor ingrese un número (ejemplo: 1.0 o 1)\n";
      })
      .withExitHandler([]() {
          std::cout << "Operación cancelada.\n";
      })
      .withMapper([&](const double &input) { return input; })
      .execute();

    auto productsList = _pim->productGetByPriceRange(priceFirstInput.value(), priceSecondInput.value());

    if (productsList.empty()) {
        std::cout << "No hay productos para mostrar.\n";
        return;
    }

    std::cout << "Lista de productos:\n";
    for (const auto& product : productsList) {
        auto productCategory = _pim->categoryGetByProductId(int(product.getId()));

        std::cout << "Id: " << product.getId() << "\n"
                  << "Nombre: " << product.getName() << "\n"
                  << "Descripcion: " << product.getDescription() << "\n"
                  << "Precio: $" << product.getPrice() << "\n";

        if (productCategory) {
            std::cout << "Categoria: " << productCategory->getName() << "\n\n";
        } else {
            std::cout << "Categoria: No tiene categoria asignada\n\n";
        }
    }
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

  //Mostrar categorias disponibles al usuario
  auto categoriesList = _pim->categoryGetAll();

  if(categoriesList.empty()) {
      std::cout << "No hay categorias\n";
      return;
  }

  std::cout << "Seleccione una categoria para el producto:\n";
  int counter = 1;
  for (const auto &category : categoriesList) {
      std::cout << counter++ << ". " << category.getName() << "\n";
  }

  auto categoryInput = _GetUserInput<int, int>()
      .withPrompt("Seleccione una categoria para el producto: ")
      .withValidator([&](const int &value) {
          return std::make_pair(value > 0 && value <= categoriesList.size(), "Seleccione una categoria válida.");
      })
      .withExceptionHandler([](const std::exception &e) {
          std::cout << "Error: " << e.what() << "\nPor favor, ingrese un numero válido.\n";
      })
      .withParseFailureMessage("El id debe ser un número válido.")
      .withParseFailureHandler([]() {
          std::cout << "Por favor ingrese un número (ejemplo: 1)\n";
      })
      .withExitHandler([]() {
          std::cout << "Operación cancelada.\n";
      })
      .withMapper([&](const int &input) { return input; })
      .execute();

  if (!categoryInput)
  {
      std::cout << "Operación cancelada.\n";
      return;
  }

  int selectedCategoryIndex = categoryInput.value() - 1;
  const Category& selectedCategory = categoriesList[selectedCategoryIndex];

  const ProductNew product(name, description, price);
  _pim->productCreate(product, selectedCategory.getId());
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
