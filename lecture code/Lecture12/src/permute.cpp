/*
 * CS 106B/X, Marty Stepp
 *
 * This program contains an example of a permute function
 * that uses the "exhaustive search" algorithmic strategy.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "recursion.h"
#include "set.h"
#include "vector.h"
using namespace std;

// function prototype declarations
void permute(Vector<string>& v);

int permute_main() {
    cout << "testing the permute function:" << endl;
    Vector<string> v {"a", "b", "b", "a", "c"};    // {"M", "A", "R", "T", "Y"};
    permute(v);

    return 0;
}

// {a,b,c,d}
void permuteHelper(Vector<string>& v, Vector<string>& chosen,
                   Set<Vector<string>>& printed) {
}

/*
 * Prints all possible rearrangements of the strings of the given vector.
 * For example, if the vector stores {M,A,R,T,Y}, prints {MYRAT}, {TRAYM}, {RTYMA}, ...
 */
void permute(Vector<string>& v) {
    Vector<string> chosen;
    Set<Vector<string>> printed;
    permuteHelper(v, chosen, printed);
}
