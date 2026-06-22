
// Archivo: LinkedStack.h
// Autores: Hecho en clase
// Descripción: Implementación de una pila (LIFO) utilizando nodos enlazados.
// Funcionalidades principales:
//  - Apilar (push) y desapilar (pop) elementos.
//  - Estructura fundamental para la ejecución del algoritmo de Búsqueda en Profundidad (DFS).

#pragma once

#include <stdexcept>
#include <iostream>
#include "Node.h"
#include "Stack.h"
#include "util.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class LinkedStack : public Stack<E> {
private:
	Node<E>* top;
	int size;

public:
	LinkedStack() {
		size = 0;
		top = nullptr;
	}
	~LinkedStack() {
		clear();
	}

	void push(E element) {
		top = new Node<E>(element, top);
		size++;
	}
	E pop() {
		if (size == 0)
			throw runtime_error("Stack is empty");
		E result = top->element;
		Node<E>* temp = top;
		top = top->next;
		delete temp;
		size--;
		return result;
	}
	//const E& topValue()
	E topValue() {
		if (size == 0)
			throw runtime_error("Stack is empty");
		return top->element;
	}
	void clear() {

		Node<E>* temp;
		while (size > 0) {
			temp = top;
			top = top->next;
			delete temp;
			size--;
		}
	}
	bool isEmpty() const {
		return size == 0;
	}
	int getSize() const {
		return size;
	}
	void print() const {
		Node<E>* temp = top;
		cout << "[ ";
		while (temp != nullptr) {
			cout << temp->element << " ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};

