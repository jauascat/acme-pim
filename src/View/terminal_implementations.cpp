#include "./terminal_implementations.h"
#include "SubMenus/Category/Categorias.h"
#include "SubMenus/Products/Productos.h"
#include "SubMenus/Search/Busqueda.h"
#include "SubMenus/Variants/Variantes.h"
#include "../Lab/LabMenu.h"

TerminalApp GetAppInstance(Cola<std::string>& queue)
{
  auto app = TerminalApp::Builder()
    .withDictionary({
      {"title", "Proyecto!"},
      {"prompt", "Elija una opcion: "},
      {"exit", "Saliendo...\n"},
      {"invalid_option", "Opcion invalida, por favor intentalo de nuevo.\n"}
    })
    //.withOperation<TerminalApp>(getSubmenuProductos())
    //.withOperation<TerminalApp>(getSubmenuCategorias())
    //.withOperation<TerminalApp>(getSubmenuBusqueda())
    //.withOperation<TerminalApp>(getSubmenuVariantes())
    .withOperation<TerminalApp>(getMenuGestionTurnos(queue))
    .build();

  return app;
}
