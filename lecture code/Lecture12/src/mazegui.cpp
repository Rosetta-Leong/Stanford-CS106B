/**
 * CS 106B/X Maze Generator/Solver
 *
 * Provides the implementation of the graphics routines needed to help animate
 * the construction of a maze.
 * This file also contains the 'main' function to run the project.
 *
 * @author Marty Stepp, based on previous maze-graphics.cpp by Jerry Cain
 * @version 2018/01/31
 * - small changes for CS 106B lecture; removed generate buttons
 * @version 2016/10/28
 * - isFile -> fileExists bug fix for Windows systems
 * @version 2016/10/26
 * - 16au 106X Maze Solver version
 * @version 2016/10/20
 * - 16au 106X autograder version
 * @version 2016/10/12
 * - made GUI window resizable as workaround for some sizing issues on Mac
 * @version 2016/10/07
 * - 16au 106X initial version
 */

#include "mazegui.h"
#include <iomanip>
#include <iostream>
#include <string>
#include "filelib.h"
#include "gevents.h"
#include "gfilechooser.h"
#include "gobjects.h"
#include "linkedhashset.h"
#include "strlib.h"
#include "timer.h"
#include "Maze.h"


// define static constants and variables
const std::string MazeGUI::WINDOW_TITLE = "CS 106B/X Maze Solver";
GButton* MazeGUI::resizeButton = nullptr;
GButton* MazeGUI::generateButton = nullptr;
GButton* MazeGUI::loadButton = nullptr;
GCheckBox* MazeGUI::animation = nullptr;
GLabel* MazeGUI::statusLabel = nullptr;
GTextField* MazeGUI::rowsColsField = nullptr;
GWindow* MazeGUI::window = nullptr;
Vector<Cell> MazeGUI::allCells;
Vector<Wall> MazeGUI::allWalls;
Set<Wall> MazeGUI::allWallsRemoved;
double MazeGUI::ulx = 0;
double MazeGUI::uly = 0;
double MazeGUI::wallLength = 0;
int MazeGUI::numRows = 0;
int MazeGUI::numCols = 0;
int MazeGUI::wallsRemoved = 0;
bool MazeGUI::animated = true;
bool MazeGUI::isEnabled = true;
bool MazeGUI::isStrict = false;
bool MazeGUI::isTrackWallsRemoved = false;
std::string MazeGUI::mazeFile;

// forward declaration of student's code
extern void generateMaze();                      // written by you, in previous assignment
bool escapeMaze(Maze& maze, int row, int col);   // written by you, in mazesolver.cpp

// define static member functions
void MazeGUI::buildAllCells(int numRows, int numCols) {
    allCells.clear();
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            Cell cell(row, col);
            allCells.add(cell);
        }
    }
}

void MazeGUI::buildAllWalls(int numRows, int numCols) {
    allWalls.clear();
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols - 1; col++) {
            Cell base(row, col);
            Cell eastNeighbor(row, col + 1);
            Wall eastWall(base, eastNeighbor);
            allWalls.add(eastWall);
        }
    }

    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows- 1; row++) {
            Cell base(row, col);
            Cell northNeighbor(row + 1, col);
            Wall northWall(base, northNeighbor);
            allWalls.add(northWall);
        }
    }
    shuffle(allWalls);
}

void MazeGUI::colorCell(const Cell& cell, int color) {
    initialize();
    if (isStrict && !inBounds(cell)) {
        error("MazeGUI::colorCell: Cell out of bounds: " + cell.toString());
    }
    double startx = ulx + cell.col * MazeGUI::wallLength + WALL_WIDTH;
    double starty = uly + cell.row * MazeGUI::wallLength + WALL_WIDTH;
    double size = MazeGUI::wallLength - 2 * WALL_WIDTH;
    window->setColor(color);
    window->fillRect(startx, starty, size, size);
}

std::string MazeGUI::convertMazeToFileFormat() {
    int numRows = MazeGUI::numRows * 2 + 1;
    int numCols = MazeGUI::numCols * 2 + 1;
    Grid<char> mazeChars(numRows, numCols);
    mazeChars.fill(Maze::OPEN);
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (row == 0 || col == 0 || row == numRows - 1 || col == numCols - 1) {
                mazeChars[row][col] = Maze::WALL;
            }
        }
    }

    // entrance and exit
    mazeChars[0][1] = Maze::OPEN;
    mazeChars[numRows - 1][numCols - 2] = Maze::OPEN;

    for (const Wall& wall : allWalls) {
        if (allWallsRemoved.contains(wall)) {
            continue;
        }

        // shift wall indexes and connect to neighboring walls
        int row = wall.one.row * 2 + 1;
        int col = wall.one.col * 2 + 1;
        if (wall.two.row == wall.one.row + 1) {
            // horizontal wall on S edge
            row++;
            mazeChars[row][col] = Maze::WALL;
            mazeChars[row][col - 1] = Maze::WALL;
            mazeChars[row][col + 1] = Maze::WALL;
        } else if (wall.two.row == wall.one.row - 1) {
            // horizontal wall on N edge
            row--;
            mazeChars[row][col] = Maze::WALL;
            mazeChars[row][col - 1] = Maze::WALL;
            mazeChars[row][col + 1] = Maze::WALL;
            if (row >= 2 && (mazeChars[row - 2][col] == Maze::WALL
                             || (col >= 2 && mazeChars[row - 2][col - 2] == Maze::WALL)
                             || (col < numCols - 2 && mazeChars[row - 2][col + 2] == Maze::WALL))) {
                mazeChars[row - 1][col] = Maze::WALL;   // connect wall above
            }
        } else if (wall.two.col == wall.one.col + 1) {
            // vertical wall on E edge
            col++;
            mazeChars[row][col] = Maze::WALL;
            mazeChars[row - 1][col] = Maze::WALL;
            mazeChars[row + 1][col] = Maze::WALL;
        } else if (wall.two.col == wall.one.col - 1) {
            // vertical wall on W edge
            col--;
            mazeChars[row][col] = Maze::WALL;
            mazeChars[row - 1][col] = Maze::WALL;
            mazeChars[row + 1][col] = Maze::WALL;
            if (col >= 2 && (mazeChars[row][col - 2] == Maze::WALL
                             || (row >= 2 && mazeChars[row - 2][col - 2] == Maze::WALL)
                             || (row >= 2 && mazeChars[row - 2][col + 2] == Maze::WALL))) {
                mazeChars[row][col - 1] = Maze::WALL;   // connect wall left
            }
        }
    }
    std::ostringstream out;
    out << numRows << std::endl;
    out << numCols << std::endl;
    out << mazeChars.toString2D("", "", "", "\n") << std::endl;
    return out.str();
}

void MazeGUI::drawBorder() {
    double mazeSize = getMazeSize();
    drawColoredLine(ulx, uly, ulx, uly + mazeSize, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx, uly + mazeSize, ulx + mazeSize - wallLength, uly + mazeSize, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx + mazeSize - wallLength, uly + mazeSize, ulx + mazeSize, uly + mazeSize, WALL_WIDTH, BLANK_COLOR);
    drawColoredLine(ulx + mazeSize, uly + mazeSize, ulx + mazeSize, uly, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx + mazeSize, uly, ulx + wallLength, uly, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx + wallLength, uly, ulx, uly, WALL_WIDTH, BLANK_COLOR);
}

void MazeGUI::drawColoredLine(double startx, double starty, double endx, double endy,
                              double lineWidth, int color) {
    GLine line(startx, starty, endx, endy);
    line.setLineWidth(lineWidth);
    line.setColor(color);
    window->draw(line);
}

void MazeGUI::drawWall(const Wall& wall) {
    if (isStrict && !inBounds(wall)) {
        error("MazeGUI::drawWall: Wall out of bounds: " + wall.toString());
    }
    drawWall(wall, WALL_COLOR, /* inset */ 0);
}

void MazeGUI::drawWall(const Wall& w, int color, double inset) {
    double startx = ulx + w.one.col * MazeGUI::wallLength;
    double starty = uly + w.one.row * MazeGUI::wallLength;

    double wallLength = MazeGUI::wallLength;
    double lineWidth = WALL_WIDTH;
    if (color == BLANK_COLOR) {
        wallLength -= 2 * inset;
        lineWidth += 2;
    }

    if (w.one.row == w.two.row) {
        startx += MazeGUI::wallLength;
        starty += inset;
        drawColoredLine(startx, starty, startx, starty + wallLength, lineWidth, color);
    } else {
        starty += MazeGUI::wallLength;
        startx += inset;
        drawColoredLine(startx, starty, startx + wallLength, starty, lineWidth, color);
    }
}

void MazeGUI::drawWalls(const Vector<Wall>& walls) {
    initialize();
    for (const Wall& wall : walls) {
        drawWall(wall);
    }
    repaint();
}

void MazeGUI::eventLoop() {
    while (true) {
        GEvent event = waitForEvent(ACTION_EVENT | MOUSE_EVENT | WINDOW_EVENT);
        if (event.getEventClass() == ACTION_EVENT) {
            GActionEvent actionEvent(event);
            if (actionEvent.getSource() == resizeButton
                    || actionEvent.getSource() == rowsColsField) {
                resize();
            } else if (actionEvent.getSource() == generateButton) {
                if (!mazeFile.empty()) {
                    // need to get out of file-maze state
                    resize();
                    mazeFile = "";
                }
                startMazeGeneration();
            } else if (actionEvent.getSource() == loadButton) {
                std::string filename = GFileChooser::showOpenDialog("", "*.txt");
                if (filename.empty() || !fileExists(filename)) {
                    continue;
                }
                mazeFile = filename;
                setStatus("Loading maze from " + getTail(mazeFile) + ".");
                readMazeFromFile(mazeFile);
            }
        } else if (event.getEventClass() == MOUSE_EVENT) {
            GMouseEvent mouseEvent(event);
            // calculate row/col that the user clicked on
            int col = (int) ((mouseEvent.getX() - ulx) / MazeGUI::wallLength);
            int row = (int) ((mouseEvent.getY() - uly) / MazeGUI::wallLength);

            if (mouseEvent.getEventType() == MOUSE_PRESSED) {
                handleMousePress(row, col);
            } else if (mouseEvent.getEventType() == MOUSE_MOVED) {
                handleMouseMove(row, col);
            }
        } else if (event.getEventClass() == WINDOW_EVENT) {
            if (event.getEventType() == WINDOW_CLOSED) {
                break;
            }
        }
    }
}

const Vector<Cell>& MazeGUI::getAllCells() {
    return allCells;
}

const Vector<Wall>& MazeGUI::getAllWalls() {
    return allWalls;
}

double MazeGUI::getMazeSize() {
    initialize();
    double w = window->getCanvasWidth() - 20;
    double h = window->getCanvasHeight() - 20;
    return w < h ? w : h;
}

int MazeGUI::getNumCols() {
    return numCols;
}

int MazeGUI::getNumRows() {
    return numRows;
}

int MazeGUI::getNumRowsCols() {
    return numRows;
}

static std::string rowColToString(int row, int col) {
    std::ostringstream out;
    out << "r" << std::setw(2) << std::setfill('0') << row
        << " c" << std::setw(2) << std::setfill('0') << col;
    return out.str();
}

void MazeGUI::handleMouseMove(int row, int col) {
    if (!inBounds(row, col)) {
        return;
    }
    setStatus(rowColToString(row, col), /* echo */ false);
}

void MazeGUI::handleMousePress(int row, int col) {
    if (row < 0 || col < 0) {
        return;
    }

    std::string mazeText;
    if (mazeFile.empty()) {
        // generated maze; convert to Maze object format
        mazeText = convertMazeToFileFormat();
    } else {
        // maze from file
        mazeText = readEntireFile(mazeFile);
    }

    // create a Maze object based on the file or generated maze
    Maze maze(mazeText);
    maze.setConsoleOutput(false);
    maze.setGraphicalOutput(true);
    if (mazeFile.empty()) {
        maze.setGraphicsScaled(true);
    }

    if (CONSOLE_OUTPUT) {
        std::cout << "Maze:\n" << maze << std::endl << std::endl;
    }
    window->repaint();

    if (inBounds(row, col)) {
        // clear past markings
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numCols; c++) {
                unmark(r, c);
            }
        }

        setStatus("Exploring ...");
        if (isAnimated()) {
            maze.setDelay(ANIMATION_DELAY_MS);
        }

        // calls your function
        int origRow = row;
        int origCol = col;
        if (mazeFile.empty()) {
            row = row * 2 + 1;
            col = col * 2 + 1;
        }

        if (CONSOLE_OUTPUT) {
            std::cout << "escapeMaze " << rowColToString(row, col);
            if (mazeFile.empty()) {
                std::cout << " (scaled in Maze; onscreen = "
                          << rowColToString(origRow, origCol) << ")";
            }
            std::cout << " ..." << std::endl;
        }
        bool result = escapeMaze(maze, row, col);

        if (!isAnimated()) {
            window->repaint();
        }
        if (result) {
            setStatus("You escaped!");
            if (CONSOLE_OUTPUT) {
                std::cout << maze << std::endl << std::endl;
            }
        } else {
            setStatus("No escape path was found.");
        }
    }
}

bool MazeGUI::inBounds(int row, int col) {
    return 0 <= row && row < numRows && 0 <= col && col < numCols;
}

bool MazeGUI::inBounds(const Cell& cell) {
    return inBounds(cell.row, cell.col);
}

bool MazeGUI::inBounds(const Wall& wall) {
    return inBounds(wall.one) && inBounds(wall.two);
}

void MazeGUI::initialize() {
    // ensure that this code runs only once
    static bool _initialized = false;
    if (_initialized) {
        return;
    }
    _initialized = true;
    if (RANDOM_SEED > 0) {
        setRandomSeed(RANDOM_SEED);
    }

    // initialize window and graphical interactors
    window = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT, /* visible */ false);
    window->setTitle(WINDOW_TITLE);
    window->setResizable(true);
    window->setRepaintImmediately(false);
    window->setExitOnClose(true);

    rowsColsField = new GTextField(4);
    rowsColsField->setText(integerToString(MAZE_DEFAULT_ROWS_COLS));
    rowsColsField->addActionListener();

    statusLabel = new GLabel("Click on a square to solve the maze!");

    animation = new GCheckBox("Animation?");
    animation->setSelected(true);
    animation->setMnemonic('A');
    resizeButton = new GButton("Resize");
    resizeButton->setMnemonic('R');
    generateButton = new GButton("Generate");
    generateButton->setMnemonic('G');
    loadButton = new GButton("Load ...");
    loadButton->setMnemonic('L');

    // window->addToRegion(rowsColsField, "North");
    // window->addToRegion(resizeButton, "North");
    // window->addToRegion(generateButton, "North");
    if (MAZE_SOLVER_ENABLED) {
        window->addToRegion(loadButton, "North");
    }
    window->addToRegion(animation, "North");
    window->addToRegion(statusLabel, "South");

    if (isEnabled) {
        window->center();
        window->setVisible(true);
        window->center();
    }
}

bool MazeGUI::isAnimated() {
    initialize();
    animated = animation->isSelected();
    return animated;
}

void MazeGUI::mark(int row, int col) {
    markHelper(row, col, MARK_COLOR);
}

void MazeGUI::markHelper(int row, int col, int color) {
    if (!inBounds(row, col)) {
        error("MazeGUI::mark/unmark: r" + integerToString(row) + "c" + integerToString(col)
              + " is out of bounds of " + integerToString(numRows) + "x" + integerToString(numCols)
              + " maze");
    }
    bool marked = color != BLANK_COLOR;
    double fudge = marked ? 0 : 1;   // make 1px larger when whiting out (avoid remnants)
    double markSize = MazeGUI::wallLength / 2 + 2*fudge;
    double startx = ulx + col * MazeGUI::wallLength + markSize/2 - fudge;
    double starty = uly + row * MazeGUI::wallLength + markSize/2 - fudge;
    window->setColor(color);
    if (marked) {
        window->fillOval(startx, starty, markSize, markSize);
    } else {
        // fill as rectangle to overfill the red circle and completely erase it
        window->fillRect(startx, starty, markSize, markSize);
    }
    if (isAnimated()) {
        window->repaint();
    }
}

void MazeGUI::readMazeFromFile(const std::string& filename) {
    std::string fileText = readEntireFile(filename);
    Maze maze(fileText);
    MazeGUI::numRows = maze.numRows();
    MazeGUI::numCols = maze.numCols();
    buildAllCells(maze.numRows(), maze.numCols());

    // don't build ALL walls; build the ones that are present in this maze
    allWalls.clear();
    for (int row = 0; row < maze.numRows(); row++) {
        for (int col = 0; col < maze.numCols(); col++) {
            if (maze.isWall(row, col)) {
                Cell base = { row, col };
                Cell nNeighbor = { row - 1, col };
                Cell sNeighbor = { row + 1, col };
                Cell wNeighbor = { row, col - 1 };
                Cell eNeighbor = { row, col + 1 };

                // have to list N/W-most cell first to draw properly
                Wall nWall = { nNeighbor, base };
                Wall sWall = { base, sNeighbor };
                Wall wWall = { wNeighbor, base };
                Wall eWall = { base, eNeighbor };

                allWalls.add(nWall);
                allWalls.add(sWall);
                allWalls.add(wWall);
                allWalls.add(eWall);
            }
        }
    }
    shuffle(allWalls);

    window->clearCanvas();
    wallLength = getMazeSize() / std::max(maze.numRows(), maze.numCols());
    ulx = (window->getCanvasWidth() - getMazeSize()) / 2;
    uly = (window->getCanvasHeight() - getMazeSize()) / 2;

    drawWalls(allWalls);
}

void MazeGUI::removeWall(const Wall& wall) {
    initialize();
    if (isStrict) {
        if (!inBounds(wall)) {
            error("MazeGUI::removeWall: Wall out of bounds: " + wall.toString());
        }
        if (isTrackWallsRemoved && (allWallsRemoved.contains(wall) || allWallsRemoved.contains(wall.inverse()))) {
            error("MazeGUI::removeWall: Attempt to remove wall twice: " + wall.toString());
        }
    }

    wallsRemoved++;
    if (isTrackWallsRemoved) {
        allWallsRemoved.add(wall);
    }

    drawWall(wall, BLANK_COLOR, wallLength / 5);
    if (isAnimated()) {
        setStatus("Removing wall between " + wall.one.toString() + " and "
                  + wall.two.toString() + ".", /* echo */ false);
        pause(ANIMATION_DELAY_MS);
        window->repaint();
    }
}

void MazeGUI::repaint() {
    initialize();
    if (window) {
        window->repaint();
    }
}

void MazeGUI::resize() {
    initialize();
    if (!rowsColsField) {
        return;
    }

    std::string rowsColsText = rowsColsField->getText();
    if (!stringIsInteger(rowsColsText)) {
        return;
    }
    int numRowsCols = stringToInteger(rowsColsText);
    if (numRowsCols >= MAZE_MIN_ROWS_COLS && numRowsCols <= MAZE_MAX_ROWS_COLS) {
        resize(numRowsCols);
    }
}

void MazeGUI::resize(int numRowsCols) {
    resize(numRowsCols, numRowsCols);
}

void MazeGUI::resize(int numRows, int numCols) {
    if (numRows < MAZE_MIN_ROWS_COLS || numRows > MAZE_MAX_ROWS_COLS
            || numCols < MAZE_MIN_ROWS_COLS || numCols > MAZE_MAX_ROWS_COLS) {
        error("Value passed to MazeGUI::resize is out of range.");
    }

    initialize();
    allCells.clear();
    allWalls.clear();
    allWallsRemoved.clear();
    MazeGUI::numRows = numRows;
    MazeGUI::numCols = numCols;
    resizeButton->setEnabled(false);
    generateButton->setEnabled(false);
    wallsRemoved = 0;
    setStatus("Resizing maze to size " + integerToString(numRows) + " x "
              + integerToString(numCols) + ".");
    window->clearCanvas();
    wallLength = getMazeSize() / std::max(numRows, numCols);
    ulx = (window->getCanvasWidth() - getMazeSize()) / 2;
    uly = (window->getCanvasHeight() - getMazeSize()) / 2;

    buildAllCells(numRows, numCols);
    buildAllWalls(numRows, numCols);

    drawBorder();
    drawWalls(allWalls);
    resizeButton->setEnabled(true);
    generateButton->setEnabled(true);
}

void MazeGUI::screenshot(const std::string& filename) {
    initialize();
    window->saveCanvasPixels(filename);
}

void MazeGUI::setAnimated(bool animate) {
    animated = animate;
    if (animation) {
        animation->setSelected(animated);
    }
}

void MazeGUI::setEnabled(bool enabled) {
    isEnabled = enabled;
}

void MazeGUI::setStatus(const std::string& text, bool echo) {
    initialize();
    statusLabel->setText(text);
    if (CONSOLE_OUTPUT && echo) {
        std::cout << text << std::endl;
    }
}

void MazeGUI::shutdown() {
    if (window) {
        window->setVisible(false);
        window->close();
        delete window;
        delete rowsColsField;
        delete statusLabel;
        delete animation;
        delete resizeButton;
        delete generateButton;
        delete loadButton;
        window = nullptr;
        rowsColsField = nullptr;
        statusLabel = nullptr;
        animation = nullptr;
        resizeButton = nullptr;
        generateButton = nullptr;
        loadButton = nullptr;
    }
}

void MazeGUI::startMazeGeneration() {
    initialize();
    wallsRemoved = 0;
    resizeButton->setEnabled(false);
    generateButton->setEnabled(false);
    mazeFile = "";   // reset memory of last maze file
    setStatus("Generating maze ...");
    Timer timer;
    timer.start();
    // generateMaze();
    timer.stop();
    setStatus("Generation complete. Removed "
              + integerToString(wallsRemoved)
              + " of " + integerToString(allWalls.size())
              + " walls. (took "
              + longToString(timer.elapsed()) + " ms)");
    repaint();
    resizeButton->setEnabled(true);
    generateButton->setEnabled(true);
}

void MazeGUI::taint(int row, int col) {
    markHelper(row, col, TAINT_COLOR);
}

void MazeGUI::unmark(int row, int col) {
    markHelper(row, col, BLANK_COLOR);
}

static bool hasWallBetween(const Set<Wall>& walls, const Cell& cell1, const Cell& cell2) {
    Wall wall1 {cell1, cell2};
    if (walls.contains(wall1)) {
        return true;
    }
    Wall wall2 {cell2, cell1};
    return walls.contains(wall2);
}

void MazeGUI::colorHelper(const Set<Wall>& walls, Set<Cell>& colored, const Cell& cell, int color) {
    if (colored.contains(cell)) {
        return;
    }

    colored.add(cell);
    colorCell(cell, color);

    Vector<Cell> neighbors {
            Cell(cell.row - 1, cell.col),
            Cell(cell.row + 1, cell.col),
            Cell(cell.row, cell.col - 1),
            Cell(cell.row, cell.col + 1)
    };
    for (const Cell& neighbor : neighbors) {
        if (inBounds(neighbor.row, neighbor.col) && !hasWallBetween(walls, cell, neighbor)) {
            colorHelper(walls, colored, neighbor, color);
        }
    }
}

int MazeGUI::colorAllCells() {
    Set<Wall> walls;
    for (const Wall& wall : allWalls) {
        walls.add(wall);
    }
    walls.removeAll(allWallsRemoved);

    LinkedHashSet<int> colors {
        0xddffdd,
        0xffdddd,
        0xddddff,
        0xffffdd,
        0xffddff,
        0xffcc99
    };
    while (colors.size() < numRows * numCols) {
        colors += randomColor() | 0xb0b0b0;   // random "pastel" bright colors
    }

    Set<Cell> colored;
    for (const Cell& cell : allCells) {
        int color = colors.first();
        colors.remove(color);
        colorHelper(walls, colored, cell, color);
    }

    return numRows * numCols - colors.size();
}

int MazeGUI::getWallsRemovedCount() {
    return isTrackWallsRemoved ? allWallsRemoved.size() : wallsRemoved;
}

const Set<Wall>& MazeGUI::getWallsRemoved() {
    return allWallsRemoved;
}

void MazeGUI::setStrict(bool strict) {
    isStrict = strict;
}

void MazeGUI::setTrackWallsRemoved(bool track) {
    isTrackWallsRemoved = track;
}


int maze_main() {
    MazeGUI::initialize();
    MazeGUI::resize(MazeGUI::MAZE_DEFAULT_ROWS_COLS);
    pause(200);
    MazeGUI::resize(MazeGUI::MAZE_DEFAULT_ROWS_COLS);
    MazeGUI::setTrackWallsRemoved(true);
    MazeGUI::eventLoop();
    return 0;
}
