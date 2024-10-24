#ifndef LABMENU_H
#define LABMENU_H

#include "../../src/View/terminal.h"
#include "../../src/Lab/LabLogic/Queue.h"
#include "../../src/View/Utils/io.h"

#include <string>

TerminalApp getMenuGestionTurnos(Cola<std::string> queue);

#endif //LABMENU_H
