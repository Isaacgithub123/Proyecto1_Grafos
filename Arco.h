#pragma once

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
};