#pragma once
#include "BSTNode.h"
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename E>
class BSTree {
private:
    BSTNode<E>* root;
    int size = 0;

    BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
        if (current == nullptr)
            return new BSTNode<E>(element);
        if (element == current->element)
            throw runtime_error("duplicated");
        if (element < current->element)
            current->left = insertAux(current->left, element);
        else
            current->right = insertAux(current->right, element);
        return current;
    }

    E findAux(BSTNode<E>* current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found");
        if (current->element == element)
            return current->element;
        if (element < current->element)
            return findAux(current->left, element);
        return findAux(current->right, element);
    }

    bool containsAux(BSTNode<E>* current, E element) {
        if (current == nullptr)
            return false;
        if (current->element == element)
            return true;
        if (element < current->element)
            return containsAux(current->left, element);
        return containsAux(current->right, element);
    }

    void clearAux(BSTNode<E>* current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    void printAux(BSTNode<E>* current) {
        if (current == nullptr)
            return;
        printAux(current->left);
        cout << current->element << " ";
        printAux(current->right);
    }

    void getElementsAux(BSTNode<E>* current, List<E>* list) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, list);
        list->insertBack(current->element);
        getElementsAux(current->right, list);
    }

public:
    BSTree() {
        root = nullptr;
    }

    ~BSTree() {
        clear();
    }

    void insert(E element) {
        root = insertAux(root, element);
        size++;
    }

    E find(E element) {
        return findAux(root, element);
    }

    bool contains(E element) {
        return containsAux(root, element);
    }

    void clear() {
        clearAux(root);
        root = nullptr;
        size = 0;
    }

    List<E>* getElements() {
        List<E>* list = new List<E>();
        getElementsAux(root, list);
        return list;
    }

    int getSize() {
        return size;
    }

    void print() {
        printAux(root);
        cout << endl;
    }
};