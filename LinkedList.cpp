// LinkedList.cpp
#include "LinkedList.h"
#include <iostream>
using namespace std;

// Constructor: inicializa la lista vacía
LinkedList::LinkedList()
{
  head = nullptr;
}

// Destructor: libera la memoria utilizada por los nodos
LinkedList::~LinkedList()
{
  Nodo *current = head;
  Nodo *next;
  while (current != nullptr)
  {
    next = current->getSgte();
    delete current;
    current = next;
  }
  head = nullptr;
}

// Método para insertar un nodo al final de la lista
void LinkedList::insert(int value)
{
  int *newValue = new int(value);     // Crear un nuevo valor dinámico
  Nodo *newNode = new Nodo(newValue); // Crear un nuevo nodo con el valor

  if (head == nullptr)
  { // Si la lista está vacía
    head = newNode;
  }
  else
  {
    Nodo *temp = head;
    while (temp->getSgte() != nullptr)
    { // Buscar el último nodo
      temp = temp->getSgte();
    }
    temp->setSgte(newNode); // Conectar el nuevo nodo al final de la lista
  }
}

// Método para eliminar un nodo con un valor específico
void LinkedList::remove(int value)
{
  if (head == nullptr)
  {
    cout << "La lista está vacía.\n";
    return;
  }

  // Si el nodo a eliminar es el primero
  if (*(head->getInfo()) == value)
  {
    Nodo *temp = head;
    head = head->getSgte();
    delete temp;
    cout << "Nodo con valor " << value << " eliminado.\n";
    return;
  }

  // Buscar el nodo a eliminar
  Nodo *temp = head;
  while (temp->getSgte() != nullptr && *(temp->getSgte()->getInfo()) != value)
  {
    temp = temp->getSgte();
  }

  if (temp->getSgte() == nullptr)
  {
    cout << "Valor " << value << " no encontrado en la lista.\n";
  }
  else
  {
    Nodo *nodeToDelete = temp->getSgte();
    temp->setSgte(temp->getSgte()->getSgte());
    delete nodeToDelete;
    cout << "Nodo con valor " << value << " eliminado.\n";
  }
}

// Método para imprimir los elementos de la lista
void LinkedList::display()
{
  if (head == nullptr)
  {
    cout << "La lista está vacía.\n";
    return;
  }

  Nodo *temp = head;
  while (temp != nullptr)
  {
    cout << *(temp->getInfo()) << " -> ";
    temp = temp->getSgte();
  }
  cout << "nullptr\n";
}

void LinkedList::display_recursive(Nodo *node)
{
  if (node == nullptr) {
    node = head;
  }
  if (node == nullptr) {
    cout << "\n empty list\n";
    return;
  }
  auto value = *(node->getInfo());
  cout << value << "\n";

  auto next = node->getSgte();
  if (next == nullptr)
  { 
    return;
  }
  display_recursive(next);
}
