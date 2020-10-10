#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "Arena.h"
#include "Robot.h"

Robot::Robot(Arena * ap, int r, int c) {
	if (ap == nullptr) {
		std::cout << "***** A robot must be in some Arena!" << std::endl;
		std::exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols()) {
		std::cout << "***** Robot created with invalid coordinates ";
		std::cout << "(" << r << "," << c << ")!" << std::endl;
		std::exit(1);
	}
	this->m_arena = ap;
	this->m_row = r;
	this->m_col = c;
	this->m_health = 2;
}

int Robot::row() const {
	return this->m_row;
}

int Robot::col() const {
	return this->m_col;
}

void Robot::move() {
	// Attempt to move in a random direction; if we can't move, don't move.
	int const dir = std::rand() % 4;
	// Update position.
	this->m_row += DELTA_ROW[dir];
	this->m_col += DELTA_COL[dir];
	// Stay within arena bounds.
	using std::min, std::max;
	this->m_row = min(max(this->m_row, 1), this->m_arena->rows());
	this->m_col = min(max(this->m_col, 1), this->m_arena->cols());
}

bool Robot::takeDamageAndLive() {
	// If the robot has been hit once before, return false (since a second
	// hit kills a robot). Otherwise, return true (since the robot survived
	// the damage).
	--this->m_health;
	return this->m_health > 0;
}
