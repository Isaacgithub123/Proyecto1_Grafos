#pragma once
#include <list>

using namespace std;

class Grafo {
private:
    int cantidadNodos;
    list<int>* adyacencias;