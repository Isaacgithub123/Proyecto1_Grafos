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