#pragma once
#include <iostream>
#include <string>

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