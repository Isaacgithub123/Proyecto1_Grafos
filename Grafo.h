#pragma once
#include <list>
#include <stdexcept>
#include <iostream>
#include <queue>
#include "Pair.h"
#include "BSTree.h"

using namespace std;

template <typename T>
class Grafo {
private:
    int V;
    std::list<Pair<int, T>>* ListaAdy;

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
            if (arista.key == v) return true;
        }
        return false;
    }

    BSTree<Pair<int, int>> BFS_Aux(int origen, int maxDist) const {
        bool* visitado = new bool[V];
        int* distancia = new int[V];
        int* padre = new int[V];

        for (int i = 0; i < V; i++) {
            visitado[i] = false;
            distancia[i] = -1;
            padre[i] = -1;
        }

        queue<int> q;
        visitado[origen] = true;
        distancia[origen] = 0;
        q.push(origen);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            if (maxDist != -1 && distancia[u] >= maxDist)
                continue;

            for (const auto& arista : ListaAdy[u]) {
                int v = arista.key;
                if (!visitado[v]) {
                    visitado[v] = true;
                    distancia[v] = distancia[u] + 1;
                    padre[v] = u;
                    q.push(v);
                }
            }
        }

        BSTree<Pair<int, int>> arbol;
        for (int i = 0; i < V; i++) {
            if (padre[i] != -1) {
                arbol.insert(Pair<int, int>(padre[i], i));
            }
        }

        delete[] visitado;
        delete[] distancia;
        delete[] padre;

        return arbol;
    }

public:
    Grafo(int vertices) {
        V = vertices;
        ListaAdy = new std::list<Pair<int, T>>[V];
    }

    ~Grafo() {
        delete[] ListaAdy;
    }

    void agregarArista(int u, int v, T peso) {
        if (u < 0 || u >= V || v < 0 || v >= V)
            throw runtime_error("Nodo fuera de rango");
        if (existeAristaAux(u, v))
            throw runtime_error("Arista duplicada");
        agregarAristaAux(u, v, peso);
    }

    bool existeArista(int u, int v) const {
        if (u < 0 || u >= V || v < 0 || v >= V)
            return false;
        return existeAristaAux(u, v);
    }

    void eliminarArista(int u, int v) {
        if (u < 0 || u >= V || v < 0 || v >= V)
            throw runtime_error("Nodo fuera de rango");
        if (!existeAristaAux(u, v))
            throw runtime_error("Arista no encontrada");
        eliminarAristaAux(u, v);
        eliminarAristaAux(v, u);
    }

    int getV() const { return V; }

    std::list<Pair<int, T>> getVecinos(int u) const {
        if (u < 0 || u >= V)
            throw runtime_error("Nodo fuera de rango");
        return ListaAdy[u];
    }

    BSTree<Pair<int, int>> BFS(int origen, int maxDist = -1) const {
        if (origen < 0 || origen >= V)
            throw runtime_error("Origen fuera de rango");
        if (maxDist < -1)
            throw runtime_error("Distancia máxima no puede ser menor que -1");
        return BFS_Aux(origen, maxDist);
    }
};