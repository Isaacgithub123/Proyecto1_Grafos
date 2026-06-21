#include <iostream>
#include "Grafo.h"

using namespace std;

template <typename T>
void mostrarGrafo(const Grafo<T>& g) {
    int V = g.getV();
    cout << "Aristas del grafo:\n";
    for (int u = 0; u < V; u++) {
        list<Pair<int, T>> vecinos = g.getVecinos(u);
        for (const auto& arista : vecinos) {
            if (u < arista.key) {
                cout << "  " << u << " -- " << arista.key << " (peso " << arista.value << ")\n";
            }
        }
    }
}

int main() {
    Grafo<int> g(6);
    g.agregarArista(0, 1, 5);
    g.agregarArista(0, 2, 3);
    g.agregarArista(1, 3, 2);
    g.agregarArista(2, 4, 1);
    g.agregarArista(3, 4, 4);
    g.agregarArista(3, 5, 7);

    mostrarGrafo(g);

    cout << "\n--- BFS desde 0 (sin límite) ---\n";
    BSTree<Pair<int, int>> arbol1 = g.BFS(0);
    cout << "Árbol de expansión BFS (padre -> hijo):\n";
    arbol1.print();

    cout << "\n--- BFS desde 0 (distancia máxima = 2) ---\n";
    BSTree<Pair<int, int>> arbol2 = g.BFS(0, 2);
    cout << "Árbol de expansión BFS (padre -> hijo):\n";
    arbol2.print();

    cout << "\n--- BFS desde 0 (distancia máxima = 1) ---\n";
    BSTree<Pair<int, int>> arbol3 = g.BFS(0, 1);
    cout << "Árbol de expansión BFS (padre -> hijo):\n";
    arbol3.print();

    cout << "\n--- BFS desde 3 (sin límite) ---\n";
    BSTree<Pair<int, int>> arbol4 = g.BFS(3);
    cout << "Árbol de expansión BFS (padre -> hijo):\n";
    arbol4.print();

    return 0;
}