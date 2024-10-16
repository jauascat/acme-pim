#include "src/terminal_implementations.h"

int main()
{
  auto app = GetAppInstance();
  app.execute();
  return 0;
}