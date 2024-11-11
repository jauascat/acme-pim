#include "src/views/app.h"

int main()
{
  PIM *pim = new PIM();
  App app(pim);
  app.execute();
  return 0;
}