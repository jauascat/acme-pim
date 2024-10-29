#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include <limits>
#include <sqlite3.h>

#include "src/database/database.h"
#include "src/models/product.h"
#include "src/models/category.h"
#include "src/models/pim.h"
#include "src/View/terminal_operation.h"

// class TerminalOperation
// {
// public:
//   virtual void execute() = 0;
//   virtual ~TerminalOperation() {}
//   std::string getDictionaryDescription() const
//   {
//     return _dictionaryDescription;
//   }
// private:

// protected:
//   PIM *_pim;
//   std::string _dictionaryDescription;
//   std::string _dictionaryTitle;
//   std::string _dictionaryPrompt;

//   template <typename... Args>
//   void _print(Args &&...args)
//   {
//     ((std::cout << std::forward<Args>(args)), ...);
//   }

//   template <typename T>
//   T _getUserInput(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate)
//   {
//     T value;
//     while (true)
//     {
//       try
//       {
//         _print(prompt);
//         std::cin >> value;

//         if (std::cin.fail())
//         {
//           throw std::invalid_argument("read input error");
//         }

//         auto [isValid, validationMsg] = validate(value);
//         if (!isValid)
//         {
//           throw std::invalid_argument(validationMsg);
//         }

//         break;
//       }
//       catch (const std::exception &e)
//       {
//         _print(e.what(), "\n");
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//       }
//     }
//     return value;
//   }

//   void _setPIM(PIM *pim)
//   {
//     _pim = pim;
//   }


//   PIM* _getPIM()
//   {
//     return _pim;
//   }

//   void _setDictionaryDescription(const std::string &description)
//   {
//     _dictionaryDescription = description;
//   }

//   void _setDictionaryTitle(const std::string &title)
//   {
//     _dictionaryTitle = title;
//   }

//   void _setDictionaryPrompt(const std::string &prompt)
//   {
//     _dictionaryPrompt = prompt;
//   }

//   std::string _getDictionaryTitle() const
//   {
//     return _dictionaryTitle;
//   }

//   std::string _getDictionaryPrompt() const
//   {
//     return _dictionaryPrompt;
//   }
// };

class TerminalMenu : public TerminalOperation
{
private:
  std::vector<std::unique_ptr<TerminalOperation>> _menuOptions;
  std::string _dictionaryInvalidOption;
  std::string _dictionaryExit;

protected:
  void _setDictionaryInvalidOption(const std::string &invalidOptionMessage)
  {
    _dictionaryInvalidOption = invalidOptionMessage;
  }

  void _setDictionaryExit(const std::string &exitMessage)
  {
    _dictionaryExit = exitMessage;
  }

  std::string _getDictionaryInvalidOption() const
  {
    return _dictionaryInvalidOption;
  }

  std::string _getDictionaryExit() const
  {
    return _dictionaryExit;
  }

  int _getOptionsQuantity() const
  {
    return static_cast<int>(_menuOptions.size());
  }

  template <typename T>
  void _setMenuOption(T &&operation)
  {
    _menuOptions.push_back(std::make_unique<T>(operation));
  }

  void _showMenuOptions()
  {
    int optionsQuantity = _getOptionsQuantity();
    _print("\n===== ", _dictionaryTitle, " =====\n");
    for (size_t i = 0; i < optionsQuantity; ++i)
    {
      _print(i + 1, ". ", _menuOptions[i]->_dictionaryDescription, "\n");
    }
    _print(optionsQuantity + 1, ". Exit\n");
  }

  int _getUserInputOption()
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

public:
  void execute()
  {
    while (true)
    {
      _showMenuOptions();
      int selectedOption = _getUserInputOption();

      if (selectedOption == selectedOption + 1)
      {
        _print(_getDictionaryExit());
        break;
      }
      _menuOptions[selectedOption - 1]->execute();
    }
  }
};

class FormProductAdd final : TerminalOperation
{
public:
  FormProductAdd(PIM* pim)
  {
    _setPIM(pim);
    _setDictionaryDescription("Crear un producto");
    _setDictionaryPrompt("Ingrese el nombre del producto:");
  }
  void execute() override
  {
    auto name = _getNewProductName();
    auto description = _getNewProductDescription();
    auto price = _getNewProductPrice();
    const ProductNew product(name, description, price);
    _pim->addProduct(product);
  }

private:
  std::string _getNewProductName()
  {
    return _getUserInput<std::string>(
        "Ingrese el nombre del producto: ",
        [](const std::string &value)
        {
          bool isValid = !value.empty();
          if (!isValid)
          {
            return std::make_pair(isValid, "El nombre del producto no puede estar vacio.");
          }
          return std::make_pair(isValid, "");
        });
  }
  std::string _getNewProductDescription()
  {
    return _getUserInput<std::string>(
        "Ingrese la descripcion del producto: ",
        [](const std::string &value)
        {
          bool isValid = !value.empty();
          if (!isValid)
          {
            return std::make_pair(isValid, "La descripcion del producto no puede estar vacia.");
          }
          return std::make_pair(isValid, "");
        });
  }
  double _getNewProductPrice()
  {
    return _getUserInput<double>(
        "Ingrese el precio del producto: ",
        [](const double &value)
        {
          bool isValid = value > 0;
          if (!isValid)
          {
            return std::make_pair(isValid, "El precio del producto debe ser mayor a cero.");
          }
          return std::make_pair(isValid, "");
        });
  }
};

class App final : public TerminalMenu
{
public:
  App(PIM* pim)
  {
    _setPIM(pim);
    _setDictionaryTitle("Proyecto!");
    _setDictionaryPrompt("Elija una opcion: ");
    _setDictionaryExit("Saliendo...\n");
    _setDictionaryInvalidOption("Opcion invalida, por favor intentalo de nuevo.\n");
    _setMenuOption<FormProductAdd>(FormProductAdd(pim));
  };
};

int main()
{
  PIM *pim = new PIM("pim.db");
  App app(pim);
  app.execute();
  return 0;
}