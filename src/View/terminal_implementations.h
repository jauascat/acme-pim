#pragma once

#include "terminal.h"
#include "../Lab/LabLogic/Queue.h"
#include "../View/Utils/io.h"

TerminalApp GetAppInstance(Cola<std::string> & queue);

