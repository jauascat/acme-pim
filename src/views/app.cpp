#include "app.h"

App::App(PIM* pim)
{
  _setPIM(pim);
  _setDictionaryTitle("Proyecto!");
  _setDictionaryPrompt("Elija una opcion: ");
  _setDictionaryExit("Saliendo...\n");
  _setDictionaryInvalidOption("Opcion invalida, por favor intentalo de nuevo.\n");
  _setMenuOption<products::Submenu>(products::Submenu(pim));
};