// Archivo: Grafo.h
// Autores: Emilio, Isaac, Maria Celeste
// Descripción: Estructura de datos principal que representa un grafo no dirigido y etiquetado
// mediante una lista de adyacencia optimizada.
// Funcionalidades principales:
//  - Almacenar una colección de nodos con posiciones espaciales (X, Y).
//  - Gestionar las conexiones (arcos) entre nodos y sus pesos (distancias).
//  - Brindar métodos para acceder a los vecinos de un nodo de forma eficiente.
//  - Controlar el estado de "visitado" de los nodos para los algoritmos de recorrido.

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
    ArrayList<LinkedList<Pair<int, double>>*>* listaAdy; // para BFS, DFS, PRIM Y 


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
 
    void generarNodosAleatorios(int ancho, int alto) {
        for (int i = 0; i < cantidadNodos; i++) {
            double x = rand() % ancho;
            double y = rand() % alto;
            agregarNodo(GNode(i, x, y));
        }
    }

    void generarArcos(double distanciaMax, int maxVecinos) {
        for (int i = 0; i < cantidadNodos; i++) {
            for (int j = i + 1; j < cantidadNodos; j++) {
                GNode n1 = getNodo(i);
                GNode n2 = getNodo(j);
                double distancia = getDistancia(n1, n2);
                if (distancia <= distanciaMax && getCantidadVecinos(i) < maxVecinos && getCantidadVecinos(j) < maxVecinos){
                    agregarArco(i,j,distancia);
                }
            }
        }
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
