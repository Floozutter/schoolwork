#ifndef GLOBALS_H
#define GLOBALS_H

// Constants.
constexpr int MAX_ROWS = 20;     // Max number of rows in the arena.
constexpr int MAX_COLS = 40;     // Max number of columns in the arena.
constexpr int MAX_ROBOTS = 130;  // Max number of robots allowed.
constexpr int MAX_SHOTLEN = 5;   // Max number of steps you can shoot.
enum {
	UP, DOWN, LEFT, RIGHT
};

// Utility functions.
int decodeDirection(char dir);
void clearScreen();

#endif
