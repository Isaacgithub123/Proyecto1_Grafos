#pragma once
#include <stdexcept>
#include <iostream>
#define DEFAULT_MAX 1024

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
        return key == other.key && value == other.value;
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