#include "globals.h"

int decodeDirection(char dir) {
	switch (dir) {
		case 'u':  return UP;
		case 'd':  return DOWN;
		case 'l':  return LEFT;
		case 'r':  return RIGHT;
		default:   return -1;
	}
}

// THIS CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.
// Note to Xcode users:  clearScreen() will just write a newline instead of
// clearing the window if you launch your program from within Xcode.
#ifdef _MSC_VER  // Microsoft Visual C++.
#include <windows.h>
void clearScreen() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(
		hConsole,
		TCHAR(' '),
		dwConSize,
		upperLeft,
		&dwCharsWritten
	);
	SetConsoleCursorPosition(hConsole, upperLeft);
}
#else  // Assume Unix.
#include <cstdlib>
#include <cstring>
#include <iostream>
void clearScreen() {
	static const char * term = std::getenv("TERM");
	if (term == nullptr || std::strcmp(term, "dumb") == 0) {
		std::cout << std::endl;
	} else {
		// ANSI Terminal Control Sequence Introducer: ESC [
		static const char * CSI = "\x1B["; 
		std::cout << CSI << "2J" << CSI << "H" << std::flush;
	}
}
#endif
