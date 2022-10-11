/**
 * CS 106B/X Maze Generator/Solver
 *
 * Provides the declarations of the Cell and Wall types used in the
 * code base.  See maze-types.cpp for the bodies of the functions.
 *
 * @author Jerry Cain, with modifications by Marty Stepp
 * @version 2016/10/26
 * - 16au 106X Maze Solver version
 * @version 2016/10/20
 * - 16au 106X autograder version
 * @version 2016/10/07
 * - 16au 106X initial version
 */

#ifndef _maze_types_h
#define _maze_types_h

#include <iostream>
#include "hashcode.h"

/**
 * Defines a positive integer coordinate in 2D space, where we
 * (arbitrarily) impose the requirement that (0, 0)
 * is above and/or to the left of all others.
 */
struct Cell {
    int row;
    int col;

    Cell(int r = 0, int c = 0) : row(r), col(c) {
        // empty
    }

    /** Returns a string representation such as "{r04 c15}". */
    std::string toString() const;
};

/**
 * Returns an integer hash code for a cell so that it can be stored
 * in the HashSet or HashMap collections.
 */
int hashCode(const Cell& cell);

/**
 * Relational operators for comparing and ordering cells.
 * These operators also allow cells to be used in a Set or Map collection.
 */
bool operator <(const Cell& one, const Cell& two);
bool operator <=(const Cell& one, const Cell& two);
bool operator >(const Cell& one, const Cell& two);
bool operator >=(const Cell& one, const Cell& two);
bool operator ==(const Cell& one, const Cell& two);
bool operator !=(const Cell& one, const Cell& two);

/**
 * Operator for printing a cell to an output stream.
 */
std::ostream& operator <<(std::ostream& out, const Cell& cell);

/**
 * A wall within a maze is described by the two cells
 * it separates.  It's the responsibility of the programmer
 * to ensure that the two cells are really next to one another,
 * and that the two cells are sensibly ordered.
 */
struct Wall {
    Cell one;
    Cell two;

    Wall() {
        // empty
    }

    Wall(const Cell& first, const Cell& second) : one(first), two(second) {
        // empty
    }

    /** Returns a new wall that is this wall but with its one/two ends flipped. */
    Wall inverse() const {
        return Wall(two, one);
    }

    /** Returns a string representation such as "{{r04 c15} - {r04 c16}}". */
    std::string toString() const;
};

/**
 * Returns an integer hash code for a wall so that it can be stored
 * in the HashSet or HashMap collections.
 */
int hashCode(const Wall& wall);

/**
 * Relational operators for comparing and ordering walls.
 * These operators also allow walls to be used in a Set or Map collection.
 */
bool operator <(const Wall& one, const Wall& two);
bool operator <=(const Wall& one, const Wall& two);
bool operator >(const Wall& one, const Wall& two);
bool operator >=(const Wall& one, const Wall& two);
bool operator ==(const Wall& one, const Wall& two);
bool operator !=(const Wall& one, const Wall& two);

/**
 * Operator for printing a wall to an output stream.
 */
std::ostream& operator <<(std::ostream& out, const Wall& wall);

#endif // _maze_types_h
