#include "products.h"

products::Submenu::Submenu(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Submenu Productos");
  _setMenuOption<products::Add>(products::Add(pim));
  _setMenuOption<products::Update>(products::Update(pim));
}



products::Add::Add(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Crear producto");
}
void products::Add::execute()
{
  auto name = _getUserInput<std::string>(
    "Ingrese el nombre del producto: ",
    [](const std::string &value)
    {
      bool isValid = !value.empty();
      if (!isValid)
      {
        return std::make_pair(isValid, "El nombre del producto no puede estar vacio.");
      }
      return std::make_pair(isValid, "");
    });
    
  auto description = _getUserInput<std::string>(
    "Ingrese la descripcion del producto: ",
    [](const std::string &value)
    {
      bool isValid = !value.empty();
      if (!isValid)
      {
        return std::make_pair(isValid, "La descripcion del producto no puede estar vacia.");
      }
      return std::make_pair(isValid, "");
    });

  auto price = _getUserInput<double>(
    "Ingrese el precio del producto: ",
    [](const double &value)
    {
      bool isValid = value > 0;
      if (!isValid)
      {
        return std::make_pair(isValid, "El precio del producto debe ser mayor a cero.");
      }
      return std::make_pair(isValid, "");
    });

  const ProductNew product(name, description, price);
  _pim->productAdd(product);
}



products::Update::Update(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Editar producto");
}
void products::Update::execute()
{
  auto nameToEdit =_getUserInput<std::string>(
    "Ingrese el nombre del producto para editar: ",
    [this](const std::string &value)
    {
      bool isValid = !value.empty();
      if (!isValid)
      {
        return std::make_pair(isValid, "El nombre del producto a editarno puede estar vacio.");
      }
      auto productToEdit = _pim->productGetByName(value);
      if(!productToEdit)
      {
        return std::make_pair(isValid, "El producto no existe.");
      }
      return std::make_pair(isValid, "");
    });

  auto productToEdit = _pim->productGetByName(nameToEdit);
  _print("Producto a editar: \n");
  _print("Nombre: ", productToEdit->name, "\n");
  _print("Descripcion: ", productToEdit->description, "\n");
  _print("Precio: ", productToEdit->price, "\n");
    
  // auto description = _getUserInput<std::string>(
  //   "Ingrese la descripcion del producto: ",
  //   [](const std::string &value)
  //   {
  //     bool isValid = !value.empty();
  //     if (!isValid)
  //     {
  //       return std::make_pair(isValid, "La descripcion del producto no puede estar vacia.");
  //     }
  //     return std::make_pair(isValid, "");
  //   });

  // auto price = _getUserInput<double>(
  //   "Ingrese el precio del producto: ",
  //   [](const double &value)
  //   {
  //     bool isValid = value > 0;
  //     if (!isValid)
  //     {
  //       return std::make_pair(isValid, "El precio del producto debe ser mayor a cero.");
  //     }
  //     return std::make_pair(isValid, "");
  //   });

  // const ProductNew product(name, description, price);
}