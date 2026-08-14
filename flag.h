#ifndef FLAG_H
#define FLAG_H

// Call once per timer tick with the elapsed time in seconds, same as
// updateFlock -- advances the flag's sway animation.
void updateFlagAnimation(float dtSeconds);

void drawFlagPole(int row, int col, int cellSize, int windowSize);

#endif
