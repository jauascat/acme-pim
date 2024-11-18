#pragma once

#include <string>

class Category
{
public:
  int id;
  std::string name;
  std::string description;

  Category(int id, const std::string &name, const std::string &description)
    : id(id), name(name), description(description) {}

  int getId() const { return id; }
  std::string getName() const { return name; }
  std::string getDescription() const { return description; }
};