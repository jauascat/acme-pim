#include "menu.h"

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

int Menu::_getUserInputOption()
{
  return _getUserInput<int>(
    _dictionaryPrompt,
    [this](const int &inputOption) -> std::pair<bool, std::string>
    {
      if (inputOption < 1 || inputOption > _getOptionsQuantity() + 1)
      {
        return std::make_pair(false, _getDictionaryInvalidOption());
      }
      return std::make_pair(true, std::string());
    }
  );
}

void Menu::execute()
{
  while (true)
  {
    _showMenuOptions();
    int selectedOption = _getUserInputOption();

    if (selectedOption == _getOptionsQuantity() + 1)
    {
      _print(_getDictionaryExit());
      break;
    }
    _menuOptions[selectedOption - 1]->execute();
  }
}