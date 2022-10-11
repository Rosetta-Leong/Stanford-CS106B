/*
 * CS 106B/X, Marty Stepp
 * This program demonstrates the use of the Stanford C++ Grid class.
 * It is similar to a 2-dimensional array but with more features.
 * Here we use it to represent an 8x8 chess board and look for legal moves.
 */

#include <iostream>
#include <cmath>
#include "console.h"
#include "grid.h"
using namespace std;

/*
 * Returns true if the given square (r1, c1) represents a Knight on a
 * chess board that can move to square (r2, c2) successfully.
 * Knights move in a 2-by-1 pattern or an "L" shape.
 * The (r1, c1) must contain the string "knight" and (r2, c2) must
 * be an empty square, and both squares must be within bounds of the
 * board, otherwise false is returned.
 */
bool knightCanMove(const Grid<string>& board,
                   int r1, int c1, int r2, int c2) {
    return false;
}

/*
 * Code below is to test the knightCanMove function.
 */
void test(const Grid<string>& board, int r1, int c1, int r2, int c2, bool expected = false);

int mainGrid() {
    Grid<string> board(8, 8);
    board[1][2] = "knight";
    board[0][4] = "king";
    board[3][1] = "rook";
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            if (board[r][c] == "") {
                cout << "?" << "\t";
            } else {
                cout << board[r][c] << "\t";
            }
        }
        cout << endl;
    }
    
    
    test(board, 1, 2, 0, 0, true);
    test(board, 1, 2, 0, 1);
    test(board, 1, 2, 0, 4);
    test(board, 1, 2, 1, 4);
    test(board, 1, 2, 2, 4, true);
    test(board, 1, 2, 3, 4);
    test(board, 1, 2, 3, 3, true);
    test(board, 1, 2, 3, 1);
    test(board, 1, 2, 2, 0, true);
    test(board, 1, 2, -1, 1);
    test(board, 1, 2, 2, 8);
    return 0;
}

/*
 * Performs one test call of the knightCanMove function.
 */
void test(const Grid<string>& board, int r1, int c1, int r2, int c2, bool expected) {
    cout << "knight can move (" << r1 << ", " << c1 << "), (" << r2 << ", " << c2 << ")? ";
    bool result = knightCanMove(board, r1, c1, r2, c2);
    cout << (result ? "true" : "false");
    if (result == expected) {
        cout << "\t pass.";
    } else {
        cout << "\t FAIL!";
    }
    cout << endl;
}
