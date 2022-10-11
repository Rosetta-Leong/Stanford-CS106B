/*
 * CS 106B/X, Ashley Taylor, adapted from Marty Stepp
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

int dice_main() {
    cout << "diceSum:" << endl;
    diceSum(3, 7);
    
    return 0;
}

/*
 * Prints all possible outcomes of rolling the given
 * number of six-sided dice that add up to exactly the given
 * desired sum, in {#, #, #} format.
 */
void diceSum(int dice, int desiredSum) {
    // TODO
}
