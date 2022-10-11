/*
 * CS 106B/X, Marty Stepp
 * This file contains the implementation of the HashIntMap class, which implements
 * a set of integers using a hash table.
 * See HashIntMap.h for the declarations of each member.
 */

#include <iostream>
#include <iomanip>
#include "HashIntMap.h"
using namespace std;

// max load before resizing
static const double MAX_LOAD_FACTOR = 0.75;


HashIntMap::HashIntMap() {
    // TODO
}

HashIntMap::~HashIntMap() {
    // TODO
}

bool HashIntMap::containsKey(int key) const {
    // TODO

    return false;
}

int HashIntMap::get(int key) const {
    // TODO

    return 0;
}

void HashIntMap::clear() {
    // TODO

}

int HashIntMap::hashCode(int key) const {
    return abs(key) % capacity;
}

double HashIntMap::loadFactor() const {
    return (double) mysize / capacity;
}

void HashIntMap::put(int key, int value) {
    // TODO
}

void HashIntMap::remove(int key) {
    // TODO

}

int HashIntMap::size() const {
    return mysize;
}

void HashIntMap::rehash() {

}


// provided by instructor for debugging
void HashIntMap::printStructure() const {
    for (int i = 0; i < capacity; i++) {
        cout << "[" << setw(2) << i << "]:";
        HashMapNode* curr = hashTable[i];
        while (curr != nullptr) {
            cout << " -> " << setw(2) << curr->key << ":" << curr->value;
            curr = curr->next;
        }
        cout << " /" << endl;
    }
    cout << "size = " << mysize << ", load factor = " << loadFactor() << endl;
}
