#pragma once

#include <string>

class NewProduct {
public:
    int id;
    std::string name;
    std::string description;
    double price;

    NewProduct(int id, const std::string& name, const std::string& description, double price);
};