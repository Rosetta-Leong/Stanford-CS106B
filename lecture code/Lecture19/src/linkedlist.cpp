/*
 * CS 106B/X, Ashley Taylor
 * 
 * This program demonstrates several common
 * linked list operations that involve
 * modifying a Linked List.
 */

#include <iostream>
#include "console.h"

using namespace std;

struct ListNode {
    int data;
    ListNode *next;

    ListNode() {
        this->data = 0;
        this->next = nullptr;
    }
    ListNode(int data, ListNode* next) {
        this->data = data;
        this->next = next;
    }
};

void printList(ListNode *front) {
    for (ListNode *ptr = front; ptr != nullptr; ptr = ptr->next) {
        cout << ptr->data << " ";
    }
}

void deleteList(ListNode *front) {
    // TODO
}

void addToFront(int elem, ListNode *&front) {
    // TODO
}

void addToBack(ListNode *front, int elem) {
    // TODO
}

void removeIndex(ListNode *front, int index) {
    // TODO
}


int main() {
    ListNode* front = new ListNode();
    front->data = 42;
    front->next = new ListNode();
    front->next->data = -3;
    front->next->next = new ListNode();
    front->next->next->data = 17;
    front->next->next->next = nullptr;
    printList(front);
    addToFront(18, front);
    cout << "added 18 to front: " << endl;
    printList(front);
//    addToBack(front, 13);
//    cout << endl << endl << "added 13 to back" << endl;
//    printList(front);
//    removeIndex(front, 2);
//    cout << endl << endl << "removed index 2" << endl;
//    printList(front);
//    deleteList(front);
    return 0;
}
