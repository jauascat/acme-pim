#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <optional>
#include <variant>
#include <any>

#include "../models/pim.h"

class Operation
{
public:
  virtual void execute() = 0;
  virtual ~Operation() {}
  std::string _dictionaryDescription;
  std::string getDictionaryDescription();

protected:
  template <typename TInput, typename TOutput>
  class _GetUserInput
  {
  public:
    _GetUserInput() : _exitClause("x")
    {
      if constexpr (std::is_same_v<TInput, std::string>)
      {
        _castInput = [](const std::string &input)
        { return input; };
      }
      else if constexpr (std::is_same_v<TInput, double> || std::is_same_v<TInput, float>)
      {
        _castInput = [](const std::string &input)
        { return std::stod(input); };
      }
      else if constexpr (std::is_integral_v<TInput>)
      {
        _castInput = [](const std::string &input)
        { return std::stoi(input); };
      }
    }

    _GetUserInput &withPrompt(const std::string &prompt)
    {
      _prompt = prompt;
      return *this;
    }

    _GetUserInput &withParseFailureMessage(const std::string &message)
    {
      _parseFailureMessage = message;
      return *this;
    }

    _GetUserInput &withValidator(std::function<std::pair<bool, std::string>(const TInput &)> validator)
    {
      _validator = validator;
      return *this;
    }

    _GetUserInput &withExitClause(const std::string &exitClause)
    {
      _exitClause = exitClause;
      return *this;
    }

    _GetUserInput &withExitHandler(std::function<void()> handler)
    {
      _exitHandler = handler;
      return *this;
    }

    _GetUserInput &withParseFailureHandler(std::function<void()> handler)
    {
      _parseFailureHandler = handler;
      return *this;
    }

    _GetUserInput &withExceptionHandler(std::function<void(const std::exception &)> handler)
    {
      _exceptionHandler = handler;
      return *this;
    }

    _GetUserInput &withMapper(std::function<TOutput(const TInput &)> mapper)
    {
      _mapper = mapper;
      return *this;
    }

    _GetUserInput &withCastInput(std::function<TInput(const std::string &)> caster)
    {
      _castInput = caster;
      return *this;
    }

    std::optional<TOutput> execute()
    {
      if (!_mapper)
      {
        throw std::runtime_error("Mapper function is required.");
      }

      while (true)
      {
        try
        {
          std::cout << _prompt << " (" << _exitClause << " para cancelar):\n";
          std::string input;
          std::getline(std::cin, input);

          if (std::cin.fail())
          {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (_parseFailureHandler)
              _parseFailureHandler();
            throw std::runtime_error(_parseFailureMessage);
          }

          if (input == _exitClause)
          {
            if (_exitHandler)
              _exitHandler();
            return std::nullopt;
          }

          TInput value = _castInput(input);

          if (_validator)
          {
            auto [isValid, validationMsg] = _validator(value);
            if (!isValid)
              throw std::runtime_error(validationMsg);
          }

          return std::optional<TOutput>(_mapper(value));
        }
        catch (const std::runtime_error &e)
        {
          std::cout << e.what() << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::exception &e)
        {
          if (_exceptionHandler)
            _exceptionHandler(e);
          else
            std::cout << "Se produjo un error inesperado. Por favor, intente nuevamente.\n" << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
    }



  private:
    std::string _prompt;
    std::string _parseFailureMessage = "Formato de entrada inválido.";
    std::string _exitClause;
    std::function<std::pair<bool, std::string>(const TInput &)> _validator;
    std::function<void()> _exitHandler;
    std::function<void()> _parseFailureHandler;
    std::function<void(const std::exception &)> _exceptionHandler;
    std::function<TOutput(const TInput &)> _mapper;
    std::function<TInput(const std::string &)> _castInput;
    std::any _store;
  };

  PIM *_pim = nullptr;
  std::string _dictionaryTitle;
  std::string _dictionaryPrompt;

  template <typename... Args>
  void _print(Args &&...args)
  {
    ((std::cout << std::forward<Args>(args)), ...);
  }

  void _setPIM(PIM *pim);
  PIM *_getPIM();

  void _setDictionaryDescription(const std::string &description);
  void _setDictionaryTitle(const std::string &title);
  void _setDictionaryPrompt(const std::string &prompt);

  std::string _getDictionaryTitle();
  std::string _getDictionaryPrompt();
};