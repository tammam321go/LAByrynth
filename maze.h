#ifndef MAZE_H
#define MAZE_H

// Must stay ODD. The generator carves paths on odd (row,col) indices
// starting from (1,1); with an even size the outer border ends up
// double-thick on the bottom/right side (the last odd node index
// falls short of the border row/col by one cell, leaving it stranded
// as an extra unreachable wall). Odd sizes leave a clean 1-cell border.
const int ROWS = 21;
const int COLS = 21;

// The maze grid. '#' = brick wall, ' ' = grass/open path, 'G' = goal flag.
extern char maze[ROWS][COLS];

extern int playerRow;
extern int playerCol;
extern bool gameWon;

// Builds a brand new random maze (called at startup and after every win).
void generateMaze();

// Attempts to move the player by (dr, dc). Returns true if the move
// succeeded (updates playerRow/playerCol and gameWon), false if it
// was blocked by a wall, the grid edge, or the game is already won.
bool movePlayer(int dr, int dc);

#endif
