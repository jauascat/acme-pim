#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "../models/pim.h"

class TerminalOperation
{
public:
    virtual void execute() = 0;
    virtual ~TerminalOperation() {}
    std::string _dictionaryDescription;
    std::string getDictionaryDescription();

protected:
    PIM *_pim = nullptr;
    std::string _dictionaryTitle;
    std::string _dictionaryPrompt;

    // template <typename... Args>
    // void _print(Args &&...args);

    // template <typename T>
    // T _getUserInput(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate);

    template <typename... Args>
    void _print(Args &&...args) {
        ((std::cout << std::forward<Args>(args)), ...);
    }
    template <typename T>
    T _getUserInput(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate) {
        T value;
        while (true) {
            try {
                _print(prompt);
                std::cin >> value;

                if (std::cin.fail()) {
                    throw std::invalid_argument("read input error");
                }

                auto [isValid, validationMsg] = validate(value);
                if (!isValid) {
                    throw std::invalid_argument(validationMsg);
                }
                break;
            } catch (const std::exception &e) {
                _print(e.what(), "\n");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return value;
    }

    void _setPIM(PIM *pim);
    PIM* _getPIM();

    void _setDictionaryDescription(const std::string &description);
    void _setDictionaryTitle(const std::string &title);
    void _setDictionaryPrompt(const std::string &prompt);

    std::string _getDictionaryTitle();
    std::string _getDictionaryPrompt();
};