# LAByrynth

A 2D top down maze game built in C++ with OpenGL and GLUT. A fresh, randomly generated maze loads every run. Walk the player character from the entrance to the goal flag while a bird flock occasionally flies overhead and a flag waves at the finish.

![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Graphics](https://img.shields.io/badge/graphics-OpenGL%20%2F%20GLUT-green)

## Features

- Procedurally generated maze, different every time you play or restart
- Hand drawn player character, birds, and brick and grass tiles rendered entirely with OpenGL primitives
- Animated bird flock that spawns periodically, flies across the screen in a V formation, and flaps its wings on a frame cycle
- Waving flag marking the goal
- Textured brick walls with per brick color variation, cracks, chips, and pits
- Grass tiles with a mini checkerboard pattern and speckled texture, seeded per cell so it stays consistent between frames
- Live game timer that freezes on completion
- Sound effects for movement and winning, plus a looping bird ambience track
- Press SPACE after winning to generate a brand new maze instantly

## Controls

| Key | Action |
|-----|--------|
| W / A / S / D | Move up / left / down / right |
| SPACE | Generate a new maze after winning |
| ESC | Quit |

## Requirements

- A C++ compiler with C++11 support or newer
- OpenGL
- GLUT (freeglut recommended)
- Windows, because the sound system uses the Windows MCI API (`windows.h`, `mmsystem.h`)

## Project Structure

```
LAByrynth/
├── main.cpp        Entry point, GLUT callbacks, and the per frame draw order
├── maze.cpp / .h    Maze generation and player movement logic
├── man.cpp / .h     Player character artwork and rendering
├── brick.cpp / .h   Brick wall tile rendering
├── grass.cpp / .h   Grass tile rendering
├── flag.cpp / .h    Goal flag rendering and sway animation
├── birds.cpp / .h   Bird flock rendering, flight, and wing flap animation
├── sound.cpp / .h   Sound effects and ambience via the Windows MCI API
├── gridutils.h      Shared helper that converts a maze grid cell into screen coordinates
├── LAByrynth.cbp    Code::Blocks project file
├── LAByrynth.depend Code::Blocks dependency cache
└── LAByrynth.layout Code::Blocks editor layout cache
```

## Building

### Code::Blocks

Open `LAByrynth.cbp` in Code::Blocks and build. The project file already lists every source file.

### Manual compile (MinGW example)

```
g++ main.cpp maze.cpp man.cpp brick.cpp grass.cpp flag.cpp birds.cpp sound.cpp -o LAByrynth -lfreeglut -lopengl32 -lglu32 -lwinmm
```

Adjust library names to match your GLUT installation.

## Sound Files

The sound system expects the following files relative to the working directory at runtime:

```
sounds/move.wav
sounds/victory.wav
sounds/birds.wav
```

Create a `sounds/` folder next to the executable and add your own `.wav` files with those names before running.

## How It Works

A quick summary of the main systems, for anyone digging into the code.

### Maze generation

The maze is generated with a randomized depth first search backtracker, the standard algorithm for producing a perfect maze (exactly one path between any two points, no loops). Rooms sit on odd row and column indices, walls sit on even indices between them. Starting at (1,1), the algorithm shuffles the four directions, carves into any unvisited neighbor two cells away, knocks down the single wall cell between them, and recurses. When a cell has no unvisited neighbors left, the recursion simply unwinds back to the previous cell and tries its next shuffled direction, which is the backtracking step. See `maze.cpp`.

### Coordinate system

Every drawing function shares one helper, `cellOrigin()` in `gridutils.h`, which converts a `(row, col)` grid position into a pixel coordinate. This is what keeps bricks, grass, the flag, and the player perfectly aligned without any module needing to know about the others.

### Game loop

`main()` registers three GLUT callbacks and then hands control to `glutMainLoop()`:

- `display()` redraws the full scene every time it is called, looping the grid to draw brick, flag, or grass tiles, then the player, then the bird flock, then the timer and any win screen text
- `timerTick()` fires roughly every 30 milliseconds, advances the bird flight and wing animation and the flag sway animation, then requests a redraw
- `keyboard()` fires on key presses, attempts to move the player, and requests a redraw

### Animation

Both the bird wing flap and the flag sway use the same pattern: a small fixed array of preset angles, a timer that accumulates elapsed time, and an index that steps through the array on a fixed interval. This is closer to a hand drawn sprite cycle than a physics simulation, and keeps the animation lightweight.

