#pragma once
#include <string>
#include <map>

class Variant {
public:
    int id;
    int productId;
    std::map<std::string, std::string> attributes;

    Variant(int id, int productId, const std::map<std::string, std::string> &attributes)
        : id(id), productId(productId), attributes(attributes) {}
};
