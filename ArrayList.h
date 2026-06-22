#pragma once
#define DEFAULT_MAX 1024
#include "List.h"
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
private:
	E* elements;
	int max;
	int size;
	int pos;

public:
	ArrayList(int max = DEFAULT_MAX) {
		elements = new E[max];
		this->max = max;
		size = 0;
		pos = 0;
	}
	~ArrayList() {
		delete[] elements;
	}
	void insert(E element) {
		if (size == max)
			throw runtime_error("List is full.");
		for (int i = size; i > pos; i--) {
			elements[i] = elements[i - 1];
		}
		elements[pos] = element;
		size++;
	}
	void append(E element) {
		if (size == max)
			throw runtime_error("List is full.");
		elements[size] = element;
		size++;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (pos == size)
			throw runtime_error("No current element.");
		E result = elements[pos];
		for (int i = pos + 1; i < size; i++) {
			elements[i - 1] = elements[i];
		}
		size--;
		return result;
	}
	void clear() {
		size = pos = 0;

	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (pos == size)
			throw runtime_error("No current element. ");
		return elements[pos];
	}
	void setElement(E element) {
		if (pos == size)
			throw runtime_error("No current element.");
		elements[pos] = element;
	}

	void goToStart() {
		pos = 0;
	}
	void goToEnd() {
		pos = size;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds. ");
		this->pos = pos;
	}
	void next() {
		if (pos < size)
			pos++;
	}
	void previous() {
		if (pos > 0)
			pos--;
	}
	bool atStart() const {
		return pos == 0;
	}
	bool atEnd() const {
		return pos == size;
	}
	int getPos() {
		return pos;
	}
	int getSize() const {
		return size;
	}
	void print() {
	}
};