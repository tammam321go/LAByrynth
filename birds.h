#ifndef BIRDS_H
#define BIRDS_H

// Call once at startup, after glutCreateWindow.
// windowSize = the size of the (square) game window, used to pick a
// random height for each flock when it spawns.
void initFlockSystem(int windowSize);

// Call once per timer tick with the elapsed time in seconds.
// Advances the flock's flight position, its wing-flap animation, and
// the countdown to the next flock spawning.
void updateFlock(float dtSeconds, int windowSize);

// Call once per display() call to draw the flock (if one is currently
// active). Draws nothing when no flock is on screen.
void drawFlock();

#endif
