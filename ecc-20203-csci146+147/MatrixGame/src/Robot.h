#ifndef ROBOT_H
#define ROBOT_H

#include "globals.h"

class Arena;

class Robot {
	public:
		Robot(Arena* ap, int r, int c);
		// Accessors.
		int row() const;
		int col() const;
		// Mutators.
		void move();
		bool takeDamageAndLive();
	private:
		Arena* m_arena;
		int m_row;
		int m_col;
};

#endif
