#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include "io.h"
#include "../models/category.h"
#include "../models/product.h"
#include "../db/db.h"

class TerminalOperation {
public:
    std::unordered_map<std::string, std::string> _dictionary;
    virtual ~TerminalOperation() = default;
    virtual void execute() = 0;
    std::string getDescription() const {
        return _dictionary.at("description");
    }
};

template <typename Child>
class TerminalOperation2 : public TerminalOperation {
public:
    Child& withDictionary(const std::unordered_map<std::string, std::string> &newDictionary) {
        _dictionary = newDictionary;
        return static_cast<Child&>(*this);
    }
};

template <typename Child, typename... InputTypes>
class TerminalOp : public TerminalOperation {
public:
    using Operate = std::function<void(InputTypes..., const std::unordered_map<std::string, std::string>&)>;
    Operate _operate;
    TerminalOp() = default;

    Child& withDictionary(const std::unordered_map<std::string, std::string>& newDictionary) {
        _dictionary = newDictionary;
        return static_cast<Child&>(*this);
    }

    Child& onInput(Operate callback) {
        _operate = callback;
        return static_cast<Child&>(*this);
    }

    void executeSafetly(std::function<void()> onPrompt) {
        try {
            _print(this->_dictionary.at("prompt"));
            onPrompt();
        } catch (const std::exception& e) {
            _print("Error at ", this->_dictionary.at("error"), ": ", e.what(), "\n");
        }
    }
};

class TeOpProductAdd final : public TerminalOperation2<TeOpProductAdd> {
public:
    void execute() override {
        std::string name = _getTerminalInput2<std::string>(
            "Ingrese el nombre del producto: ",
            [](const std::string &value) {
                bool isValid = !value.empty();
                if (!isValid) {
                    return std::make_pair(isValid, "El nombre del producto no puede estar vacio.");
                }
                return std::make_pair(isValid, "");
            }
        );
        std::string description = _getTerminalInput2<std::string>(
            "Ingrese la descripcion del producto: ",
            [](const std::string &value) {
                bool isValid = !value.empty();
                if (!isValid) {
                    return std::make_pair(isValid, "La descripcion del producto no puede estar vacia.");
                }
                return std::make_pair(isValid, "");
            }
        );
        double price = _getTerminalInput2<double>(
            "Ingrese el precio del producto: ",
            [](const double &value) {
                bool isValid = value <= 0;
                if (!isValid) {
                    return std::make_pair(isValid, "El precio del producto debe ser mayor a cero.");
                }
                return std::make_pair(isValid, "");
            }
        );
        // Product product = Product(0, name, description, price);
        //log product
        _print("Producto añadido con exito!\n");
        // _print("Nombre: ", product.name, "\n");
        // _print("Descripcion: ", product.description, "\n");
        // _print("Precio: ", product.price, "\n");
    }
};

template <typename T>
class UnaryOperation final : public TerminalOp<UnaryOperation<T>, T> {
public:
    void execute() override {
        this->executeSafetly([&]() {
            T value1 = _getTerminalInput<T>();
            this->_operate(value1, this->_dictionary);
        });
    }
};

template <typename T, typename U>
class BinaryOperation final : public TerminalOp<BinaryOperation<T, U>, T, U> {
public:
    void execute() override {
        this->executeSafetly([&]() {
            T value1 = _getTerminalInput<T>();
            U value2 = _getTerminalInput<U>();
            this->_operate(value1, value2, this->_dictionary);
        });
    }
};

class TerminalApp : public TerminalOp<TerminalApp> {
private:
    std::vector<std::unique_ptr<TerminalOperation>> _operations;

public:
    class Builder;

    void execute();
    void _showOptions() const;
};


class TerminalApp::Builder {
    TerminalApp _app;

public:
    Builder() : _app() {}

    Builder& withDictionary(const std::unordered_map<std::string, std::string>& dictionary) {
        _app._dictionary = dictionary;
        return *this;
    }

    template <typename T, typename... Args>
    Builder& withOperation(Args&&... args) {
        _app._operations.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *this;
    }

    TerminalApp build() {
        return std::move(_app);
    }
};