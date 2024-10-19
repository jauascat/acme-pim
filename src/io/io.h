#pragma once
#include <iostream>
#include <string>
#include <limits>

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

template <typename T>
T _getTerminalInput2(const std::string &prompt, std::function<std::pair<bool, std::string>(const T &)> validate)
{
  T value;
  while (true)
  {
    try
    {
      _print(prompt); // Print the prompt
      std::cin >> value;

      if (std::cin.fail())
      {
        throw std::invalid_argument("Invalid input type.");
      }

      // Validate the input and get the validation result and error message
      auto [isValid, validationMsg] = validate(value);
      if (!isValid)
      {
        throw std::invalid_argument(validationMsg);
      }

      break; // If valid, break out of the loop
    }
    catch (const std::exception &e)
    {
      _print(e.what(), "\n"); // Print error message
      std::cin.clear(); // Clear error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
    }
  }
  return value;
}