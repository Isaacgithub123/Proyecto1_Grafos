#pragma once
#include <stdexcept>

using namespace std;

template <typename E>
class BSTNode {
public:
    E element;
    BSTNode<E>* left;
    BSTNode<E>* right;

    BSTNode(E element) {
        this->element = element;
        left = right = nullptr;
    }

    int children() {
        int count = 0;
        if (left != nullptr)
            count++;
        if (right != nullptr)
            count++;
        return count;
    }

    BSTNode<E>* getOnlyChild() {
        if (children() != 1)
            throw runtime_error("No only child");

        return left != nullptr ? left : right;
    }
};

