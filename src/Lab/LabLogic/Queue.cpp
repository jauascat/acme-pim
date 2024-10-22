#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue() : frente(0), final(-1), longitud(0) {}

bool Queue::esVaciaCola() const {
    return longitud == 0;
}

Queue Queue::insertarElem(const string& turno) {
    if (longitud < MAX_SIZE) {
        final = (final + 1) % MAX_SIZE;
        datos[final] = turno;
        longitud++;
        cout << "Turno " << turno << " ha sido insertado en la cola." << endl;
    } else {
        cout << "La cola está llena. No se puede agregar más turnos." << endl;
    }
    return *this;
}

Queue Queue::atender(string& turno) {
    if (!esVaciaCola()) {
        turno = datos[frente];
        frente = (frente + 1) % MAX_SIZE;
        longitud--;
        cout << "Atendiendo turno: " << turno << endl;
    } else {
        cout << "No hay clientes en espera." << endl;
    }
    return *this;
}

Queue Queue::eliminarElem(int posicion) {
    if (posicion >= 0 && posicion < longitud) {
        for (int i = posicion; i != final; i = (i + 1) % MAX_SIZE) {
            datos[i] = datos[(i + 1) % MAX_SIZE];
        }
        final = (final - 1 + MAX_SIZE) % MAX_SIZE;
        longitud--;
        cout << "Turno eliminado." << endl;
    } else {
        cout << "Posición inválida." << endl;
    }
    return *this;
}

string Queue::ultimoElem() const {
    if (!esVaciaCola()) {
        return datos[final];
    }
    return "La cola está vacía";
}

int Queue::getLongitud() const {
    return longitud;
}

void Queue::listarTurnos() const {
    if (!esVaciaCola()) {
        cout << "Turnos en la cola: " << endl;
        for (int i = 0; i < longitud; ++i) {
            int index = (frente + i) % MAX_SIZE;
            cout << datos[index] << " ";
        }
        cout << endl;
    } else {
        cout << "La cola está vacía." << endl;
    }
}

void Queue::destruirCola() {
    frente = 0;
    final = -1;
    longitud = 0; // Resetea la cola
    datos.clear();
}

