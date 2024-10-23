// #include "./src/View/terminal_implementations.h"
// #include "./src/Lab/LabLogic/Queue.h"
#include <iostream>
#include <string>

template <typename T>
class ColaNode
{
public:
  T data;
  ColaNode *next;

  ColaNode(T element) : data(element), next(nullptr) {}
};



template <typename T>
class Cola
{
private:
  ColaNode<T> *front;
  ColaNode<T> *back;
  int length;

public:
  Cola() : front(nullptr), back(nullptr), length(0) {}

  ~Cola()
  {
    clear();
  }

  bool esVaciaCola() const
  {
    return length == 0;
  }

  void insertarElem(const T &element)
  {
    ColaNode<T> *newNode = new ColaNode<T>(element);
    if (esVaciaCola())
    {
      front = back = newNode;
    }
    else
    {
      back->next = newNode;
      back = newNode;
    }
    length++;
  }

  bool atender(T &element)
  {
    if (!esVaciaCola())
    {
      ColaNode<T> *nodeToRemove = front;
      element = front->data;
      front = front->next;
      if (front == nullptr)
      {
        back = nullptr;
      }
      delete nodeToRemove;
      length--;
      return true;
    }
    return false;
  }

  bool removeAt(int position)
  {
    if (position < 0 || position >= length)
      return false;
    if (position == 0)
    {
      T temp;
      return atender(temp);
    }
    ColaNode<T> *current = front;
    for (int i = 0; i < position - 1; ++i)
    {
      current = current->next;
    }
    ColaNode<T> *nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    if (nodeToDelete == back)
    {
      back = current;
    }
    delete nodeToDelete;
    length--;
    return true;
  }

  T getUltimo() const
  {
    if (!esVaciaCola())
    {
      return back->data;
    }
    return T();
  }

  int getLength() const
  {
    return length;
  }

  void clear()
  {
    while (!esVaciaCola())
    {
      T temp;
      atender(temp);
    }
  }

  void listarTurnos()
  {
    if (!esVaciaCola())
    {
      std::cout << "Turnos en cola:\n";
      ColaNode<T> *current = front;
      while (current != nullptr)
      {
        std::cout << current->data << std::endl;
        current = current->next;
      }
    }
  }
};

int main()
{
    Cola<std::string> queue;

    // Insertar elementos
    queue.insertarElem("item1");
    queue.insertarElem("item2");
    queue.insertarElem("item3");

    std::cout << "Queue length: " << queue.getLength() << std::endl;

    // Listar elementos
    queue.listarTurnos();

    // Atender elementos
    std::string frontItem;
    if (queue.atender(frontItem)) {
        std::cout << "atendido al turno: " << frontItem << std::endl;
    }
    std::cout << "largo de la cola: " << queue.getLength() << std::endl;

    // Eliminar elemento en posicion 1
    if (queue.removeAt(1)) {
        std::cout << "Removido el turno en la posicion 1." << std::endl;
    }

    // Listar elementos
    queue.listarTurnos();


  return 0;
}