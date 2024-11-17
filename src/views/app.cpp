#include "app.h"

#include "menus/Variants/variants.h"
#include "menus/Products/products.h"
#include "menus/Categories/categories.h"

App::App(PIM* pim)
{
  _setPIM(pim);
  _setDictionaryTitle("ACME PIM!");
  _setDictionaryPrompt("Elija una opcion: ");
  _setDictionaryExit("Saliendo...\n");
  _setDictionaryInvalidOption("Opcion invalida, por favor intentalo de nuevo.\n");
  _setMenuOption<products::Submenu>(products::Submenu(pim));
  _setMenuOption<variants::Submenu>(variants::Submenu(pim));
  _setMenuOption<categories::Submenu>(categories::Submenu(pim));
};