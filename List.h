// Archivo: List.h
// Autores: Hecho en clase
//
// Descripción:
// Interfaz abstracta para estructuras de listas genéricas.
// Define las operaciones básicas que deben implementar las
// distintas estructuras de listas del proyecto.
//
// Funcionalidades principales:
// - Insertar y agregar elementos.
// - Eliminar y obtener elementos.
// - Recorrer la lista.
// - Consultar tamaño y posición.
// - Limpiar y mostrar elementos.
//
// Esta interfaz es implementada por estructuras como ArrayList
// y LinkedList.

#pragma once

template <typename E>
class List {
public:
	List() {}
	List(const List<E>& other) = delete;
	void operator = (const List<E>& other) = delete;
	virtual ~List() {}
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual void setElement(E element) = 0;
	virtual E getElement() = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atStart() const = 0;
	virtual bool atEnd() const = 0;
	virtual int getPos() = 0;
	virtual int getSize() const = 0;
	virtual void print() = 0;
};

