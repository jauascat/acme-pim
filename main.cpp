// #include "./src/View/terminal_implementations.h"
// #include "./src/Lab/LabLogic/Queue.h"
#include <iostream>
#include <string>

#include "src/Lab/LabMenu.h"
#include "src/Lab/LabLogic/Queue.h"

int main()
{
    Cola<std::string> queue;

    auto app = getMenuGestionTurnos(queue);

    app.execute();

  return 0;
}
