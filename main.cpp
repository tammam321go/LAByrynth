#include <GL/glut.h>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

#include "maze.h"
#include "man.h"
#include "brick.h"
#include "grass.h"
#include "flag.h"
#include "birds.h"
#include "sound.h"

const int CELL = 50;
const int WINDOW_SIZE = CELL * ROWS; // 21 * 50 = 1050

std::chrono::steady_clock::time_point startTime;
double finishTime = 0.0;

void drawText(float x, float y, const std::string &text)
{
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// GLUT's bitmap fonts have no real "bold" variant, so we fake both
// bold and depth: a ring of black copies at 1px offsets thickens the
// strokes (bold/outline), a further offset copy behind that gives it
// a drop shadow, and the real color goes on top last.
void drawTextBold(float x, float y, const std::string &text, float r, float g, float b)
{
    static const float ring[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    // drop shadow, offset further down-right for a sense of depth
    glColor4f(0.0f, 0.0f, 0.0f, 0.45f);
    drawText(x + 3, y - 3, text);

    // outline ring -- this is what reads as "bold"
    glColor3f(0.0f, 0.0f, 0.0f);
    for (auto &o : ring)
        drawText(x + o[0], y + o[1], text);

    // actual text on top
    glColor3f(r, g, b);
    drawText(x, y, text);
}

// Semi-transparent rounded-ish panel so the win text stays legible
// no matter what's drawn underneath it (brick, grass, flag, birds...).
void drawPanel(float cx, float cy, float w, float h)
{
    float x0 = cx - w / 2.0f, x1 = cx + w / 2.0f;
    float y0 = cy - h / 2.0f, y1 = cy + h / 2.0f;

    glColor4f(1.0f, 1.0f, 1.0f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();

    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == '#')
                drawBrick(i, j, CELL, WINDOW_SIZE);
            else if (maze[i][j] == 'G')
                drawFlagPole(i, j, CELL, WINDOW_SIZE);
            else
                drawGrass(i, j, CELL, WINDOW_SIZE);
        }
    }

    drawMan(playerRow, playerCol, CELL, WINDOW_SIZE);

    drawFlock();

    double elapsed = gameWon
        ? finishTime
        : std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count();

    std::stringstream timer;
    timer << std::fixed << std::setprecision(2) << "Time: " << elapsed;

    glColor3f(0, 0, 0);
    drawText(20, WINDOW_SIZE - 30, timer.str());

    if (gameWon)
    {
        drawPanel(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f, 480.0f, 160.0f);

        drawTextBold(WINDOW_SIZE / 2 - 90, WINDOW_SIZE / 2 + 40, "YOU WIN!", 0.0f, 0.55f, 0.10f);

        std::stringstream ss;
        ss << "Time: " << std::fixed << std::setprecision(2) << finishTime << " seconds";
        drawTextBold(WINDOW_SIZE / 2 - 130, WINDOW_SIZE / 2, ss.str(), 0.0f, 0.0f, 0.0f);

        drawTextBold(WINDOW_SIZE / 2 - 170, WINDOW_SIZE / 2 - 40, "Press SPACE for the next maze", 0.0f, 0.0f, 0.0f);
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
    bool moved = false;

    switch (key)
    {
        case 'w': case 'W': moved = movePlayer(-1, 0); break;
        case 's': case 'S': moved = movePlayer(1, 0);  break;
        case 'a': case 'A': moved = movePlayer(0, -1); break;
        case 'd': case 'D': moved = movePlayer(0, 1);  break;

        case ' ':
            if (gameWon)
            {
                generateMaze();
                startTime = std::chrono::steady_clock::now();
            }
            break;

        case 27: // ESC
            exit(0);
    }

    // Just won this frame? Freeze the clock and play the victory sound.
    if (gameWon && finishTime == 0.0)
    {
        finishTime = std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count();
        playVictorySound();
    }
    else if (moved)
    {
        playMoveSound();
    }

    if (!gameWon)
        finishTime = 0.0;

    glutPostRedisplay();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_SIZE, 0, WINDOW_SIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void timerTick(int)
{
    updateFlock(0.03f, WINDOW_SIZE); // dt matches the 30ms tick interval below
    updateFlagAnimation(0.03f);
    glutPostRedisplay();
    glutTimerFunc(30, timerTick, 0); // ~33 fps redraw so the clock keeps ticking
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutCreateWindow("2D Maze Game");

    init();
    generateMaze();
    initFlockSystem(WINDOW_SIZE);
    initSound();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, timerTick, 0);

    startTime = std::chrono::steady_clock::now();

    atexit(closeSound); // makes sure sounds/*.wav get released even when ESC calls exit(0)

    glutMainLoop();
    return 0;
}
