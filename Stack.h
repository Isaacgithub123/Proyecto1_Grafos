
// Archivo: Stack.h
// Autores: Hecho en clase
// Descripción: Interfaz abstracta para la estructura de datos de pila (LIFO).
// Funcionalidades principales:
//  - Definir operaciones básicas de pila: push, pop, topValue, isEmpty, getSize.
//  - Establecer el contrato para la implementación LinkedStack.

#pragma once

template <typename E>
class Stack {
public:
	Stack() {}
	Stack(const Stack<E>&) = delete;
	void operator=(const Stack<E>&) = delete;
	virtual ~Stack() {}
	virtual void push(E element) = 0;
	virtual E pop() = 0;
	virtual E topValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
	virtual int getSize() const = 0;
	virtual void print() const = 0;
};

