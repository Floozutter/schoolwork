#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <memory>
#include "Player.h"
#include "Robot.h"
#include "Arena.h"

Arena::Arena(int r, int c) {
	if (r <= 0 || c <= 0 || r > MAX_ROWS || c > MAX_COLS) {
		std::cout << "***** Arena created with invalid size ";
		std::cout << r << " by " << c << "!" << std::endl;
		std::exit(1);
	}
	this->m_rows = r;
	this->m_cols = c;
	this->m_player = nullptr;
	this->m_nRobots = 0;
}

Arena::~Arena() {
	// Delete player.
	delete this->m_player;
	// Delete robots.
	std::for_each(
		this->m_robots,
		this->m_robots + this->m_nRobots,
		std::default_delete<Robot>()
	);
}

int Arena::rows() const {
	return this->m_rows;
}

int Arena::cols() const {
	return this->m_cols;
}

Player * Arena::player() const {
	return this->m_player;
}

int Arena::robotCount() const {
	return this->m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const {
	return std::count_if(
		this->m_robots,
		this->m_robots + this->m_nRobots,
		[r, c] (Robot const * robot) {
			return robot->row() == r && robot->col() == c;
		}
	);
}

void Arena::display(std::string msg) const {
	// Position (row,col) in the arena coordinate system is represented in the
	// array element grid[row - 1][col - 1].
	char grid[MAX_ROWS][MAX_COLS];
	// Fill the grid with dots.
	for (int r = 0; r < this->rows(); ++r) {
		for (int c = 0; c < this->cols(); ++c) {
			grid[r][c] = '.';
		}
	}
	// Indicate each robot's position:
	// If only 1 robot is at some grid point, set the char to 'R'.
	// If there are 2 though 8 at some grid point, set it to '2' through '8'.
	// If there are 9 or more at some grid point, set it to '9'.
	for (int r = 0; r < this->rows(); ++r) {
		for (int c = 0; c < this->cols(); ++c) {
			size_t const n = this->nRobotsAt(r + 1, c + 1);
			if (n < 1) {
			} else if (n == 1) {
				grid[r][c] = 'R';
			} else if (n < 9) {
				grid[r][c] = '0' + n;
			} else {
				grid[r][c] = '9';
			}
		}
	}
	// Indicate player's position.
	if (this->m_player != nullptr) {
		// Set the char to '@', unless there's also a robot there,
		// in which case set it to '*'.
		char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
		if (gridChar == '.') {
			gridChar = '@';
		} else {
			gridChar = '*';
		}
	}
	// Draw the grid.
	clearScreen();
	for (int r = 0; r < this->rows(); ++r) {
		for (int c = 0; c < this->cols(); ++c) {
			std::cout << grid[r][c];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	// Write message, robot, and player info.
	std::cout << std::endl;
	if (msg != "") {
		std::cout << msg << std::endl;
	}
	std::cout << "There are " << this->robotCount() << " ";
	std::cout << "robots remaining." << std::endl;
	if (this->m_player == nullptr) {
		std::cout << "There is no player." << std::endl;
	} else {
		if (this->m_player->age() > 0) {
			std::cout << "The player has lasted ";
			std::cout << this->m_player->age() << " steps." << std::endl;
		}
		if (this->m_player->isDead()) {
			std::cout << "The player is dead." << std::endl;
		}
	}
}

bool Arena::addRobot(int r, int c) {
	// If MAX_ROBOTS have already been added, return false. Otherwise,
	// dynamically allocate a new robot at coordinates (r,c). Save the pointer
	// pointer to the newly allocated robot and return true.
	if (this->m_nRobots >= MAX_ROBOTS) {
		return false;
	} else {
		this->m_robots[this->m_nRobots] = new Robot(this, r, c);
		++this->m_nRobots;
		return true;
	}
}

bool Arena::addPlayer(int r, int c) {
	// Don't add a player if one already exists.
	if (this->m_player != nullptr) {
		return false;
	}
	// Dynamically allocate a new Player and add it to the arena.
	this->m_player = new Player(this, r, c);
	return true;
}

void Arena::damageRobotAt(int r, int c) {
	// Damage one robot at row r, column c if at least one is there. If the
	// robot does not survive the damage, destroy it.
	Robot * * it = std::find_if(
		this->m_robots,
		this->m_robots + this->m_nRobots,
		[r, c] (Robot const * robot) {
			return robot->row() == r && robot->col() == c;
		}
	);
	if (it != this->m_robots + this->m_nRobots) {
		// Robot found, so damage it.
		if (!(*it)->takeDamageAndLive()) {
			// Robot didn't survive, so destroy it.
			delete *it;
			// Swap and pop to maintain contiguity of live robots.
			*it = *(this->m_robots + this->m_nRobots - 1);
			--this->m_nRobots;
		}
	}
}

bool Arena::moveRobots() {
	// Move each robot in the arena. If that move results in that robot being
	// in the same position as the player, the player dies.
	std::for_each(
		this->m_robots,
		this->m_robots + this->m_nRobots,
		[plyr = this->m_player] (Robot * robot) {
			robot->move();
			if (robot->row() == plyr->row() && robot->col() == plyr->col()) {
				plyr->setDead();
			}
		}
	);
	// Return true if the player is still alive, false otherwise.
	return !this->m_player->isDead();
}
