#include "menu.h"
#include <optional>

void Menu::_setDictionaryInvalidOption(const std::string &invalidOptionMessage)
{
  _dictionaryInvalidOption = invalidOptionMessage;
}

void Menu::_setDictionaryExit(const std::string &exitMessage)
{
  _dictionaryExit = exitMessage;
}

std::string Menu::_getDictionaryInvalidOption() const
{
  return _dictionaryInvalidOption;
}

std::string Menu::_getDictionaryExit() const
{
  return _dictionaryExit;
}

int Menu::_getOptionsQuantity() const
{
  return static_cast<int>(_menuOptions.size());
}

void Menu::_showMenuOptions()
{
  int optionsQuantity = _getOptionsQuantity();
  _print("\n===== ", _dictionaryTitle, " =====\n");
  for (size_t i = 0; i < optionsQuantity; ++i)
  {
    _print(i + 1, ". ", _menuOptions[i]->getDictionaryDescription(), "\n");
  }
  _print(optionsQuantity + 1, ". Exit\n");
}

void Menu::execute()
{
  while (true)
  {
    _showMenuOptions();
    auto selectedOption = _GetUserInput<int, int>()
      .withPrompt(_dictionaryPrompt)
      .withValidator([this](const int &inputOption) { return std::make_pair(inputOption > 0 && inputOption <= _getOptionsQuantity() + 1, _getDictionaryInvalidOption()); })
      .withExitHandler([]() { std::cout << "Operación cancelada.\n"; })
      .withMapper([](const int &inputOption) { return inputOption; })
      .execute();
    
    if (!selectedOption) {
      break;
    }
    int option = selectedOption.value();

    if (option == _getOptionsQuantity() + 1)
    {
      _print(_getDictionaryExit());
      break;
    }
    _menuOptions[*selectedOption - 1]->execute();
  }
}