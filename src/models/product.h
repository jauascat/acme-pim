#pragma once

#include <string>

class Product {
public:
    int id;
    std::string name;
    std::string description;
    double price;

    Product(const int id, const std::string& name, const std::string& description, double price)
      : id(id), name(name), description(description), price(price) {}

    int getId() const {return id; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    double getPrice() const { return price; }
};

class ProductNew : public Product {
public:
    ProductNew(const std::string& name, const std::string& description, double price)
      : Product(0, name, description, price) {}
};

class ProductEdited : public Product {
public:
    ProductEdited()
      : Product(0, std::string(), std::string(), 0) {}
};