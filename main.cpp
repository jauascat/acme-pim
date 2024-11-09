#include "src/views/app.h"

int main()
{
  PIM *pim = new PIM();
  App terminalApp(pim);
  terminalApp.execute();
  return 0;
}