#pragma once
#include <list>
#include "Pair.h"  

template <typename T>
class Grafo {
private:
    int V;                          // Número de vértices
    std::list<Pair<int, T>>* ListaAdy;  // Arreglo dinámico de listas de Pair
    // Pair<destino, peso>

public:
    // Constructor
    Grafo(int vertices) {
        V = vertices;
        ListaAdy = new std::list<Pair<int, T>>[V];
    }

    // Destructor
    ~Grafo() {
        delete[] ListaAdy;
    }