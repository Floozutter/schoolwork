#ifndef ARENA_H
#define ARENA_H

#include <string>
#include "globals.h"
#include "Player.h"
#include "Robot.h"

class Player;
class Robot;

class Arena {
	public:
		Arena(int r, int c);
		~Arena();
		// Accessors.
		int rows() const;
		int cols() const;
		Player* player() const;
		int robotCount() const;
		int nRobotsAt(int r, int c) const;
		void display(std::string msg) const;
		// Mutators.
		bool addRobot(int r, int c);
		bool addPlayer(int r, int c);
		void damageRobotAt(int r, int c);
		bool moveRobots();
	private:
		int m_rows;
		int m_cols;
		Player* m_player;
		Robot* m_robots[MAX_ROBOTS];
		int m_nRobots;
};

#endif
