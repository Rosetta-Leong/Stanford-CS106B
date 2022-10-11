/*
 * CS 106B/X, Marty Stepp
 * This header declares the ArrayStack class and its members.
 * A ArrayStack encapsulates the list methods from previous lectures
 * into an object that keeps track of the front of the list.
 * See ArrayStack.cpp for the implementation of the methods.
 */

#ifndef _arraystack_h
#define _arraystack_h

#include <iostream>
using namespace std;

template <typename T>
class ArrayStack {
public:
    /* Constructs a new empty stack. */
    ArrayStack();

    /* Destructor */
    ~ArrayStack();
    
    // member functions (methods)
    
    /* Adds the given element on top of the stack. */
    void push(T n);
    
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
    bool isEmpty();

    template <typename U>
    friend ostream& operator <<(ostream& out, const ArrayStack<U> & stack);

private:
    // member variables (instance variables / fields)
    T *_array;
    int _size;
    int _capacity;
};

template <typename T>
ArrayStack<T>::ArrayStack() {
    _size = 0;
    _capacity = 10;
    _array = new T[_capacity];
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] _array;
}

template <typename T>
void ArrayStack<T>::push(T n) {
    // Check if size exceeds capacity
    _array[_size] = n;
    _size++;
}

template <typename T>
T ArrayStack<T>::pop() {
    T lastElement = _array[_size - 1];
    _size--;
    return lastElement;
}

template <typename T>
T ArrayStack<T>::peek() const {
    return _array[_size - 1];
}

template <typename T>
bool ArrayStack<T>::isEmpty() {
    return _size == 0;
}

template <typename T>
ostream & operator << (ostream & out, const ArrayStack<T> & stack) {
    out << "{ ";
    for (int i = 0; i < stack._size; i++) {
        out << stack._array[i] << " ";
    }
    out << "}";
    return out;
}

#endif // _arraystack_h
