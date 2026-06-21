#pragma once
#include <stdexcept>
#include <iostream>
#include "Pair.h"  
#include "GNode.h"
#include "Arco.h"
#include "LinkedList.h"
#include "ArrayList.h"


class Grafo {
private:

    int cantidadNodos;
    List<GNode>* nodos; 
    List<Arco>* arcos; // para Kruskal
    ArrayList<LinkedList<Pair<int, double>>*>* listaAdy; // para BFS, DFS, PRIM Y DIJKASTRA


public:
    // Constructor
    Grafo(int n) {
        cantidadNodos = n;
        nodos = new ArrayList<GNode>();
        arcos = new LinkedList<Arco>();
        listaAdy = new ArrayList<LinkedList<Pair<int, double>>*>(n);
        for (int i = 0; i < n; i++) {
            listaAdy->append(new LinkedList<Pair<int, double>>());
        }

    }

    // Destructor
    ~Grafo() {
        for (int i = 0; i < cantidadNodos; i++) {
            listaAdy->goToPos(i);
            delete listaAdy->getElement();
        }
        delete listaAdy;
        delete nodos;
        delete arcos;
    }


    void agregarArco(int nOrigen, int nDestino, double peso) {
        if (nOrigen < 0 || nOrigen >= cantidadNodos)
            throw runtime_error("Nodo origen invalido.");
        if (nDestino < 0 || nDestino >= cantidadNodos)
            throw runtime_error("Nodo destino invalido.");
        listaAdy->goToPos(nOrigen);
        LinkedList<Pair<int, double>>* vecinos = listaAdy->getElement();
        vecinos->append(Pair<int, double>(nDestino, peso));
        listaAdy->goToPos(nDestino);
        vecinos = listaAdy->getElement();
        vecinos->append(Pair<int, double>(nOrigen, peso));
    }

};
