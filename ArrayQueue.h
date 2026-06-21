#pragma once

#include <iostream>
#include <stdexcept>
#include "Queue.h"   

using std::runtime_error;
using std::cout;
using std::endl;

#ifndef DEFAULT_MAX
#define DEFAULT_MAX 100
#endif

template <typename E>
class ArrayQueue : public Queue<E> {
private:
    E* elements;
    int front;
    int back;
    int size;
    int max;

public:
    ArrayQueue(int max = DEFAULT_MAX) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        this->max = max;
        front = back = size = 0;
    }

    ~ArrayQueue() {
        delete[] elements;
    }

    void enqueue(E element) override {
        if (size == max)
            throw runtime_error("Queue is full");
        elements[back] = element;   
        back = (back + 1) % max;
        size++;                     
    }

    E dequeue() override {         
        if (size == 0)
            throw runtime_error("Queue is empty");
        E result = elements[front];
        front = (front + 1) % max;
        size--;
        return result;
    }

    void clear() override {
        front = back = size = 0;    
    }

    bool isEmpty() const override {
        return size == 0;
    }

    int getSize() const override {
        return size;
    }

    void print() const override {
        cout << "[ ";
        for (int i = front; i != back; i = (i + 1) % max) {  
            cout << elements[i];
            if ((i + 1) % max != back)
                cout << ", ";
        }
        cout << " ]" << endl;
    }
};