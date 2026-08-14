#include <cstdlib>
#include <algorithm>
#include <random>
#include "maze.h"

char maze[ROWS][COLS];
int playerRow = 1;
int playerCol = 1;
bool gameWon = false;

static bool visited[ROWS][COLS];

static const int dr[4] = {-1, 1, 0, 0};
static const int dc[4] = {0, 0, -1, 1};

static void shuffleDirections(int dir[4])
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(dir, dir + 4, gen);
}

static void dfsGenerate(int r, int c)
{
    visited[r][c] = true;
    maze[r][c] = ' ';

    int dir[4] = {0, 1, 2, 3};
    shuffleDirections(dir);

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[dir[i]] * 2;
        int nc = c + dc[dir[i]] * 2;

        if (nr <= 0 || nr >= ROWS - 1 || nc <= 0 || nc >= COLS - 1)
            continue;
        if (visited[nr][nc])
            continue;

        maze[r + dr[dir[i]]][c + dc[dir[i]]] = ' ';
        dfsGenerate(nr, nc);
    }
}

static void placeGoal()
{
    for (int i = ROWS - 2; i >= 1; i--)
        for (int j = COLS - 2; j >= 1; j--)
            if (maze[i][j] == ' ')
            {
                maze[i][j] = 'G';
                return;
            }
}

void generateMaze()
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            maze[i][j] = '#';
            visited[i][j] = false;
        }

    dfsGenerate(1, 1);

    playerRow = 1;
    playerCol = 1;
    gameWon = false;

    placeGoal();
}

bool movePlayer(int drIn, int dcIn)
{
    if (gameWon)
        return false;

    int nr = playerRow + drIn;
    int nc = playerCol + dcIn;

    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS)
        return false;
    if (maze[nr][nc] == '#')
        return false;

    playerRow = nr;
    playerCol = nc;

    if (maze[nr][nc] == 'G')
        gameWon = true;

    return true;
}
