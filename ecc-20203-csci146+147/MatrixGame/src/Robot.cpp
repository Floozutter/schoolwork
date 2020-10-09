#include <cstdlib>
#include <iostream>
#include "Robot.h"

Robot::Robot(Arena* ap, int r, int c) {
	if (ap == nullptr) {
		std::cout << "***** A robot must be in some Arena!" << std::endl;
		std::exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols()) {
		std::cout << "***** Robot created with invalid coordinates ";
		std::cout << "(" << r << "," << c << ")!" << std::endl;
		exit(1);
	}
	this->m_arena = ap;
	this->m_row = r;
	this->m_col = c;
}

int Robot::row() const {
	return this->m_row;
}

int Robot::col() const {
	// TODO: TRIVIAL: Return what column the robot is at.
	// Delete the following line and replace it with the correct code.
	return 1;  // This implementation compiles, but is incorrect.
}

void Robot::move() {
	// Attempt to move in a random direction; if we can't move, don't move.
	switch (std::rand() % 4) {
		// TODO: Implement the movements.
		case UP:
			break;
		case DOWN:
			break;
		case LEFT:
			break;
		case RIGHT:
			break;
	}
}

bool Robot::takeDamageAndLive() {
	// TODO: If the robot has been hit once before, return false (since a
	// second hit kills a robot). Otherwise, return true (since the robot
	// survived the damage).
	return false;  // This implementation compiles, but is incorrect.
}
