#include <cstdlib>
#include <iostream>
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
    // TODO: Delete the player and all remaining dynamically allocated robots.
}

int Arena::rows() const {
	// TODO: TRIVIAL:  Return the number of rows in the arena.
	// Delete the following line and replace it with the correct code.
	return 1;  // This implementation compiles, but is incorrect.
}

int Arena::cols() const {
	// TODO: TRIVIAL: Return the number of columns in the arena.
	// Delete the following line and replace it with the correct code.
	return 1;  // This implementation compiles, but is incorrect.
}

Player* Arena::player() const {
	return this->m_player;
}

int Arena::robotCount() const {
	return this->m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const {
	// TODO: Return the number of robots at row r, column c.
	return 0;  // This implementation compiles, but is incorrect.
}

void Arena::display(std::string msg) const {
	// Position (row,col) in the arena coordinate system is represented in the
	// array element grid[row - 1][col - 1].
	char grid[MAX_ROWS][MAX_COLS];
	int r, c;
	// Fill the grid with dots.
	for (r = 0; r < this->rows(); ++r) {
		for (c = 0; c < this->cols(); ++c) {
			grid[r][c] = '.';
		}
	}
	// Indicate each robot's position.
	// TODO: If one robot is at some grid point, set the char to 'R'.
	// If it's 2 though 8, set it to '2' through '8'.
	// For 9 or more, set it to '9'.
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
	for (r = 0; r < this->rows(); ++r) {
		for (c = 0; c < this->cols(); ++c) {
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
	// If MAXROBOTS have already been added, return false.  Otherwise,
	// dynamically allocate a new robot at coordinates (r,c).  Save the
	// pointer to the newly allocated robot and return true.
	// TODO:  Implement this.
	return false;  // This implementation compiles, but is incorrect.
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
    // TODO:  Damage one robot at row r, column c if at least one is there.
    // If the robot does not survive the damage, destroy it.
}

bool Arena::moveRobots() {
	for (int k = 0; k < this->m_nRobots; ++k) {
		// TODO:  Have the k-th robot in the arena make one move.
		// If that move results in that robot being in the same position as
		// the player, the player dies.
	}
	// Return true if the player is still alive, false otherwise.
	return !this->m_player->isDead();
}
