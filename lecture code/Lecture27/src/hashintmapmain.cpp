/*
 * CS 106B/X, Marty Stepp
 * This client program tests the HashIntMap class.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "HashIntMap.h"
using namespace std;

// function prototype declarations
void test_containsKey(HashIntMap& map, int key, bool expected, bool pauseAfter = true);
void test_get(HashIntMap& map, int key, int valueExpected, bool pauseAfter = true);
void test_put(HashIntMap& map, int key, int value, bool pauseAfter = true);
void test_remove(HashIntMap& map, int key, bool pauseAfter = true);

int main_map() {
    // create an initial set state
    const int LEN = 16;
    int keys[LEN]    = {17, 41, 9, 29, 41, 9, 29, 37, 81, 69, 20, 42, 55, 25, 5, -15};
    int values[LEN]  = {17, 41, 9, 29, 41, 9, 29, 37, 81, 69, 20, 42, 55, 25, 5, -15};
    int notfound[5]  = {87, -3, -1, 7, 0};

    cout << "put:" << endl;
    HashIntMap map;
    for (int i = 0; i < LEN; i++) {
        test_put(map, keys[i], values[i], /* pauseAfter */ true);
    }
    cout << endl;

    // call various functions on the set
    cout << "containsKey:" << endl;
    for (int n : keys) {
        test_containsKey(map, n, true, /* pauseAfter */ true);
    }
    for (int n : notfound) {
        test_containsKey(map, n, false, /* pauseAfter */ true);
    }
    cout << endl;

    cout << "get:" << endl;
    for (int i = 0; i < LEN; i++) {
        test_get(map, keys[i], values[i], /* pauseAfter */ true);
    }
    for (int n : notfound) {
        test_get(map, n, 0, /* pauseAfter */ true);
    }
    cout << endl;

    // test remove function
    cout << "remove:" << endl;
    int elementsToRemove[7] = {37, 81, 17, 17, 9, -20, 35};
    for (int n: elementsToRemove) {
        test_remove(map, n, /* pauseAfter */ true);
    }

    int elementsAfterRemove[8] = {41, 29, 69, 42, 55, 25, 5, -15};
    for (int n : elementsAfterRemove) {
        test_containsKey(map, n, /* pauseAfter */ true);
    }

    return 0;
}

/*
 * Tests the hash map's add function.
 */
void test_put(HashIntMap& map, int key, int value, bool pauseAfter) {
    clearConsole();
    cout << "  put " << setw(2) << key << ":" << value << " (before):" << endl;
    map.printStructure();
    if (pauseAfter) {
        getLine();
        clearConsole();
    }
    cout << "  put " << setw(2) << key << ":" << value << " (after):" << endl;
    map.put(key, value);
    map.printStructure();
    if (pauseAfter) getLine();
}

/*
 * Tests the hash map's contains function.
 */
void test_containsKey(HashIntMap& map, int key, bool expected, bool pauseAfter) {
    clearConsole();
    cout << "  containsKey " << setw(2) << key << ": \t ";
    bool result = map.containsKey(key);
    cout << (result ? "true" : "false");
    if (expected != result) {
        cout << " \t (FAIL)";
    }
    cout << endl;
    map.printStructure();
    if (pauseAfter) getLine();
}

/*
 * Tests the hash map's get function.
 */
void test_get(HashIntMap& map, int key, int valueExpected, bool pauseAfter) {
    clearConsole();
    cout << "  get " << setw(2) << key << ": \t ";
    int value = map.get(key);
    cout << value;
    if (value != valueExpected) {
        cout << " \t (FAIL)";
    }
    cout << endl;
    map.printStructure();
    if (pauseAfter) getLine();
}

/*
 * Tests the hash map's remove function.
 */
void test_remove(HashIntMap& map, int key, bool pauseAfter) {
    clearConsole();
    cout << "  remove " << setw(2) << key << " (before):" << endl;
    map.printStructure();
    if (pauseAfter) {
        getLine();
        clearConsole();
    }
    cout << "  remove " << setw(2) << key << " (after):" << endl;
    map.remove(key);
    map.printStructure();
    if (pauseAfter) getLine();
}
