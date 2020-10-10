#include <cstdlib>
#include <iostream>
#include "Arena.h"
#include "Player.h"

Player::Player(Arena * ap, int r, int c) {
	if (ap == nullptr) {
		std::cout << "***** The player must be in some Arena!" << std::endl;
		std::exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols()) {
		std::cout << "**** Player created with invalid coordinates ";
		std::cout << "(" << r << "," << c << ")!" << std::endl;
		std::exit(1);
	}
	this->m_arena = ap;
	this->m_row = r;
	this->m_col = c;
	this->m_age = 0;
	this->m_dead = false;
}

int Player::row() const {
	return this->m_row;
}

int Player::col() const {
	return this->m_col;
}

int Player::age() const {
	return this->m_age;
}

std::string Player::takeComputerChosenTurn() {
	// TODO: Replace this implementation:
	this->stand();
	return "Stood";
	// Your replacement implementation should do something intelligent and
	// return a string that describes what happened. When you've decided what
	// action to take, take it by calling move, shoot, or stand.
	// This function must return one of the following four strings:
	// - "Moved."
	// - "Shot and hit!"
	// - "Shot and missed!"
	// - "Stood."
	// Here's one possible strategy:
	// If moving in some direction would put me in less immediate danger than
	// standing, then move in that direction. Else, shoot in the direction of
	// the nearest robot I can hit.
	// A more aggressive strategy is possible, where you hunt down robots.
}

void Player::stand() {
	++this->m_age;
}

void Player::move(int dir) {
	++this->m_age;
	// Update position.
	this->m_row += DELTA_ROW[dir];
	this->m_col += DELTA_COL[dir];
	// Stay within arena bounds.
	using std::min, std::max;
	this->m_row = min(max(this->m_row, 1), this->m_arena->rows());
	this->m_col = min(max(this->m_col, 1), this->m_arena->cols());
}

bool Player::shoot(int dir) {
    ++this->m_age;
	if (rand() % 3 == 0) {
		// Miss with 1/3 probability.
		return false;
	} else {
		// Damage the nearest robot in direction dir, returning true if a
		// robot is hit and damaged, false if not hit.
		int r = this->row();
		int c = this->col();
		for (size_t i = 0; i < MAX_SHOTLEN; ++i) {
			r += DELTA_ROW[dir];
			c += DELTA_COL[dir];
			if (this->m_arena->nRobotsAt(r, c) > 0) {
				this->m_arena->damageRobotAt(r, c);
				return true;
			}
		}
		return false;
	}
}

bool Player::isDead() const {
	return this->m_dead;
}

void Player::setDead() {
	this->m_dead = true;
}
