/*
 * CS 106B/X, Marty Stepp and Julie Zelenski
 * This program demonstrates functions and reference parameters.
 */

#include <iostream>
#include "console.h"
#include "math.h"
#include "simpio.h"
using namespace std;

// function prototype declarations
void swap(int& a, int& b);
void quadratic(double a, double b, double c, double& firstRoot, double& secondRoot);
void nameDiamond(string s);
void testSwap();
void bigGame();

// Swaps the values of integers a and b.
// The a and b parameters are passed by reference,
// so the change will be seen by the caller.
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Finds the roots for the quadratic equation with coefficients a, b, c.
void quadratic(double a, double b, double c, double& firstRoot, double& secondRoot) {
    double discriminant = sqrt(b*b - 4*a*c);
    firstRoot = (-b + discriminant) / (2 * a);
    secondRoot = (-b - discriminant) / (2 * a);
}

// Prints a "diamond" pattern of characters from a string,
// such as:
// K
// Ka
// Kat
// Kate
//  ate
//   te
//    e
void nameDiamond(string s) {
    // print top half of diamond
    for (int i = 1; i <= s.length(); i++) {
        cout << s.substr(0, i) << endl;
    }

    // print bottom half of diamond
    for (int i = 0; i <= s.length(); i++) {
        // prefix with 'i' spaces
        for (int j = 0; j < i; j++) {
            cout << " ";
        }
        cout << s.substr(i) << endl;
    }
}

// Demonstrates the swap function.
void testSwap() {
    int x = 17;
    int y = 35;
    swap(x, y);
    cout << x << "," << y << endl;
}

int main() {
    // test the nameDiamond function
    nameDiamond("Kate");

    double firstRoot;
    double secondRoot;
    quadratic(1, -3, -4, firstRoot, secondRoot);
    cout << "First root: " << firstRoot << " Second root: " << secondRoot << endl;

    // test the swap function
    // testSwap();

    // test the Big Game
    // bigGame();

    return 0;
}

// Simulates the Stanford vs Cal "big game" by prompting
// the user for points scored by each team and then printing
// who won the game.
void bigGame() {
    int stanford = getInteger("Stanford points scored? ");
    int cal = getInteger("Cal points scored? ");
    if (stanford > cal) {
        cout << "Stanford won!" << endl;
    } else if (cal > stanford) {
        cout << "Cal won!" << endl;   // will not be reached
    } else {
        cout << "A tie." << endl;
    }
}
