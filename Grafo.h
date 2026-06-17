#pragma once
#include "LinkedList.h"

using namespace std;

class Grafo {
private:
    int cantidadNodos;
    list<int>* adyacencias;
public:
    Grafo(int n) {
        cantidadNodos = n;
        adyacencias = new list<int>[n];
    }

    ~Grafo() {
        delete[] adyacencias;
    }

    void agregarArista(int origen, int destino) {
     