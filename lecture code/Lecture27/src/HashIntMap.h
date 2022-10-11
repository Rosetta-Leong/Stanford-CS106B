/*
 * CS 106B/X, Marty Stepp
 * This file contains the declaration of the HashIntMap class, which implements
 * a map of integers to integers using a hash table.
 * The hash table uses separate chaining (a linked list of values in each
 * hash bucket) to resolve hash collisions.
 * See HashIntMap.cpp for the implementation of each member.
 */

#ifndef _hashintmap_h
#define _hashintmap_h

#include <iostream>
#include <string>

/*
 * A HashMapNode stores a single integer of data and a link to another node.
 */
struct HashMapNode {
    int key;
    int value;
    HashMapNode* next;
    
    HashMapNode(int key = 0, int value = 0, HashMapNode* next = nullptr) {
        this->key = key;
        this->value = value;
        this->next = next;
    }
};

class HashIntMap {
public:
    /* Constructs a new empty map. */
    HashIntMap();

    /* Frees the memory allocated by the map. */
    ~HashIntMap();

    /* Removes all pairs from the map. */
    void clear();

    /* Returns true if the given key is part of a pair contained in the map. */
    bool containsKey(int key) const;
    
    /*
     * Returns the value associated with the given key,
     * or a default value of 0 if the given key is not
     * part of a pair contained in the map.
     */
    int get(int key) const;

    /*
     * Returns ratio of size to capacity.
     * Used to decide when to rehash.
     */
    double loadFactor() const;

    /* Prints the hash table contents in detail for debugging. */
    void printStructure() const;

    /*
     * Adds the given pair to the map, if not already present.
     * If the key is already in the map, replaces its value.
     */
    void put(int key, int value);

    /*
     * Removes the given key and its value from the map, if it was contained.
     * If the key is not in the map, has no effect.
     */
    void remove(int key);
    
    /* Returns the number of pairs in the map. */
    int size() const;

private:
    HashMapNode** hashTable;
    int capacity;
    int mysize;

    /*
     * Returns an integer index at which the given integer can be stored in
     * the map's hash table array.
     */
    int hashCode(int key) const;
    
    /* Resizes the internal array to one twice as large. */
    void rehash();
};

#endif
