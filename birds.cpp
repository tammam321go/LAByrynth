#include <GL/glut.h>
#include <cmath>
#include <random>

#include "birds.h"
#include "sound.h"

namespace
{
    // The 8-frame wing-flap cycle, taken from the original single-bird demo.
    const float wingAngles[8] = {
        -65.0f, -45.0f, -20.0f, 5.0f, 30.0f, 50.0f, 25.0f, -20.0f
    };

    // ---------------- bird artwork, adapted from the single-bird demo ----------------
    // (unchanged geometry -- just no longer reading global birdX/birdY/currentFrame)

    void ellipse(float cx, float cy, float rx, float ry)
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 60; i++)
        {
            float a = 2.0f * 3.1415926f * i / 60.0f;
            glVertex2f(cx + cosf(a) * rx, cy + sinf(a) * ry);
        }
        glEnd();
    }

    void bezierPoint(float p0x, float p0y, float p1x, float p1y,
                      float p2x, float p2y, float p3x, float p3y,
                      float t, float &x, float &y)
    {
        float u = 1.0f - t;
        x = u * u * u * p0x + 3 * u * u * t * p1x + 3 * u * t * t * p2x + t * t * t * p3x;
        y = u * u * u * p0y + 3 * u * u * t * p1y + 3 * u * t * t * p2y + t * t * t * p3y;
    }

    void drawSmoothWing(float angle, bool upperWing)
    {
        glPushMatrix();

        if (upperWing)
            glTranslatef(475, 315, 0);
        else
            glTranslatef(475, 300, 0);

        glRotatef(angle, 0, 0, 1);

        glColor3f(0.23f, 0.15f, 0.21f);

        float p0x = 0,   p0y = 0;
        float p1x = -55, p1y = 45;
        float p2x = -125,p2y = 85;
        float p3x = -190,p3y = 55;

        glBegin(GL_POLYGON);
        for (int i = 0; i <= 40; i++)
        {
            float t = (float)i / 40.0f;
            float x, y;
            bezierPoint(p0x, p0y, p1x, p1y, p2x, p2y, p3x, p3y, t, x, y);
            glVertex2f(x, y);
        }
        for (int i = 40; i >= 0; i--)
        {
            float t = (float)i / 40.0f;
            float x, y;
            bezierPoint(0, -5, -60, 10, -125, 5, -180, -15, t, x, y);
            glVertex2f(x, y);
        }
        glEnd();

        glColor3f(0.30f, 0.21f, 0.27f);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 40; i++)
        {
            float t = (float)i / 40.0f;
            float x, y;
            bezierPoint(0, 0, -55, 45, -125, 85, -190, 55, t, x, y);
            glVertex2f(x, y);
        }
        glEnd();

        glColor3f(0.28f, 0.19f, 0.25f);
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= 25; i++)
        {
            float t = (float)i / 25.0f;
            float x1, y1, x2, y2;
            bezierPoint(-10, 0, -55, 30, -115, 55, -175, 40, t, x1, y1);
            bezierPoint(-15, -2, -60, 12, -120, 15, -175, 0, t, x2, y2);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();

        glPopMatrix();
    }

    void drawBirdBody()
    {
        glColor3f(0.28f, 0.19f, 0.25f);
        ellipse(505, 305, 78, 22);

        glColor3f(0.25f, 0.17f, 0.23f);
        ellipse(555, 320, 32, 28);

        glColor3f(0.34f, 0.24f, 0.29f);
        ellipse(547, 329, 6, 6);

        glColor3f(0.95f, 0.85f, 0.65f);
        ellipse(550, 331, 3, 3);

        glColor3f(0.17f, 0.10f, 0.14f);
        glBegin(GL_TRIANGLES);
            glVertex2f(580, 320);
            glVertex2f(625, 313);
            glVertex2f(580, 330);
        glEnd();

        glColor3f(0.80f, 0.50f, 0.25f);
        glBegin(GL_TRIANGLES);
            glVertex2f(520, 285);
            glVertex2f(535, 285);
            glVertex2f(528, 276);

            glVertex2f(535, 285);
            glVertex2f(550, 283);
            glVertex2f(543, 275);
        glEnd();
    }

    void drawBirdTail()
    {
        glColor3f(0.25f, 0.16f, 0.22f);
        glBegin(GL_POLYGON);
            glVertex2f(445, 300);
            glVertex2f(350, 270);
            glVertex2f(395, 305);
            glVertex2f(350, 300);
            glVertex2f(410, 315);
            glVertex2f(370, 325);
            glVertex2f(440, 325);
        glEnd();
    }

    // Draws one bird centered on its own local (500,300) design pivot.
    // Caller is responsible for translating to the bird's actual position.
    void drawSingleBird(float wingAngle)
    {
        drawSmoothWing(wingAngle, true);
        drawSmoothWing(-wingAngle * 0.45f, false);
        drawBirdTail();
        drawBirdBody();
    }

    // ---------------- flock formation ----------------

    struct FlockMember
    {
        float offsetX, offsetY; // position relative to the flock leader (forms the V)
        int phase;               // starting index into wingAngles, so wings desync
    };

    // Leader up front, two trailing arms -- similar spread to a real V formation.
    const FlockMember FLOCK_SHAPE[] = {
        {    0,   0, 0 },  // leader
        {  -55,  22, 2 },
        {  -55, -22, 5 },
        { -105,  40, 1 },
        { -105, -40, 6 },
        { -150,  55, 4 },
    };
    const int FLOCK_SIZE = sizeof(FLOCK_SHAPE) / sizeof(FLOCK_SHAPE[0]);

    // ---------------- flock state ----------------

    bool flockActive = false;
    float flockX = 0.0f;
    float flockY = 0.0f;
    const float FLOCK_SPEED = 140.0f; // pixels per second

    int wingFrame = 0;
    float wingFrameTimer = 0.0f;
    const float WING_FRAME_INTERVAL = 0.09f; // ~90ms per flap frame

    float spawnCountdown = 5.0f;

    std::mt19937 rng(std::random_device{}());

    float randomRange(float lo, float hi)
    {
        std::uniform_real_distribution<float> dist(lo, hi);
        return dist(rng);
    }

    void spawnFlock(int windowSize)
    {
        flockActive = true;
        flockX = -250.0f; // start off-screen to the left
        // keep flocks in the upper portion of the window so they read
        // as "flying over" the maze rather than through the middle of it
        flockY = randomRange(windowSize * 0.55f, windowSize * 0.92f);

        startBirdAmbience();
    }
}

void initFlockSystem(int windowSize)
{
    (void)windowSize;
    spawnCountdown = randomRange(4.0f, 8.0f); // first flock shows up a bit after launch
}

void updateFlock(float dt, int windowSize)
{
    spawnCountdown -= dt;

    if (!flockActive && spawnCountdown <= 0.0f)
    {
        spawnFlock(windowSize);
        spawnCountdown = randomRange(10.0f, 20.0f);
    }

    if (flockActive)
    {
        flockX += FLOCK_SPEED * dt;

        wingFrameTimer += dt;
        if (wingFrameTimer >= WING_FRAME_INTERVAL)
        {
            wingFrameTimer -= WING_FRAME_INTERVAL;
            wingFrame = (wingFrame + 1) % 8;
        }

        if (flockX > windowSize + 250.0f) // fully past the right edge
        {
            flockActive = false;
            stopBirdAmbience();
        }
    }
}

void drawFlock()
{
    if (!flockActive)
        return;

    const float BIRD_SCALE = 0.4f;   // birds at 40% size = 60% smaller
    const float SPREAD_SCALE = 1.6f; // formation spacing, independent of bird size

    for (int i = 0; i < FLOCK_SIZE; i++)
    {
        float bx = flockX + FLOCK_SHAPE[i].offsetX * SPREAD_SCALE;
        float by = flockY + FLOCK_SHAPE[i].offsetY * SPREAD_SCALE;
        int frameIndex = (wingFrame + FLOCK_SHAPE[i].phase) % 8;

        glPushMatrix();
            glTranslatef(bx, by, 0.0f);
            glScalef(BIRD_SCALE, BIRD_SCALE, 1.0f);
            glTranslatef(-500.0f, -300.0f, 0.0f);
            drawSingleBird(wingAngles[frameIndex]);
        glPopMatrix();
    }
}
