#pragma once

#include <string>

class Category {
public:
    int id;
    std::string name;
    std::string description;

    Category(int id, const std::string& name, const std::string& description);
};