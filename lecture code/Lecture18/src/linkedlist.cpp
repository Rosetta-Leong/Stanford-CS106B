/*
 * 
 * This program demonstrates iterating through a Linked List.
 */

#include <iostream>
#include "console.h"

using namespace std;

struct ListNode {
    int data;
    ListNode *next;
};

void printList(ListNode *front) {
    // TODO
}


int main() {
    ListNode* front = new ListNode();
    front->data = 42;
    front->next = new ListNode();
    front->next->data = -3;
    front->next->next = new ListNode();
    front->next->next->data = 17;
    printList(front);
    return 0;
}
