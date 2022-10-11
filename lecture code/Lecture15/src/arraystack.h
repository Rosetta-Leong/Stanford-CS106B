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

class ArrayStack {
public:
    /* Constructs a new empty stack. */
    ArrayStack();
    
    // member functions (methods)
    
    /* Adds the given element on top of the stack. */
    void push(int n);
    
    /*
     * Removes and returns the top element from the stack.
     * Throws a string exception if the stack is empty.
     */
    int pop();
    
    /*
     * Returns the top element from the stack without removing it.
     * Throws a string exception if the stack is empty.
     */
    int peek();
    
    /* Returns true if the stack contains no elements. */
    bool isEmpty();
    
    /* Returns a text representation of the stack. */
    string toString();

private:
    // member variables (instance variables / fields)
};

#endif // _arraystack_h
