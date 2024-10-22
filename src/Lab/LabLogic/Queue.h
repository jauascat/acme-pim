#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

const long int MAX_SIZE = 100;

class Queue {
private:
    string datos[MAX_SIZE];
    int frente;
    int final;
    int longitud;

public:
    Queue();
    bool esVaciaCola() const;
    Queue insertarElem(const string& turno);
    Queue atender(string& turno);
    Queue eliminarElem(int posicion);
    string ultimoElem() const;
    int getLongitud() const;
    void listarTurnos() const;
    void destruirCola();
};

#endif
