/**
 * CS 106X Maze Generator/Solver
 *
 * This instructor-provided file contains the implementation of the Maze class.
 * See Maze.h for documentation of each member.
 *
 * @author Marty Stepp
 * @version 2016/10/26
 * - 16au 106X Maze Solver version
 */

#include "Maze.h"
#include "mazegui.h"
#include <iomanip>
#include <sstream>
#define __DONT_ENABLE_GRAPHICAL_CONSOLE
#include "console.h"
#undef __DONT_ENABLE_GRAPHICAL_CONSOLE
#include "strlib.h"

Maze::Maze(const std::string& mazeText) {
    m_delayMS = 0;
    m_consoleOutput = true;
    m_graphicalOutput = false;
    m_graphicsScaled = false;

    // read data from file; format is
    // # ROWS r
    // # COLS c
    // (r) lines of (c) chars each
    std::istringstream input(mazeText);
    std::string line;
    if (!getline(input, line) || !stringIsInteger(trim(line))) {
        throw "missing # of rows at start of file";
    }
    int rows = stringToInteger(line);
    if (!getline(input, line) || !stringIsInteger(trim(line))) {
        throw "missing # of cols at start of file";
    }
    int cols = stringToInteger(line);
    if (rows < 1 || cols < 1) {
        throw "illegal maze size";
    }
    m_grid.resize(rows, cols);

    // read each line
    for (int row = 0; row < rows; row++) {
        if (!getline(input, line)) {
            throw "missing data for row #" + integerToString(row);
        }

        // repair line length as needed
        line = trim(line);
        if ((int) line.length() > cols) {
            throw "wrong number of characters for row #" + integerToString(row);
        } else {
            // line might end with spaces that were stripped when saving;
            // re-add them if necessary
            while ((int) line.length() < cols) {
                line += " ";
            }
        }

        // store line's contents into grid
        for (int col = 0; col < cols; col++) {
            char ch = line[col];
            if (ch != WALL && ch != OPEN) {
                throw "invalid character in row #"
                        + integerToString(row) + ", col #"
                        + integerToString(col) + ": '" + ch
                        + "' (ASCII " + integerToString(ch) + ")";
            }
            m_grid[row][col] = ch;
        }
    }
}

void Maze::clearMarks() {
    for (int row = 0; row < m_grid.numRows(); row++) {
        for (int col = 0; col < m_grid.numCols(); col++) {
            if (isMarked(row, col)) {
                unmark(row, col);
            } else if (isTainted(row, col)) {
                untaint(row, col);
            }
        }
    }
}

bool Maze::inBounds(int row, int col) const {
    return m_grid.inBounds(row, col);
}

bool Maze::isAnimated() const {
    return m_delayMS > 0;
}

bool Maze::isMarked(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == MARK;
}

bool Maze::isOpen(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == OPEN;
}

bool Maze::isTainted(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == TAINT;
}

bool Maze::isWall(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == WALL;
}

void Maze::mark(int row, int col) {
    checkIndex(row, col);
    if (!isOpen(row, col)) {
        throw "square at row #" + integerToString(row) + ", col #"
                + integerToString(col) + " is not an unmarked open square:\n"
                + toString();
    }
    m_grid[row][col] = MARK;
    if (m_graphicalOutput) {
        if (m_graphicsScaled) {
            // due to weird scaling, only draw odd cells
            if (row % 2 != 0 && col % 2 != 0) {
                checkDelay();
                MazeGUI::mark((row - 1) / 2, (col - 1) / 2);
            }
        } else {
            checkDelay();
            MazeGUI::mark(row, col);
        }
    } else {
        checkDelay();
    }
}

int Maze::numCols() const {
    return m_grid.numCols();
}
int Maze::width() const {
    return m_grid.numCols();
}

int Maze::numRows() const {
    return m_grid.numRows();
}
int Maze::height() const {
    return m_grid.numRows();
}

void Maze::setConsoleOutput(bool output) {
    m_consoleOutput = output;
}

void Maze::setDelay(int ms) {
    if (ms < 0) {
        throw "Illegal delay MS: " + integerToString(ms);
    }
    m_delayMS = ms;
}

void Maze::setGraphicalOutput(bool output) {
    m_graphicalOutput = output;
}

void Maze::setGraphicsScaled(bool scaled) {
    m_graphicsScaled = scaled;
}

// very similar/redundant with mark() implementation
void Maze::taint(int row, int col) {
    checkIndex(row, col);
    if (!isOpen(row, col) && !isMarked(row, col)) {
        throw "square at row #" + integerToString(row) + ", col #"
                + integerToString(col) + " is not an open square:\n"
                + toString();
    }
    m_grid[row][col] = TAINT;
    if (m_graphicalOutput) {
        if (m_graphicsScaled) {
            // due to weird scaling, only draw odd cells
            if (row % 2 != 0 && col % 2 != 0) {
                checkDelay();
                MazeGUI::taint((row - 1) / 2, (col - 1) / 2);
            }
        } else {
            checkDelay();
            MazeGUI::taint(row, col);
        }
    } else {
        checkDelay();
    }
}

std::string Maze::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

void Maze::unmark(int row, int col) {
    checkIndex(row, col);
    if (!isMarked(row, col)) {
        throw "square at row #" + integerToString(row) + ", col #"
                + integerToString(col) + " is not a marked square:\n"
                + toString();
    }
    m_grid[row][col] = OPEN;
    if (m_graphicalOutput) {
        if (m_graphicsScaled) {
            // due to weird scaling, only draw odd cells
            if (row % 2 != 0 && col % 2 != 0) {
                checkDelay();
                MazeGUI::unmark((row - 1) / 2, (col - 1) / 2);
            }
        } else {
            checkDelay();
            MazeGUI::unmark(row, col);
        }
    } else {
        checkDelay();
    }
}

// very similar/redundant with unmark() implementation
void Maze::untaint(int row, int col) {
    checkIndex(row, col);
    if (!isTainted(row, col)) {
        throw "square at row #" + integerToString(row) + ", col #"
                + integerToString(col) + " is not a tainted square:\n"
                + toString();
    }
    m_grid[row][col] = OPEN;
    if (m_graphicalOutput) {
        if (m_graphicsScaled) {
            // due to weird scaling, only draw odd cells
            if (row % 2 != 0 && col % 2 != 0) {
                checkDelay();
                MazeGUI::unmark((row - 1) / 2, (col - 1) / 2);
            }
        } else {
            checkDelay();
            MazeGUI::unmark(row, col);
        }
    } else {
        checkDelay();
    }
}

void Maze::checkDelay() const {
    if (m_delayMS > 0) {
        if (m_consoleOutput) {
            clearConsole();
            std::cout << toString() << std::endl;
            std::cout.flush();
        }
        pause(m_delayMS);
    }
}

void Maze::checkIndex(int row, int col) const {
    if (!inBounds(row, col)) {
        throw "illegal index: row #" + integerToString(row)
                + ", col #" + integerToString(col) + ":\n"
                + toString();
    }
}

std::ostream& operator <<(std::ostream& out, const Maze& maze) {
    // header line with column numbers
    out << "   ";
    for (int c = 0; c < maze.numCols(); c++) {
        out << c % 10;
    }
    out << std::endl;

    for (int r = 0; r < maze.numRows(); r++) {
        // header column with row numbers
        out << std::setw(2) << std::setfill(' ') << std::right << r << " ";

        // chars on each row
        for (int c = 0; c < maze.numCols(); c++) {
            out << maze.m_grid[r][c];
        }
        if (r != maze.numRows() - 1) {
            out << std::endl;
        }
    }
    return out;
}

bool operator ==(const Maze& maze1, const Maze& maze2) {
    return maze1.m_grid == maze2.m_grid;
}

bool operator !=(const Maze& maze1, const Maze& maze2) {
    return maze1.m_grid != maze2.m_grid;
}
