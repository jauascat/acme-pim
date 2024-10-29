#include "terminal_operation.h"

std::string TerminalOperation::getDictionaryDescription() {
    return _dictionaryDescription;
}

void TerminalOperation::_setPIM(PIM *pim) {
    _pim = pim;
}

PIM* TerminalOperation::_getPIM() {
    return _pim;
}

void TerminalOperation::_setDictionaryDescription(const std::string &description) {
    _dictionaryDescription = description;
}

void TerminalOperation::_setDictionaryTitle(const std::string &title) {
    _dictionaryTitle = title;
}

void TerminalOperation::_setDictionaryPrompt(const std::string &prompt) {
    _dictionaryPrompt = prompt;
}

std::string TerminalOperation::_getDictionaryTitle() {
    return _dictionaryTitle;
}

std::string TerminalOperation::_getDictionaryPrompt() {
    return _dictionaryPrompt;
}

// template <typename... Args>
// void TerminalOperation::_print(Args &&...args) {
//     ((std::cout << std::forward<Args>(args)), ...);
// }

// template <typename T>
// T TerminalOperation::_getUserInput(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate) {
//     T value;
//     while (true) {
//         try {
//             _print(prompt);
//             std::cin >> value;

//             if (std::cin.fail()) {
//                 throw std::invalid_argument("read input error");
//             }

//             auto [isValid, validationMsg] = validate(value);
//             if (!isValid) {
//                 throw std::invalid_argument(validationMsg);
//             }
//             break;
//         } catch (const std::exception &e) {
//             _print(e.what(), "\n");
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         }
//     }
//     return value;
// }