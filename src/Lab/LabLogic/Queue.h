#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

const long int MAX_SIZE = 100;

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

  bool insertarElem(const T &element)
  {

    if(length + 1 > MAX_SIZE) {
      return false;
    }

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
    return true;
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

  bool eliminarElem(int position)
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

  int getLongitud() const
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

#endif
