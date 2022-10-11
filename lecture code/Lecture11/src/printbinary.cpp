/*
 * CS 106B/X, Ashley Taylor, adapted from Marty Stepp
 *
 * This program contains examples of printBinary and printDecimal
 * functions that use the "exhaustive search" algorithmic strategy.
 * 
 * The problems in this file focus on generating all binary or base-10
 * numbers with a given number of digits.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "recursion.h"
#include "strlib.h"
using namespace std;

// function prototype declarations
void printAllBinary(int digits);
void printDecimal(int digits);

int main() {
    cout << "printAllBinary(3):" << endl;
    printAllBinary(3);
    cout << endl;
    
//    cout << "printDecimal(2):" << endl;
//    printDecimal(2);
//    cout << endl;

    return 0;
}

/*
 * Prints every binary (base-2) number that has exactly the given number of digits.
 * printBinary(1);
 * 0
 * 1
 *
 * printBinary(2);
 * 00
 * 01
 * 10
 * 11
 *
 * printBinary(3);
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 * 111
 */
void printAllBinary(int digits) {
    // TODO
}

/*
 * Prints every decimal (base-10) number that has exactly the given number of digits.
 */
void printDecimal(int digits) {
    // TODO
    
}
