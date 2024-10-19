#pragma once

#include <string>

class Product {
public:
  int id;
  std::string name;
  std::string description;
  double price;

  Product(int id, const std::string& name, const std::string& description, double price)
    : id(id), name(name), description(description), price(price) {}
};


class Category {
public:
  int id;
  std::string name;
  std::string description;

  Category(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}
};
