
// Archivo: Node.h
// Autores: Hecho en clase
// Descripción: Estructura de nodo base para las implementaciones de listas y estructuras enlazadas.
// Funcionalidades principales:
//  - Almacenar el elemento de datos (template genérico).
//  - Mantener un puntero al siguiente nodo en la estructura enlazada.

#pragma once

template <typename E>
class Node {
public:
	E element;
	Node<E>* next;

	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};


