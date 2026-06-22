// Archivo: Pair.h
// Autores: Emilio, Isaac, Maria Celeste
// Descripción: Clase que agrupa dos elementos (llave y valor).
// Funcionalidades principales:
//  - Almacenar asociaciones (ej: ID de vecino y peso del arco).
//  - Proveer operadores de comparación basados en la llave para ordenar elementos.

#pragma once
#include <stdexcept>
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

template <typename K, typename V>
class Pair {
public:
    K key;
    V value; 

    Pair() : key(), value() {}

    Pair(K key) : key(key), value() {}

    Pair(K key, V value) : key(key), value(value) {}

    bool operator==(const Pair<K, V>& other) const {
        return key == other.key;
    }

    bool operator!=(const Pair<K, V>& other) const {
        return key != other.key;
    }

    bool operator>=(const Pair<K, V>& other) const {
        return key >= other.key;
    }

    bool operator<=(const Pair<K, V>& other) const {
        return key <= other.key;
    }

    bool operator>(const Pair<K, V>& other) const {
        return key > other.key;
    }

    bool operator<(const Pair<K, V>& other) const {
        return key < other.key;
    }

    friend ostream& operator<<(ostream& os, const Pair<K, V>& p) {
        os << "(" << p.key << "," << p.value << ")";
        return os;
    }
};