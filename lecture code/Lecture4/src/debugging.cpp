/*
 * CS 106B/X, Ashley Taylor
 * This program gives practice for effective debugging.
 * It should rotate the image 90 degrees counter-clockwise.
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "strlib.h"
using namespace std;

bool isVowel(char ch) {
    return ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' ||
            ch == 'i' || ch =='I' || ch == 'o' || ch == 'O' ||
            ch == 'u' || ch == 'U';
}

void countStatistics() {

}

void avgScores(string filename = "scores.txt") {
}

int main() {
    countStatistics();
    avgScores();
    return 0;
}
