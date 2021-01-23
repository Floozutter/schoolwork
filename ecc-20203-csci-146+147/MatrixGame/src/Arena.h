#ifndef ARENA_H
#define ARENA_H

#include <string>
#include "globals.h"

class Player;
class Robot;

class Arena {
	public:
		Arena(int r, int c);
		~Arena();
		// Accessors.
		int rows() const;
		int cols() const;
		Player * player() const;
		int robotCount() const;
		int nRobotsAt(int r, int c) const;
		// Mutators.
		bool addRobot(int r, int c);
		bool addPlayer(int r, int c);
		void damageRobotAt(int r, int c);
		bool moveRobots();
		// Output.
		void display(std::string msg) const;
	private:
		int m_rows;
		int m_cols;
		Player * m_player;
		Robot * m_robots[MAX_ROBOTS];
		int m_nRobots;
};

#endif
