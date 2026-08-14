#include <GL/glut.h>
#include <cstdlib>
#include <algorithm>
#include "grass.h"
#include "gridutils.h"

void drawGrass(int row, int col, int cellSize, int windowSize)
{
    int x, y;
    cellOrigin(row, col, cellSize, windowSize, x, y);

    // Same texture every run
    srand(row * 73856093 ^ col * 19349663);

    const int MINI = 8;                   // 8x8 mini tiles
    int miniSize = cellSize / MINI;

    //--------------------------------------------------
    // Draw the tiny checkerboard
    //--------------------------------------------------
    for (int i = 0; i < MINI; i++)
    {
        for (int j = 0; j < MINI; j++)
        {
            float r, g, b;

            if ((i + j) % 2 == 0)
            {
                // Dark green
                r = 0.22f;
                g = 0.48f;
                b = 0.08f;
            }
            else
            {
                // Light green
                r = 0.56f;
                g = 0.78f;
                b = 0.12f;
            }

            int sx = x + i * miniSize;
            int sy = y + j * miniSize;

            glColor3f(r, g, b);

            glBegin(GL_QUADS);
                glVertex2i(sx, sy);
                glVertex2i(sx + miniSize, sy);
                glVertex2i(sx + miniSize, sy + miniSize);
                glVertex2i(sx, sy + miniSize);
            glEnd();

            //--------------------------------------------------
            // Add dots inside this mini tile
            //--------------------------------------------------

            glPointSize(2);
            glBegin(GL_POINTS);

            int dots = miniSize * miniSize / 2;

            for (int k = 0; k < dots; k++)
            {
                int px = sx + rand() % miniSize;
                int py = sy + rand() % miniSize;

                int t = rand() % 100;

                if (t < 45)
                {
                    // lighter
                    glColor3f(
                        std::min(r + 0.10f, 1.0f),
                        std::min(g + 0.10f, 1.0f),
                        std::min(b + 0.06f, 1.0f));
                }
                else if (t < 85)
                {
                    // darker
                    glColor3f(
                        std::max(r - 0.08f, 0.0f),
                        std::max(g - 0.08f, 0.0f),
                        std::max(b - 0.05f, 0.0f));
                }
                else
                {
                    // nearly black
                    glColor3f(0.05f, 0.08f, 0.02f);
                }

                glVertex2i(px, py);
            }

            glEnd();
        }
    }

    //--------------------------------------------------
    // Fill right edge if cellSize isn't divisible by MINI
    //--------------------------------------------------
    if (miniSize * MINI < cellSize)
    {
        glColor3f(0.35f, 0.60f, 0.12f);

        glBegin(GL_QUADS);

        glVertex2i(x + miniSize * MINI, y);
        glVertex2i(x + cellSize, y);
        glVertex2i(x + cellSize, y + cellSize);
        glVertex2i(x + miniSize * MINI, y + cellSize);

        glEnd();
    }

    //--------------------------------------------------
    // Fill top edge if needed
    //--------------------------------------------------
    if (miniSize * MINI < cellSize)
    {
        glColor3f(0.35f, 0.60f, 0.12f);

        glBegin(GL_QUADS);

        glVertex2i(x, y + miniSize * MINI);
        glVertex2i(x + miniSize * MINI, y + miniSize * MINI);
        glVertex2i(x + miniSize * MINI, y + cellSize);
        glVertex2i(x, y + cellSize);

        glEnd();
    }
}
