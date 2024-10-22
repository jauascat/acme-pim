#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include "./Utils/io.h"
#include "../Lab/LabLogic/Queue.h"

class TerminalOperation {
public:
    std::unordered_map<std::string, std::string> _dictionary;
    virtual ~TerminalOperation() = default;
    virtual void execute() = 0;
    std::string getDescription() const {
        return _dictionary.at("description");
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
    Queue queue;  // Instancia de la cola de turnos
    void execute();
    void _showOptions() const;
    void destruirCola();
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