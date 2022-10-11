/*
 * CS 106B/X, Marty Stepp
 * This file contains the implementation of the HashIntSet class, which implements
 * a set of integers using a hash table.
 * See HashIntSet.h for the declarations of each member.
 */

#include <iostream>
#include <iomanip>
#include "HashIntSet.h"
using namespace std;

// max load before resizing
static const double MAX_LOAD_FACTOR = 0.75;


HashIntSet::HashIntSet() {
    hashTable = new HashNode*[17]();
    mysize = 0;
    capacity = 17;
}

HashIntSet::~HashIntSet() {
    // TODO
}

void HashIntSet::add(int value) {
    // TODO
}

bool HashIntSet::contains(int value) const {
    // TODO

    return false;
}

int HashIntSet::getIndex(int value) const {
    return abs(value) % capacity;
}

double HashIntSet::loadFactor() const {
    return (double) mysize / capacity;
}

void HashIntSet::remove(int value) {
    // TODO

}

int HashIntSet::size() const {
    return mysize;
}

void HashIntSet::rehash() {

}


// provided by instructor for debugging
void HashIntSet::printStructure() const {
    for (int i = 0; i < capacity; i++) {
        cout << "[" << setw(2) << i << "]:";
        HashNode* curr = hashTable[i];
        while (curr != nullptr) {
            cout << " -> " << setw(2) << curr->data;
            curr = curr->next;
        }
        cout << " /" << endl;
    }
    cout << "size = " << mysize << ", load factor = " << loadFactor() << endl;
}
