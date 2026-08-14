#include <windows.h>
#include <mmsystem.h>
#include "sound.h"

// Windows' MCI API is used instead of the simpler PlaySound() because
// PlaySound only supports ONE sound playing at a time -- starting a
// move sound would cut off the bird ambience loop. MCI lets each
// sound be opened under its own "alias", so multiple can overlap
// (footsteps on top of a looping bird ambience, etc).

void initSound()
{
    mciSendStringA("open sounds/move.wav type waveaudio alias moveSound", NULL, 0, NULL);
    mciSendStringA("open sounds/victory.wav type waveaudio alias victorySound", NULL, 0, NULL);
    mciSendStringA("open sounds/birds.wav type waveaudio alias birdSound", NULL, 0, NULL);
}

void closeSound()
{
    mciSendStringA("close moveSound", NULL, 0, NULL);
    mciSendStringA("close victorySound", NULL, 0, NULL);
    mciSendStringA("close birdSound", NULL, 0, NULL);
}

void playMoveSound()
{
    // "from 0" restarts it every time, so rapid movement doesn't wait
    // for the previous footstep sound to finish.
    mciSendStringA("play moveSound from 0", NULL, 0, NULL);
}

void playVictorySound()
{
    mciSendStringA("play victorySound from 0", NULL, 0, NULL);
}

void startBirdAmbience()
{
    mciSendStringA("play birdSound from 0", NULL, 0, NULL);
}

void stopBirdAmbience()
{
    mciSendStringA("stop birdSound", NULL, 0, NULL);
}
