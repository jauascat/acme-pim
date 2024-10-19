#include "product.h"

Product::Product(int id, const std::string& name, const std::string& description, double price)
  : id(id), name(name), description(description), price(price) {}
