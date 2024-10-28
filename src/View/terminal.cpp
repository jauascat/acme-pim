#include "terminal.h"
#include <limits>

void TerminalMenu::execute() {
    while (true) {
        _showOptions();

        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        int option;
        if (!(ss >> option) || !(ss.eof())) {
            _print(_dictionary.at("invalid_option"));
            continue;
        }

        if (option == static_cast<int>(_menuOptions.size()) + 1) {
            _print(_dictionary.at("exit"));
            break;
        }

        if (option > 0 && static_cast<int>(option) <= _menuOptions.size()) {
            _menuOptions[option - 1]->execute();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            _print(_dictionary.at("invalid_option"));
        }
    }
}

void TerminalMenu::_showOptions() const {
    _print("\n===== ", _dictionary.at("title"), " =====\n");
    for (size_t i = 0; i < _menuOptions.size(); ++i) {
        _print(i + 1, ". ", _menuOptions[i]->getDescription(), "\n");
    }
    _print(_menuOptions.size() + 1, ". Exit\n");
    _print(_dictionary.at("prompt"));
}
