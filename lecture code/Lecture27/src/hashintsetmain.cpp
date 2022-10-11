/*
 * CS 106B/X, Marty Stepp
 * This client program tests the HashIntSet class.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "HashIntSet.h"
using namespace std;

// function prototype declarations
void test_add(HashIntSet& set, int value, bool pauseAfter = true);
void test_contains(HashIntSet& set, int value, bool expected, bool pauseAfter = true);
void test_remove(HashIntSet& set, int value, bool pauseAfter = true);

int main() {
    // create an initial set state
    int elements[16] = {17, 41, 9, 29, 41, 9, 29, 37, 81, 69, 20, 42, 55, 25, 5, -15};
    int notfound[5] = {87, -3, -1, 7, 0};

    cout << "add:" << endl;
    HashIntSet set;
    for (int n : elements) {
        test_add(set, n, /* pauseAfter */ true);
    }
    cout << endl;

    // call various functions on the set
    cout << "contains:" << endl;
    for (int n : elements) {
        test_contains(set, n, true, /* pauseAfter */ true);
    }
    for (int n : notfound) {
        test_contains(set, n, false, /* pauseAfter */ true);
    }
    cout << endl;

    // test remove function
    cout << "remove:" << endl;
    int elementsToRemove[7] = {37, 81, 17, 17, 9, -20, 35};
    for (int n: elementsToRemove) {
        test_remove(set, n, /* pauseAfter */ true);
    }

    int elementsAfterRemove[8] = {41, 29, 69, 42, 55, 25, 5, -15};
    for (int n : elementsAfterRemove) {
        test_contains(set, n, /* pauseAfter */ true);
    }

    return 0;
}

/*
 * Tests the hash set's add function.
 */
void test_add(HashIntSet& set, int value, bool pauseAfter) {
    clearConsole();
    cout << "  add " << setw(2) << value << " (before):" << endl;
    set.printStructure();
    if (pauseAfter) {
        getLine();
        clearConsole();
    }
    cout << "  add " << setw(2) << value << " (after):" << endl;
    set.add(value);
    set.printStructure();
    if (pauseAfter) getLine();
}

/*
 * Tests the hash set's contains function.
 */
void test_contains(HashIntSet& set, int value, bool expected, bool pauseAfter) {
    clearConsole();
    cout << "  contains " << setw(2) << value << ": \t ";
    bool result = set.contains(value);
    cout << (result ? "true" : "false");
    if (expected != result) {
        cout << " \t (FAIL)";
    }
    cout << endl;
    set.printStructure();
    if (pauseAfter) getLine();
}

/*
 * Tests the hash set's remove function.
 */
void test_remove(HashIntSet& set, int value, bool pauseAfter) {
    clearConsole();
    cout << "  remove " << setw(2) << value << " (before):" << endl;
    set.printStructure();
    if (pauseAfter) {
        getLine();
        clearConsole();
    }
    cout << "  remove " << setw(2) << value << " (after):" << endl;
    set.remove(value);
    set.printStructure();
    if (pauseAfter) getLine();
}
