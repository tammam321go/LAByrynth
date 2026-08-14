#include <GL/glut.h>
#include <algorithm>
#include <cmath>

#include "brick.h"
#include "gridutils.h"

// The brick pattern below was originally designed on its own 100x100
// unit "wall" (see WALL_DESIGN). We keep that design untouched and
// just scale the whole thing down to fit whatever cellSize the maze
// is using -- see the glScalef call in drawBrick().
static const int WALL_DESIGN = 100;
// Fewer, bigger bricks per cell (2 columns x 4 rows) read cleanly from
// a distance. The old 20x10 units packed 50 tiny bricks into one cell,
// which is what made the wall look small and "broken" up close.
static const int BRICK_UNIT_W = 50;
static const int BRICK_UNIT_H = 25;

static const float MORTAR_RGB[] = {0.55f, 0.27f, 0.07f};
static const float BRICK_RGB[]  = {0.55f, 0.27f, 0.07f};
static const float BRICK_VARIATION = 0.1f;

static void getBrickColor(int row, int col, float *color)
{
    float variation = BRICK_VARIATION * (sinf(row * 1.7f + col * 3.2f) * 0.5f + 0.5f);
    color[0] = std::min(1.0f, std::max(0.0f, BRICK_RGB[0] + variation * 0.2f));
    color[1] = std::min(1.0f, std::max(0.0f, BRICK_RGB[1] + variation * 0.1f));
    color[2] = std::min(1.0f, std::max(0.0f, BRICK_RGB[2] + variation * 0.05f));
}

static void drawCracks(float x, float y, float w, float h)
{
    glColor3f(0.20f, 0.10f, 0.05f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(x + w * 0.20f, y + h * 0.75f);
        glVertex2f(x + w * 0.45f, y + h * 0.55f);

        glVertex2f(x + w * 0.45f, y + h * 0.55f);
        glVertex2f(x + w * 0.35f, y + h * 0.30f);

        glVertex2f(x + w * 0.35f, y + h * 0.30f);
        glVertex2f(x + w * 0.55f, y + h * 0.18f);
    glEnd();
}

static void drawChip(float x, float y, float w, float h)
{
    glColor3f(0.25f, 0.12f, 0.05f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + h);
        glVertex2f(x + w * 0.12f, y + h);
        glVertex2f(x, y + h - h * 0.18f);

        glVertex2f(x + w, y);
        glVertex2f(x + w - w * 0.12f, y);
        glVertex2f(x + w, y + h * 0.15f);
    glEnd();
}

static void drawPits(float x, float y, float w, float h)
{
    glColor3f(0.35f, 0.18f, 0.08f);
    glPointSize(2);
    glBegin(GL_POINTS);
        glVertex2f(x + w * 0.30f, y + h * 0.70f);
        glVertex2f(x + w * 0.62f, y + h * 0.50f);
        glVertex2f(x + w * 0.75f, y + h * 0.30f);
        glVertex2f(x + w * 0.40f, y + h * 0.22f);
    glEnd();
}

static void drawOneBrick(float x, float y, float width, float height, float *color)
{
    glColor3fv(color);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // top highlight
    glColor4f(1, 1, 1, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y + height - 2);
        glVertex2f(x, y + height - 2);
    glEnd();

    // bottom shadow
    glColor4f(0, 0, 0, 0.18f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + 2);
        glVertex2f(x, y + 2);
    glEnd();

    // outline
    glColor3f(0.3f, 0.15f, 0.05f);
    glLineWidth(0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    int seed = (int)(x + y);
    if (seed % 3 == 0) drawCracks(x, y, width, height);
    if (seed % 5 == 0) drawChip(x, y, width, height);
    if (seed % 2 == 0) drawPits(x, y, width, height);
}

void drawBrick(int row, int col, int cellSize, int windowSize)
{
    int cx, cy;
    cellOrigin(row, col, cellSize, windowSize, cx, cy);

    // Scale the WALL_DESIGN x WALL_DESIGN pattern so it exactly fills
    // one cellSize x cellSize maze cell, no matter what CELL is.
    float scale = (float)cellSize / (float)WALL_DESIGN;

    glPushMatrix();
        glTranslatef((float)cx, (float)cy, 0.0f);
        glScalef(scale, scale, 1.0f);

        // mortar background fills the whole design square
        glColor3fv(MORTAR_RGB);
        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f((float)WALL_DESIGN, 0);
            glVertex2f((float)WALL_DESIGN, (float)WALL_DESIGN);
            glVertex2f(0, (float)WALL_DESIGN);
        glEnd();

        int cols = WALL_DESIGN / BRICK_UNIT_W;
        int rows = WALL_DESIGN / BRICK_UNIT_H;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                float x = c * BRICK_UNIT_W;
                float y = r * BRICK_UNIT_H;

                // stagger every other row like real brickwork
                if (r % 2 == 1)
                {
                    x += BRICK_UNIT_W / 2.0f;
                    if (x + BRICK_UNIT_W > WALL_DESIGN)
                        continue;
                }

                float color[3];
                getBrickColor(r, c, color);
                if (r % 2 == 0)
                {
                    color[0] *= 0.95f;
                    color[1] *= 0.95f;
                    color[2] *= 0.95f;
                }

                drawOneBrick(x, y, (float)BRICK_UNIT_W, (float)BRICK_UNIT_H, color);
            }
        }
    glPopMatrix();
}
