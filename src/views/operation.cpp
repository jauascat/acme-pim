#include "operation.h"

std::string Operation::getDictionaryDescription()
{
  return _dictionaryDescription;
}

void Operation::_setPIM(PIM *pim)
{
  _pim = pim;
}

PIM *Operation::_getPIM()
{
  return _pim;
}

void Operation::_setDictionaryDescription(const std::string &description)
{
  _dictionaryDescription = description;
}

void Operation::_setDictionaryTitle(const std::string &title)
{
  _dictionaryTitle = title;
}

void Operation::_setDictionaryPrompt(const std::string &prompt)
{
  _dictionaryPrompt = prompt;
}

std::string Operation::_getDictionaryTitle()
{
  return _dictionaryTitle;
}

std::string Operation::_getDictionaryPrompt()
{
  return _dictionaryPrompt;
}