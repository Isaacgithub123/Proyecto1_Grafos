#include <iostream>
#include "Grafo.h"
#include "LinkedList.h"  

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
    try {
        Grafo<int> g(6);
        g.agregarArista(0, 1, 5);
        g.agregarArista(0, 2, 3);
        g.agregarArista(1, 3, 2);
        g.agregarArista(2, 4, 1);
        g.agregarArista(3, 4, 4);
        g.agregarArista(3, 5, 7);

        mostrarGrafo(g);

        cout << "\n--- BFS desde 0 (sin límite) ---\n";
        BSTree<Pair<int, int>> arbolBFS = g.BFS(0);
        cout << "Tamaño del árbol BFS: " << arbolBFS.getSize() << endl;

        List<Pair<int, int>>* lista = arbolBFS.getElements();
        if (lista) {
            cout << "Árbol BFS (padre -> hijo):\n";
            lista->goToStart();
            while (!lista->atEnd()) {
                Pair<int, int> p = lista->getElement();
                cout << "  " << p.key << " -> " << p.value << endl;
                lista->next();
            }
            delete lista;   
        }

        
        cout << "\nUsando BSTree::print():\n";
        arbolBFS.print();

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}