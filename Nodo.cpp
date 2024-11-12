// Nodo.cpp
#include "Nodo.h"

// Constructor que recibe un puntero a un entero
Nodo::Nodo(int* item) {
    setInfo(item);     // Inicializa la información del nodo
    setSgte(nullptr);  // Inicializa el puntero siguiente como nullptr
}

// Establece el valor del nodo
void Nodo::setInfo(int* item) {
    info = item;
}

// Establece el siguiente nodo
void Nodo::setSgte(Nodo* siguiente) {
    sgte = siguiente;
}

// Obtiene el valor del nodo
int* Nodo::getInfo() {
    return info;
}

// Obtiene el siguiente nodo
Nodo* Nodo::getSgte() {
    return sgte;
}
