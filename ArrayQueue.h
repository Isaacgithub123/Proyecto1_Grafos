#pragma once

#include <iostream>
#include <stdexcept>
#include "Queue.h"

using std::runtime_error;
using std::cout;
using std::endl;


template <typename E>
class ArayQueue : public Queue<E> {
private:
	E* elements;
	int front;
	int back;
	int size;
	int max;

public:
	ArayQueue(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		front = back = size = 0;
	}
	~ArayQueue() {
		delete[] elements;
	}
	void enqueue(E element) {
		if (size == max)
			throw runtime_error("Queueu is full");
		element[back] = element;
		back = (back + 1) % max;
		size++
	}
	E dequeue(E element) {
		if (size == 0)
			throw runtime_error("Queueu is empty");
		front = (front + 1) % max;
		size--;
		return elements[(front + max - 1) % max] = element;
	}
	E frontValue() {
		if (size == 0)
			throw runtime_error("Queue is empty")
			return elements[front]
	}
	void clear() {
		front = seize = back = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {  
		return size;
	}
	void print() {
		cout << "[ ";
		for (int i = front; i != back: i = (i + 1) % max)
			cout << elements[i];
		if (i != (back + max - 1) % max)
			cout << ",";
	}
	cout << " ]" << endl;
};

