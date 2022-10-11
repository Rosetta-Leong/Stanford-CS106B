/*
 * CS 106B/X, Marty Stepp
 * This program demonstrates using recursion to draw "fractal" images,
 * which are repeated self-similar patterns based on mathematical functions.
 * This code draws the Cantor Set, a simple horizontal-line-based fractal,
 * as well as the H-tree, a repeated pattern of smaller "H" shaped figures.
 */

#include <cmath>
#include <iostream>
#include <string>
#include "console.h"
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

void boxyFractal(GWindow& gw, int x, int y, int size, int order);
void cantorSet(GWindow& window, int x, int y, int length, int levels);
void kochSnowflake(GWindow& window, int x, int y, int size, int levels);

int main() {
    GWindow window(800, 600);
    window.setWindowTitle("CS 106B Fractals");
    window.setColor("black");

    //boxyFractal(window, 150, 150, 300, 3);

    //cantorSet(window, 50, 50, 700, 8);

    //kochSnowflake(window, 200, 200, 400, 3);

    return 0;
}

void boxyFractal(GWindow& gw, int x, int y, int size, int order) {
    if (order >= 1) {
        // A) here
        boxyFractal(gw, x-size/4, y-size/4, size/2, order-1);
        // B) here
        boxyFractal(gw, x+3*size/4, y+3*size/4, size/2, order-1);
        // C) here
        boxyFractal(gw, x+3*size/4, y-size/4, size/2, order-1);
        // D) here
        boxyFractal(gw, x-size/4, y+3*size/4, size/2, order-1);
        // E) here
    }
}

/*
 * Draws the Cantor Set fractal at the given level of depth on the given window.
 * A level-1 Cantor Set is just a line, and a level-2 set is a line
 * followed by the first third and last third of that line, and so on.
 * Here is a crude text illustration of a level-4 Cantor Set:
 *
 * ---------------------------
 * ---------         ---------
 * ---   ---         ---   ---
 * - -   - -         - -   - -
 *
 * A level-0 or below produces no output.
 */
void cantorSet(GWindow& gw, int x, int y, int length, int levels) {
    // TODO
}


/*
 * Draws the Koch Snowflake fractal at the given level of depth on the given window.
 * A level-1 Koch Snowflake is just a triangle, while level 2 is a triangle
 * with triangular bumps sticking out of each of its sides; and so on.
 */
void kochSnowflake(GWindow& gw, int x, int y, int size, int levels) {
    // TODO
}
