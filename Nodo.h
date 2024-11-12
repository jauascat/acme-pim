// Nodo.h
#ifndef NODO_H
#define NODO_H

class Nodo {
private:
    int* info;       // Puntero que almacena el dato del nodo
    Nodo* sgte;      // Puntero al siguiente nodo

public:
    // Constructor que recibe un puntero a un objeto (en este caso, int)
    Nodo(int* item);

    // Métodos para obtener y establecer información
    void setInfo(int* item);
    void setSgte(Nodo* siguiente);
    int* getInfo();
    Nodo* getSgte();
};

#endif
