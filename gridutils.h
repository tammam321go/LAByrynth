#ifndef GRIDUTILS_H
#define GRIDUTILS_H

// Converts a (row, col) grid cell into the OpenGL coordinate of its
// bottom-left corner. row 0 is the TOP of the maze, so we flip it.
// inline so this can safely be included by multiple .cpp files.
inline void cellOrigin(int row, int col, int cellSize, int windowSize, int &x, int &y)
{
    x = col * cellSize;
    y = windowSize - (row + 1) * cellSize;
}

#endif
