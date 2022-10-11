/*
 * This header declares the GeneralStack class and its members.
 * It also includes the implementation.
 * It's a template version of the ArrayStack we did in class,
 * and it demonstrates how to create a template class in C++.
 */

#ifndef _generalstack_h
#define _generalstack_h

#include <iostream>
using namespace std;

// definition
template<typename T>
class GeneralStack {
public:
    /* Constructs a new empty stack. */
    GeneralStack();

    /* Destructor */
    ~GeneralStack();
    
    // member functions (methods)
    
    /* Adds the given element on top of the stack. */
    void push(T elem);
    
    /*
     * Removes and returns the top element from the stack.
     * Throws a string exception if the stack is empty.
     */
    T pop();
    
    /*
     * Returns the top element from the stack without removing it.
     * Throws a string exception if the stack is empty.
     */
    T peek() const;
    
    /* Returns true if the stack contains no elements. */
    bool isEmpty() const;

private:
    int size;
    T *elements;
    int capacity;
    
    /* Helper to resize the array if necessary when pushing */
    void resize();
};

// implementation
template<typename T>
GeneralStack<T>::GeneralStack() {
    elements = new T[10];
    size = 0;
    capacity = 10;
}

template<typename T>
GeneralStack<T>::~GeneralStack() {
    delete[] elements;
}

template<typename T>
void GeneralStack<T>::push(T elem) {
    size++;
    if (size == capacity) {
        resize();
    }
    elements[size - 1] = elem;
}

template<typename T>
T GeneralStack<T>::pop() {
    if (isEmpty()) {
        throw "Cannot peek on an empty stack";
    }
    size--;
    return elements[size];
}

template<typename T>
T GeneralStack<T>::peek() const {
    if (isEmpty()) {
        throw "Cannot peek on an empty stack";
    }
    return elements[size - 1];
}

template<typename T>
bool GeneralStack<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void GeneralStack<T>::resize() {
    capacity *= 2;
    T *newElements = new T[capacity];
    for (int i = 0; i < size; i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}

#endif // _generalstack_h
