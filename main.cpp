#include "./src/View/terminal_implementations.h"

int main()
{
  auto app = GetAppInstance();
  app.execute();
  app.queue.destruirCola();
  return 0;
}