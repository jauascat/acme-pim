#include <utility>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "src/logic.h"


template <typename... Args>
void _print(Args &&...args)
{
  ((std::cout << std::forward<Args>(args)), ...);
}
template <typename T>
T _getTerminalInput()
{
  T value;
  std::cin >> value;
  return value;
}


class TerminalOperation
{
public:
  std::unordered_map<std::string, std::string> _dictionary;
  virtual ~TerminalOperation() = default;
  virtual void execute() = 0;
  std::string getDescription() const {
    return _dictionary.at("description");
  }
};



template <typename Child, typename... InputTypes>
class TerminalOp : public TerminalOperation
{
public:
  using Operate = std::function<void(InputTypes..., const std::unordered_map<std::string, std::string> &)>;
  Operate _operate;
  TerminalOp() = default;

  Child &withDictionary(const std::unordered_map<std::string, std::string> &newDictionary)
  {
    _dictionary = newDictionary;
    return static_cast<Child &>(*this);
  }

  Child& onInput(Operate callback)
  {
    _operate = callback;
    return static_cast<Child &>(*this);
  }
  void executeSafetly(std::function<void()> onPrompt)
  {
    try
    {
      _print(this->_dictionary.at("prompt"));
      onPrompt();
    }
    catch (const std::exception &e)
    {
      _print("Error at", this->_dictionary.at("error"), ":\n", e.what(), "\n");
    }
  }
};



template <typename T>
class UnaryOperation final : public TerminalOp<UnaryOperation<T>, T>
{
public:
  void execute() override
  {
    this->executeSafetly([&]() {
      T value1 = _getTerminalInput<T>();
      this->_operate(value1, this->_dictionary);
    });
  }
};




template <typename T, typename U>
class BinaryOperation final : public TerminalOp<BinaryOperation<T, U>, T, U>
{
public:
  void execute() override
  {
    this->executeSafetly([&]() {
      T value1 = _getTerminalInput<T>();
      U value2 = _getTerminalInput<U>();
      this->_operate(value1, value2, this->_dictionary);
    });   
  }
};




class TerminalApp : public TerminalOp<TerminalApp>
{
private:
  std::vector<std::unique_ptr<TerminalOperation>> _operations;
public:
  class Builder;

  void execute()
  {
    while (true)
    {
      _showOptions();
      const int option = _getTerminalInput<int>();
      if (option == static_cast<int>(_operations.size()) + 1)
      {
        _print(_dictionary.at("exit"));
        break;
      }
      if (option > 0 && static_cast<int>(option) <= _operations.size())
      {
        _operations[option - 1]->execute();
      }
      else
      {
        _print(_dictionary.at("invalid_option"));
      }
    }
  }

  void _showOptions() const
  {
    _print("\n===== ", _dictionary.at("title"), " =====\n");
    for (size_t i = 0; i < _operations.size(); ++i)
    {
      _print(i + 1, ". ", _operations[i]->getDescription(), "\n");
    }
    _print(_operations.size() + 1, ". Exit\n");
    _print(_dictionary.at("prompt"));
  }
};



class TerminalApp::Builder
{
  TerminalApp _app;
public:
  Builder() : _app() {}

  Builder& withDictionary(const std::unordered_map<std::string, std::string> &dictionary)
  {
    _app._dictionary = dictionary;
    return *this;
  }

  template <typename T, typename... Args>
  Builder& withOperation(Args &&...args)
  {
    _app._operations.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return *this;
  }

  TerminalApp build()
  {
    return std::move(_app);
  }
};


TerminalApp getCalculatorMenu()
{
  auto isPrimeOp = UnaryOperation<int>()
    .withDictionary({
      {"prompt", "Enter a number to check if it's prime: "},
      {"description", "Check if a number is prime"},
      {"is", " is a prime number!\n"},
      {"is_not", " is not a prime number.\n"},
      {"error", "Invalid input for prime check.\n"}
    })
    .onInput([](int value, const auto &dict) {
      bool isPrime = Logic::isPrime(value);
      if (isPrime) {
        _print(value, dict.at("is"));
      } else {
        _print(value, dict.at("is_not"));
      }
    });

  auto addNumbersOp = BinaryOperation<int, int>()
    .withDictionary({
      {"prompt", "Enter two numbers to add: "},
      {"description", "Perform addition"},
      {"result", "Result: "},
      {"error", "Invalid input for addition.\n"}
    })
    .onInput([](int a, int b, const auto &dict) {
      int result = Logic::add(a, b);
      _print(dict.at("result"), a, " + ", b, " = ", result, "\n");
    });
    
  auto subtractNumbersOp = BinaryOperation<int, int>()
    .withDictionary({
      {"prompt", "Enter two numbers to subtract: "},
      {"description", "Perform subtraction"},
      {"result", "Result: "},
      {"error", "Invalid input for subtraction.\n"}
    })
    .onInput([](int a, int b, const auto &dict) {
      int result = Logic::subtract(a, b);
      _print(dict.at("result"), a, " - ", b, " = ", result, "\n");
    });

  auto multiplyNumbersOp = BinaryOperation<int, int>()
    .withDictionary({
      {"prompt", "Enter two numbers to multiply: "},
      {"description", "Perform multiplication"},
      {"result", "Result: "},
      {"error", "Invalid input for multiplication.\n"}
    })
    .onInput([](int a, int b, const auto &dict) {
      int result = Logic::multiply(a, b);
      _print(dict.at("result"), a, " * ", b, " = ", result, "\n");
    });

  auto divideNumbersOp = BinaryOperation<int, int>()
    .withDictionary({
      {"prompt", "Enter two numbers to divide: "},
      {"description", "Perform division"},
      {"result", "Result: "},
      {"error", "Invalid input for division.\n"}
    })
    .onInput([](int a, int b, const auto &dict) {
      double result = Logic::divide(a, b);
      _print(dict.at("result"), a, " / ", b, " = ", result, "\n");
    });

  auto calculatorApp = TerminalApp::Builder()
    .withDictionary({
      {"title", "Calculator!"},
      {"prompt", "Choose an option: "},
      {"exit", "Exiting...\n"},
      {"invalid_option", "Invalid option, please try again.\n"}
    })
    .withOperation<UnaryOperation<int>>(isPrimeOp)
    .withOperation<BinaryOperation<int, int>>(addNumbersOp)
    .withOperation<BinaryOperation<int, int>>(subtractNumbersOp)
    .withOperation<BinaryOperation<int, int>>(multiplyNumbersOp)
    .withOperation<BinaryOperation<int, int>>(divideNumbersOp)
    .build();


  return calculatorApp;
}

int main()
{
  auto calculator = getCalculatorMenu();
  calculator.execute();
  return 0;
}
