/*
 * CS 106B/X, Marty Stepp
 * This file contains the declaration of the HashIntSet class, which implements
 * a set of integers using a hash table.
 * The hash table uses separate chaining (a linked list of values in each
 * hash bucket) to resolve hash collisions.
 * See HashIntSet.cpp for the implementation of each member.
 */

#ifndef _hashintset_h
#define _hashintset_h

#include <iostream>
#include <string>

/*
 * A HashNode stores a single integer of data and a link to another node.
 */
struct HashNode {
    int data;
    HashNode* next;
    
    HashNode(int data = 0, HashNode* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

class HashIntSet {
public:
    /* Constructs a new empty set. */
    HashIntSet();

    /* Frees the memory allocated by the set. */
    ~HashIntSet();

    /*
     * Adds the given element to the set, if not already present.
     * If the value is already in the set, has no effect.
     */
    void add(int value);

    /* Returns true if the given value is contained in the set. */
    bool contains(int value) const;
    
    /*
     * Returns ratio of size to capacity.
     * Used to decide when to rehash.
     */
    double loadFactor() const;

    /* Prints the hash table contents in detail for debugging. */
    void printStructure() const;

    /*
     * Removes the given value from the set, if it was contained.
     * If the value is not in the set, has no effect.
     */
    void remove(int value);
    
    /* Returns the number of elements in the set. */
    int size() const;

private:
    // int[]  ==> int*
    // HashNode*[] ==> HashNode**
    HashNode** hashTable;
    int capacity;
    int mysize;

    /*
     * Returns an integer index at which the given integer can be stored in
     * the set's hash table array.
     */
    int getIndex(int value) const;
    
    /* Resizes the internal array to one twice as large. */
    void rehash();
};

#endif
