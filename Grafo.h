#pragma once
#include <list>
#include <stdexcept>
#include <iostream>
#include "Pair.h"  

using namespace std;

template <typename T>
class Grafo {
private:
    int V;                          // Número de vértices
    std::list<Pair<int, T>>* ListaAdy;  // Arreglo dinámico de listas de Pair
    // Pair<destino, peso>

    void agregarAristaAux(int u, int v, T peso) {
        ListaAdy[u].push_back(Pair<int, T>(v, peso));
        ListaAdy[v].push_back(Pair<int, T>(u, peso));
    }
    
    void eliminarAristaAux(int u, int v) {
        ListaAdy[u].remove_if([v](const Pair<int, T>& arista) {
            return arista.key == v;
            });
    }

    bool existeAristaAux(int u, int v) const {
        for (const auto& arista : ListaAdy[u]) {
            if (arista.key == v) {
                return true;
            }
        }
        return false;
    }

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

   
    void agregarArista(int u, int v, T peso) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            throw runtime_error("Vértice fuera de rango");
        }
        if (existeAristaAux(u, v)) {
            throw runtime_error("Arista duplicada");
        }
        agregarAristaAux(u, v, peso);
    }

    


    bool existeArista(int u, int v) const {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            return false;
        }
        return existeAristaAux(u, v);
    }

   

  
    void eliminarArista(int u, int v) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            throw runtime_error("Vértice fuera de rango");
        }
        if (!existeAristaAux(u, v)) {
            throw runtime_error("Arista no encontrada");
        }
        eliminarAristaAux(u, v);
        eliminarAristaAux(v, u);  // Eliminar en ambos sentidos 
    }