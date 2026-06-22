// Archivo: Arco.h
// Autores: Emilio, Isaac, Maria Celeste
// Descripción: Representa una arista o arco entre dos nodos del grafo.
// Funcionalidades principales:
//  - Almacenar los índices de los nodos de origen y destino.
//  - Guardar el peso del arco (distancia geométrica calculada).
//  - Implementar operadores de comparación para su uso en Min-Heaps y algoritmos de expansión.

#pragma once
#include <iostream>


class Arco {
public:
    int origen;
    int destino;
    double peso;

    Arco() {
        origen = destino = -1;
        peso = 0;
    }

    Arco(int origen, int destino, double peso) {
        this->origen = origen;
        this->destino = destino;
        this->peso = peso;
    }



    bool operator==(const Arco& other) const {
        return peso == other.peso;
    }

    bool operator!=(const Arco& other) const {
        return peso != other.peso;
    }

    bool operator<(const Arco& other) const {
        return peso < other.peso;
    }
    bool operator<=(const Arco& other) const {
        return peso <= other.peso;
    }

    bool operator>(const Arco& other) const {
        return peso > other.peso;
    }
    bool operator>=(const Arco& other) const {
        return peso >= other.peso;
    }

    friend std::ostream& operator<<(std::ostream& os, const Arco& a) {
        os << "(" << a.origen << "," << a.destino << "," << a.peso << ")";
        return os;
    }
};