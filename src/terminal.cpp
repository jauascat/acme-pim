#include "terminal.h"

void TerminalApp::execute() {
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

        if (option == static_cast<int>(_operations.size()) + 1) {
            _print(_dictionary.at("exit"));
            break;
        }

        if (option > 0 && static_cast<int>(option) <= _operations.size()) {
            _operations[option - 1]->execute();
        } else {
            _print(_dictionary.at("invalid_option"));
        }
    }
}

void TerminalApp::_showOptions() const {
    _print("\n===== ", _dictionary.at("title"), " =====\n");
    for (size_t i = 0; i < _operations.size(); ++i) {
        _print(i + 1, ". ", _operations[i]->getDescription(), "\n");
    }
    _print(_operations.size() + 1, ". Exit\n");
    _print(_dictionary.at("prompt"));
}
