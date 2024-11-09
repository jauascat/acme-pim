#include "products.h"

products::Add::Add(PIM *pim)
{
  _setPIM(pim);
  _setDictionaryDescription("Crear un producto");
  _setDictionaryPrompt("Ingrese el nombre del producto:");
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
  _pim->addProduct(product);
}