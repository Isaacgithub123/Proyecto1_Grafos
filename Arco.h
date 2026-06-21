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