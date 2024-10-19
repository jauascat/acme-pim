#pragma once

#include <string>

class Product {
public:
    int id;
    std::string name;
    std::string description;
    double price;

    Product(int id, const std::string& name, const std::string& description, double price);
};