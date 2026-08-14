#ifndef SOUND_H
#define SOUND_H

// Call once at startup, after glutCreateWindow.
void initSound();

// Call once, right before the program exits (releases the sound devices).
void closeSound();

void playMoveSound();
void playVictorySound();

// Loops until stopBirdAmbience() is called.
void startBirdAmbience();
void stopBirdAmbience();

#endif
