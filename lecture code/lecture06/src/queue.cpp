/*
 * CS 106B/X, Ashley Taylor
 * This program demonstrates using the Stack collection class.
 */

#include <iostream>
#include "console.h"
#include "queue.h"
#include "stack.h"
using namespace std;

void repeat(Queue<int> &queue);
void mirror(Queue<string> &queue);

int main() {
    Queue<int> queue = {1, 2, 3};
    cout << "Before repeat: " << queue << endl;
    repeat(queue);
    cout << "After repeat: " << queue << endl;

    Queue<string> q = {"a", "b", "c"};
    cout << "Before mirror: " << q << endl;
    mirror(q);
    cout << "After mirror: " << q << endl;
    return 0;
}

/*
 * Accepts a queue of integers. Replaces every element with two copies of
 * that element.
 */
void repeat(Queue<int> &queue) {
    //TODO
}

/*
 * Accepts a queue of strings. Appends the queue's contents to itself in
 * reverse order.
 */
void mirror(Queue<string> &queue) {
    //TODO
}
