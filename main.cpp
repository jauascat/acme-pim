#include "./src/View/terminal_implementations.h"
#include "./src/Lab/LabLogic/Queue.h"

int main()
{
  Queue queue;
  auto app = GetAppInstance(queue);
  app.execute();
  queue.destruirCola();
  return 0;
}