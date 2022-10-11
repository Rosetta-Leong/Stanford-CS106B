/*
 * CS 106B/X, Marty Stepp
 *
 * This program is a client that uses the ArrayStack class.
 */

#include <iostream>
#include "console.h"
#include "arraystack.h"

int main() {
    ArrayStack<int> stack;

    // add (push) some values onto the stack
    cout << "push tests:" << endl;
    for (int value : {42, -3, 17, 88}) {
        cout << "push:  " << value << endl;
        stack.push(value);
        cout << "after: " << stack << endl;
    }
    cout << endl;

    // remove (pop) values from the stack
    cout << "peek/pop tests:" << endl;
    while (!stack.isEmpty()) {
        cout << "peek:  " << stack.peek() << endl;
        cout << "pop:   " << stack.pop() << endl;
        cout << "after: " << stack << endl;
    }

    std::string hello = "hello";

    return 0;
}
