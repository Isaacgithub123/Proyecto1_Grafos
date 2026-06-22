// Archivo: GNode.h
// Autores: Emilio, Isaac, Maria Celeste
// Descripción: Clase que representa un vértice o nodo dentro del grafo. Almacena la información
// necesaria para la representación espacial y lógica.
// Funcionalidades principales:
//  - Almacenar el identificador único del nodo.
//  - Guardar coordenadas cartesianas (X, Y) para su dibujo en pantalla.
//  - Mantener banderas de estado (como 'visited') para facilitar los recorridos.

#pragma once

class GNode {
public:
    int id;
    double x;
    double y;
    bool visited;

    GNode() {
        id = -1;
        x = 0;
        y = 0;
        visited = false;
    }

    GNode(int id, double x, double y) {
        this->id = id;
        this->x = x;
        this->y = y;
        visited = false;
    }


};