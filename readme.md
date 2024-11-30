# Acme PIM v0.1 🚀 

Showcasing a variety of OOP-wise design patterns, this repository is an academic exercise demonstrating a simple implementation of a product information management system (PIM).
It presents the C++ 17 code files for a command-line application that manages a database of products and categories. 
The language of the implementation is Spanish.

## Core functionalities:
- **A modular class hierarchy for terminal-based user interfaces** 
- **Database in SQLite**
- **An Abstract Data Type (ADT) class for**
  - *Product Management and Persistence*
    - Create, update, delete, and query products with attributes like name, SKU, description, price, and category.
  - *Category Management and Persistence*
    - Add, modify, delete, and visualize categories.
  - **Custom Attributes and Variants**
    - Flexible definition of product attributes (e.g., color, size) and management of product variants.

## Layers overview
```mermaid
graph TD
    CLI["Command-line Application"]
    ADT["P.I.M. Abstract Data Type"]
    DB["P.I.M. Database"]

    CLI --> ADT
    ADT --> DB
```
## Commnad-line classes
All command line operations are simple classes that extend either `Operation` or `Menu`.
All child classes implement main polymorphic `execute()` function to compose Operations within themselves.
All `execute()` implementations are simply concrete implementations of `_GetUserInput` inner class.
```mermaid
classDiagram
    class Operation {
        execute()
        getDictionaryDescription()
        setPIM(pim)
        getPIM()
        setDictionaryDescription(description)
        setDictionaryTitle(title)
        setDictionaryPrompt(prompt)
        getDictionaryTitle()
        getDictionaryPrompt()
        _print(args)
    }

    class Menu {
        execute()
        _setDictionaryInvalidOption(invalidOptionMessage)
        _setDictionaryExit(exitMessage)
        _getDictionaryInvalidOption()
        _getDictionaryExit()
        _getOptionsQuantity()
        _setMenuOption(operation)
        _showMenuOptions()
        _getUserInputOption()
    }

    class _GetUserInput {
        withPrompt(prompt)
        withParseFailureMessage(message)
        withValidator(validator)
        withExitClause(exitClause)
        withExitHandler(handler)
        withParseFailureHandler(handler)
        withExceptionHandler(handler)
        withMapper(mapper)
        withCastInput(caster)
        execute()
    }


    %% Relationships
    Operation <|-- Menu : inherits
    Menu o-- Operation : contains
    Operation o-- _GetUserInput : contains

```
An example of a concrete implementation of this hierarchy:
```
void products::Update::execute()
{
    auto productResult = _GetUserInput<std::string, Product>()
        .withPrompt("Ingrese el nombre del producto para editar: ")
        .withValidator([this](const std::string &value) {
            auto product = _pim->productGetByName(value);
            if (!product) {
                return std::make_pair(false, "El producto no existe en el sistema.");
            }
            return std::make_pair(true, "");
        })
        .withMapper([this](const std::string &value) -> Product {
            auto product = _pim->productGetByName(value);
            if (!product) {
                throw std::runtime_error("El producto no existe en el sistema.");
            }
            return product.value();
        })
        .withExceptionHandler([](const std::exception &e) {
            std::cout << "Error al procesar el nombre del producto: " << e.what() << "\n";
        })
        .execute();
```
### Command line classes implementation overview:
All command line operations are simple classes that extend either `Operation` or `Menu`.
Each `Operation` implementation calls a different operation upon the P.I.M class.
![UI overview](https://github.com/jauascat/acme-pim/blob/MES_READ/scrap/ui_overview.png)

## Main dependencies:
  - C++ 17
  - CMake v3.29
  - Sqlite3 v3.47.0

## Installation:
1. Clone the repository:
```bash
git clone https://github.com/jauascat/acme-pim.git
```
2. Two options for compilation base on operating system:
  1. Windows:
    - Compile using JetBrains' CLion. 
    - Clion's project files are included in the repository.
    - Sqlite3 is included in the repository, so no need to install it.
    
  2. Linux based:
    - Use Microsoft's Visual Studio Code
    - Be sure to have environment properly installed on your machine:
      - C++ 17 enabled compiler
      - Sqlite3 v3.47.0
      - CMake v3.29
    - Compile using CMake and execute using `launch.json` file.
3. Executable is placed in `./build/acme_pim`
