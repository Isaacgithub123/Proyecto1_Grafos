#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>
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
        nodos = new ArrayList<GNode>(n);
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
        listaAdy->goToPos(nOrigen);
        LinkedList<Pair<int, double>>* vecinos = listaAdy->getElement();
        vecinos->append(Pair<int, double>(nDestino, peso));
        listaAdy->goToPos(nDestino);
        vecinos = listaAdy->getElement();
        vecinos->append(Pair<int, double>(nOrigen, peso));
        arcos->append(Arco(nOrigen, nDestino, peso));
    }
    bool existeArco(int origen, int destino) {
        LinkedList<Pair<int, double>>* vecinos = getVecinos(origen);
        vecinos->goToStart();
        while (!vecinos->atEnd()) {
            Pair<int, double> p = vecinos->getElement();
            if (p.key == destino)
                return true;
            vecinos->next();
        }
        return false;
    }
    void agregarNodo(GNode nodo) {
        nodos->append(nodo);
    }
    GNode getNodo(int id) {
		nodos->goToPos(id);
		return nodos->getElement();
    }
    List<Arco>* getArcos() {
        return arcos;
    }

    LinkedList<Pair<int, double>>* getVecinos(int id) {
		listaAdy->goToPos(id);
		return listaAdy->getElement();
    }
    int getCantidadNodos() {
		return cantidadNodos;
    }
    int getCantidadArcos() {
		return arcos->getSize();
    }
    int getCantidadVecinos(int id) {
		listaAdy->goToPos(id);
		return listaAdy->getElement()->getSize();
    }

    double getDistancia(GNode n1,GNode n2) {
        double dx = n1.x - n2.x;
        double dy = n1.y - n2.y;
        return sqrt(dx * dx + dy * dy);
    }

    void marcarVisitado(int id) {
		GNode nodo = getNodo(id);
		nodo.visited = true;
		nodos->setElement(nodo);
    }
    bool visitado(int id) {
        return getNodo(id).visited;
    }
    void limpiarVisitados() {
		for (int i = 0; i < cantidadNodos; i++) {
			nodos->goToPos(i);
			GNode nodo = nodos->getElement();
			nodo.visited = false;
			nodos->setElement(nodo);
		}
    }
};
