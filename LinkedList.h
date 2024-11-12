// LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Nodo.h"

class LinkedList {
private:
    Nodo* head;   // Puntero al primer nodo de la lista

public:
    LinkedList();      // Constructor
    ~LinkedList();     // Destructor

    // Métodos para manipular la lista
    void insert(int value);
    void remove(int value);
    void display();
    void display_recursive(Nodo* node = nullptr);
};

#endif
