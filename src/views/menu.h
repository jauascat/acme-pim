#pragma once

#include <vector>
#include <memory>
#include <string>
#include <utility>

#include "operation.h"

class Menu : public Operation
{
private:
    std::vector<std::unique_ptr<Operation>> _menuOptions;
    std::string _dictionaryInvalidOption;
    std::string _dictionaryExit;

protected:
    void _setDictionaryInvalidOption(const std::string &invalidOptionMessage);
    void _setDictionaryExit(const std::string &exitMessage);
    std::string _getDictionaryInvalidOption() const;
    std::string _getDictionaryExit() const;
    int _getOptionsQuantity() const;

    template <typename T>
    void _setMenuOption(T &&operation)
    {
    _menuOptions.push_back(std::make_unique<T>(std::forward<T>(operation)));
    }

    void _showMenuOptions();
    int _getUserInputOption();

public:
    void execute();
};