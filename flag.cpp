#include <GL/glut.h>
#include "flag.h"
#include "grass.h"
#include "gridutils.h"

namespace
{
    // A handful of sway angles the flag cycles through, the same way
    // the birds cycle through wingAngles -- discrete frames rather
    // than a continuous animation.
    const float swayAngles[6] = { -14.0f, -6.0f, 0.0f, 8.0f, 14.0f, 6.0f };
    int swayFrame = 0;
    float swayTimer = 0.0f;
    const float SWAY_INTERVAL = 0.15f; // seconds per frame
}

void updateFlagAnimation(float dt)
{
    swayTimer += dt;
    if (swayTimer >= SWAY_INTERVAL)
    {
        swayTimer -= SWAY_INTERVAL;
        swayFrame = (swayFrame + 1) % 6;
    }
}

void drawFlagPole(int row, int col, int cellSize, int windowSize)
{
    int x, y;
    cellOrigin(row, col, cellSize, windowSize, x, y);

    // grass floor underneath, matching every other grass cell in the maze
    drawGrass(row, col, cellSize, windowSize);

    float cx = x + cellSize * 0.5f;

    // pole
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(4);
    glBegin(GL_LINES);
        glVertex2f(cx, y);
        glVertex2f(cx, y + cellSize);
    glEnd();

    // flag, swaying around the top of the pole like it's catching wind
    glPushMatrix();
        glTranslatef(cx, y + cellSize, 0.0f);
        glRotatef(swayAngles[swayFrame], 0, 0, 1);

        glColor3f(0.9f, 0.1f, 0.1f);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(cellSize * 0.45f, -cellSize * 0.2f);
            glVertex2f(0.0f, -cellSize * 0.4f);
        glEnd();
    glPopMatrix();
}
