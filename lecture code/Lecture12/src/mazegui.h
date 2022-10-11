/**
 * CS 106B/X Maze Generator/Solver
 *
 * Provides the declarations of the graphics routines needed to help animate
 * the construction of a maze.
 * See mazegui.cpp for the bodies of each static member function.
 *
 * @author Marty Stepp, based on previous maze-graphics.cpp by Jerry Cain
 * @version 2016/10/26
 * - 16au 106X Maze Solver version
 * @version 2016/10/20
 * - 16au 106X autograder version
 * @version 2016/10/07
 * - 16au 106X initial version for Maze Generator
 */

#ifndef _mazegui_h
#define _mazegui_h

#include <string>
#include "ginteractors.h"
#include "gwindow.h"
#include "hashset.h"
#include "linkedhashset.h"
#include "linkedlist.h"
#include "set.h"
#include "vector.h"
#include "mazetypes.h"

class MazeGUI {
public:
    /** Default starting number of rows and columns. */
    static const int MAZE_DEFAULT_ROWS_COLS = 10;

    /** Maximum number of rows and columns. */
    static const int MAZE_MAX_ROWS_COLS = 50;

    /** Minimum number of rows and columns. */
    static const int MAZE_MIN_ROWS_COLS = 2;

    /**
     * Gives a colored background to a cell.
     */
    static void colorCell(const Cell& cell, int color);

    /**
     * Draws the given wall on the maze.
     */
    static void drawWall(const Wall& wall);

    /**
     * Handles events in the GUI window.
     * Not to be called by students.
     */
    static void eventLoop();

    /**
     * Returns all cells of the maze as a vector.
     */
    static const Vector<Cell>& getAllCells();

    /**
     * Returns all walls of the maze as a vector.
     */
    static const Vector<Wall>& getAllWalls();

    /**
     * Returns the number of columns of the maze.
     */
    static int getNumCols();

    /**
     * Returns the number of rows of the maze.
     */
    static int getNumRows();

    /**
     * Returns the number of rows or columns of the square maze.
     */
    static int getNumRowsCols();

    /**
     * Returns true if the given (row, col) index is within the bounds of
     * this maze, from (0, 0) through (size - 1, size - 1) inclusive.
     */
    static bool inBounds(int row, int col);
    static bool inBounds(const Cell& cell);
    static bool inBounds(const Wall& wall);

    /**
     * Sets up the GUI and makes the window appear on screen.
     * Should be called once at program startup.
     */
    static void initialize();

    /**
     * Returns true if the Animation checkbox is checked.
     */
    static bool isAnimated();

    /**
     * Draws a marking on the given row/column location.
     */
    static void mark(int row, int col);

    /**
     * Removes the given wall from the GUI, if present.
     */
    static void removeWall(const Wall& wall);

    /**
     * Instructs the GUI to redraw itself.
     * Clients generally do not need to ever call this.
     */
    static void repaint();

    /**
     * Tells the GUI to display the number of rows and columns as typed into
     * the text box at the top of the window.
     */
    static void resize();

    /**
     * Tells the GUI to display the given number of rows and columns.
     */
    static void resize(int numRowsCols);
    static void resize(int numRows, int numCols);

    /**
     * Saves a screenshot of the GUI to the given filename.
     */
    static void screenshot(const std::string& filename);

    /**
     * Turns on/off animation delay when removing walls.
     */
    static void setAnimated(bool animated = true);

    /**
     * Turns the GUI on/off.
     * Generally clients should not need to call this method, but we have
     * included it to facilitate grading scripts and other private features.
     */
    static void setEnabled(bool enabled = true);

    /**
     * Shuts down the GUI and closes the window.
     * Clients generally do not need to call this.
     */
    static void shutdown();

    /**
     * Tells the GUI to begin generating a new maze.
     */
    static void startMazeGeneration();

    /**
     * Draws a "tainted" marking on the given row/column location.
     */
    static void taint(int row, int col);

    /**
     * Removes a marking on the given row/column location.
     */
    static void unmark(int row, int col);


    /// BEGIN AUTOGRADER-ONLY METHODS; NOT TO BE CALLED BY STUDENTS ///

    /**
     * Gives all cells of the maze a colored background based on whether
     * they can reach each other.
     * Cells that are in the same chamber (that can reach each other) are
     * given the same color as each other.
     */
    static int colorAllCells();

    /**
     * Returns the count of how many walls have been removed.
     */
    static int getWallsRemovedCount();

    /**
     * Returns a set of which walls have been removed.
     */
    static const Set<Wall>& getWallsRemoved();

    /**
     * Enables/disables 'strict' mode, where if you pass invalid args such as
     * out-of-bounds indexes or walls that have already been removed, it will
     * throw an error exception.
     */
    static void setStrict(bool strict = true);

    /**
     * Enables/disables whether the GUI will internally track a set of all walls
     * that have been removed.
     */
    static void setTrackWallsRemoved(bool track = true);

    /// END AUTOGRADER-ONLY METHODS; NOT TO BE CALLED BY STUDENTS ///

private:
    /*
     * Private constructor prevents client construction.
     * This class is meant to be accessed via static methods.
     */
    MazeGUI();

    /* Creates Cell objects for all rows and columns in the maze. */
    static void buildAllCells(int numRows, int numCols);

    /* Creates Wall objects between all rows and columns in the maze. */
    static void buildAllWalls(int numRows, int numCols);

    /* Helper function to color a cell and its reachable neighbors. */
    static void colorHelper(const Set<Wall>& walls, Set<Cell>& colored,
                            const Cell& cell, int color);

    /* Converts a generated maze into the format used by our input text files. */
    static std::string convertMazeToFileFormat();

    /* Draws a border around the confines of the maze. */
    static void drawBorder();

    /* Draws a line of the given color and thickness between the two given points. */
    static void drawColoredLine(double startx, double starty, double endx, double endy,
                                double lineWidth, int color);

    /* Draws the given wall on the maze in the given color and the given amount of spacing. */
    static void drawWall(const Wall& w, int color, double inset);

    /* Draws all walls in the given vector. */
    static void drawWalls(const Vector<Wall>& walls);

    /* Returns the maze's size in pixels. */
    static double getMazeSize();

    /* Processes a single mouse event on the given cell in the window. */
    static void handleMouseMove(int row, int col);

    /* Processes a single mouse event on the given cell in the window. */
    static void handleMousePress(int row, int col);

    /* Helper to add/remove a marking on the given row/column location. */
    static void markHelper(int row, int col, int color);

    /* Reads a maze from a text file in a particular format. */
    static void readMazeFromFile(const std::string& filename);

    /* Displays a status label in the bottom of the GUI window. */
    static void setStatus(const std::string& text, bool echo = true);

    /**
     * Global constants that help provide more
     * meaningful names for what will otherwise be
     * magic values.
     */
    static const int ANIMATION_DELAY_MS = 100;
    static const int WINDOW_WIDTH  = 700;      // w/h of window in pixels
    static const int WINDOW_HEIGHT = 500;
    static const int WALL_WIDTH = 2;           // 2px thick wall lines
    static const int RANDOM_SEED = 106;        // set < 0 for truly random stuff
    static const int WALL_COLOR  = 0x0000ff;   // color of walls in maze
    static const int BLANK_COLOR = 0xffffff;   // color of blank area behind walls
    static const int MARK_COLOR  = 0xdd2020;   // color of escape markings
    static const int TAINT_COLOR  = 0xdddddd;  // color of tainted markings
    static const bool MAZE_SOLVER_ENABLED = true;
    static const bool CONSOLE_OUTPUT = false;
    static const std::string WINDOW_TITLE;     // window title text

    /* private internal data; clients should not use/modify these */
    static GButton* resizeButton;
    static GButton* generateButton;
    static GButton* loadButton;
    static GCheckBox* animation;
    static GLabel* statusLabel;
    static GTextField* rowsColsField;
    static GWindow* window;
    static Vector<Cell> allCells;
    static Vector<Wall> allWalls;
    static Set<Wall> allWallsRemoved;
    static double wallLength;
    static double ulx;
    static double uly;
    static int numRows;
    static int numCols;
    static int wallsRemoved;
    static bool animated;
    static bool isEnabled;
    static bool isStrict;
    static bool isTrackWallsRemoved;
    static std::string mazeFile;
}; // class MazeGUI

#endif // _mazegui_h
