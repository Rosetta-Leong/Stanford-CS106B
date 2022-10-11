/*
 * CS 106B/X, Marty Stepp
 *
 * This program contains examples of functions that use the
 * "recursive backtracking" algorithmic strategy.
 * 
 * The problems in this file focus on rolling/summing a given number of dice.
 */

#include <iostream>
#include "console.h"
#include "exceptions.h"
#include "recursion.h"
#include "vector.h"
using namespace std;

// function prototype declarations
void diceSum(int dice, int desiredSum);

int calls = 0;

int dice_main() {
    cout << "diceSum:" << endl;
    diceSum(3, 7);

    cout << "total calls: " << calls << endl;
    
    return 0;
}

/*
 * Prints all possible outcomes of rolling the given
 * number of six-sided dice that add up to exactly the given
 * desired sum, in {#, #, #} format.
 */
void diceSumHelper(int dice, int desiredSum, Vector<int>& chosen) {
    calls++;
    if (dice == 0) {
        // base case
        if (desiredSum == 0) {
            cout << chosen << endl;
        }
    } else {
        // I will handle 1 die;
        // try all possible values (1-6) to see if they can work
        for (int i = 1; i <= 6; i++) {
            // "choose" i
            chosen.add(i);

            // "explore" what could follow that
            diceSumHelper(dice - 1, desiredSum - i, chosen);

            // "un-choose" i
            chosen.removeBack();
        }
    }
}

void diceSum(int dice, int desiredSum) {
    Vector<int> v;
    diceSumHelper(dice, desiredSum, v);
}
