#pragma once
#include "Grafo.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "MinHeap.h"
#include "Pair.h"
#include <iostream>

class Algoritmos {
public:
    // ===== BFS =====
    // Devuelve el orden de visita en un ArrayList<int> y llena 'arbol' con los arcos usados para descubrir nodos.
    static ArrayList<int>* BFS(Grafo& g, int inicio, LinkedList<Arco>& arbol) {
        ArrayList<int>* orden = new ArrayList<int>(g.getCantidadNodos());
        g.limpiarVisitados();
        LinkedQueue<int> cola;
        cola.enqueue(inicio);
        g.marcarVisitado(inicio);
        while (!cola.isEmpty()) {
            int actual = cola.dequeue();
            orden->append(actual);
            LinkedList<Pair<int, double>>* vecinos = g.getVecinos(actual);
            vecinos->goToStart();
            while (!vecinos->atEnd()) {
                Pair<int, double> p = vecinos->getElement();
                int v = p.key;
                if (!g.visitado(v)) {
                    g.marcarVisitado(v);
                    arbol.append(Arco(actual, v, 0.0));   // arco de descubrimiento
                    cola.enqueue(v);
                }
                vecinos->next();
            }
        }
        return orden;
    }

    // ===== DFS =====
    static ArrayList<int>* DFS(Grafo& g, int inicio, LinkedList<Arco>& arbol) {
        ArrayList<int>* orden = new ArrayList<int>(g.getCantidadNodos());
        g.limpiarVisitados();
        LinkedStack<int> pila;
        pila.push(inicio);
        g.marcarVisitado(inicio);
        while (!pila.isEmpty()) {
            int actual = pila.pop();
            orden->append(actual);
            LinkedList<Pair<int, double>>* vecinos = g.getVecinos(actual);
            vecinos->goToStart();
            while (!vecinos->atEnd()) {
                Pair<int, double> p = vecinos->getElement();
                int vecino = p.key;
                if (!g.visitado(vecino)) {
                    g.marcarVisitado(v);
                    arbol.append(Arco(actual, vecino, 0.0));
                    pila.push(v);
                }
                vecinos->next();
            }
        }
        return orden;
    }

    static void Dijkstra(Grafo& g, int inicio, int destino,
        LinkedList<Arco>& camino,
        double*& dist, int*& padre) {
        int n = g.getCantidadNodos();
        dist = new double[n];
        padre = new int[n];
        bool* visitado = new bool[n];
        for (int i = 0; i < n; ++i) {
            dist[i] = 1e9;
            padre[i] = -1;
            visitado[i] = false;
        }
        dist[inicio] = 0.0;

        MinHeap<Pair<double, int>> heap(n * n); // tamaño máximo estimado
        heap.insert(Pair<double, int>(0.0, inicio));

        while (heap.getSize() > 0) {
            Pair<double, int> actual = heap.removeFirst();
            double d = actual.key;
            int u = actual.value;
            if (visitado[u]) continue;
            visitado[u] = true;

            LinkedList<Pair<int, double>>* vecinos = g.getVecinos(u);
            vecinos->goToStart();
            while (!vecinos->atEnd()) {
                Pair<int, double> p = vecinos->getElement();
                int v = p.key;
                double w = p.value;
                if (!visitado[v] && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    padre[v] = u;
                    heap.insert(Pair<double, int>(dist[v], v));
                }
                vecinos->next();
            }
        }
        delete[] visitado;
        // Construir camino (si destino != -1)
        if (destino != -1) {
            int actual = destino;
            while (actual != -1 && padre[actual] != -1) {
                int p = padre[actual];
                double peso = 0;
                LinkedList<Pair<int, double>>* vecinosP = g.getVecinos(p);
                vecinosP->goToStart();
                while (!vecinosP->atEnd()) {
                    Pair<int, double> par = vecinosP->getElement();
                    if (par.key == actual) {
                        peso = par.value;
                        break;
                    }
                    vecinosP->next();
                }
                camino.insert(Arco(p, actual, peso));
                actual = p;
            }
        }
    }

    // PRIM 
    static void Prim(Grafo& g, int inicio, LinkedList<Arco>& arbol) {
        arbol.clear();
        int n = g.getCantidadNodos();
        double* dist = new double[n];
        int* padre = new int[n];
        bool* incluido = new bool[n];
        for (int i = 0; i < n; ++i) {
            dist[i] = 1e9;
            padre[i] = -1;
            incluido[i] = false;
        }
        dist[inicio] = 0.0;
        MinHeap<Pair<double, int>> heap(n * n);
        heap.insert(Pair<double, int>(0.0, inicio));

        while (heap.getSize() > 0) {
            Pair<double, int> actual = heap.removeFirst();
            double d = actual.key;
            int u = actual.value;
            if (incluido[u]) continue;
            incluido[u] = true;

            if (padre[u] != -1) {
                double peso = 0;
                LinkedList<Pair<int, double>>* vecinos = g.getVecinos(u);
                vecinos->goToStart();
                while (!vecinos->atEnd()) {
                    Pair<int, double> p = vecinos->getElement();
                    if (p.key == padre[u]) {
                        peso = p.value;
                        break;
                    }
                    vecinos->next();
                }
                arbol.append(Arco(padre[u], u, peso));
            }

            LinkedList<Pair<int, double>>* vecinos = g.getVecinos(u);
            vecinos->goToStart();
            while (!vecinos->atEnd()) {
                Pair<int, double> p = vecinos->getElement();
                int v = p.key;
                double w = p.value;
                if (!incluido[v] && w < dist[v]) {
                    dist[v] = w;
                    padre[v] = u;
                    heap.insert(Pair<double, int>(dist[v], v));
                }
                vecinos->next();
            }
        }

        delete[] dist;
        delete[] padre;
        delete[] incluido;
    }

    // ===== KRUSKAL =====
    static void Kruskal(Grafo& g, LinkedList<Arco>& arbol) {

    }
};