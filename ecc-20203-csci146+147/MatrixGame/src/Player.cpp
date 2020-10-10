#include <cstdlib>
#include <iostream>
#include "Arena.h"
#include "Player.h"

Player::Player(Arena* ap, int r, int c) {
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
	// TODO: TRIVIAL: Return what row the player is at.
	// Delete the following line and replace it with the correct code.
	return 1;  // This implementation compiles, but is incorrect.
}

int Player::col() const {
	// TODO: TRIVIAL: Return what column the player is at.
	// Delete the following line and replace it with the correct code.
	return 1;  // This implementation compiles, but is incorrect.
}

int Player::age() const {
	// TODO: TRIVIAL: Return the player's age.
	// Delete the following line and replace it with the correct code.
	return 0;  // This implementation compiles, but is incorrect.
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
	switch (dir) {
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

bool Player::shoot(int dir) {
    ++this->m_age;
	if (rand() % 3 == 0) {
		// Miss with 1/3 probability.
		return false;
	} else {
		// TODO:  Damage the nearest robot in direction dir, returning
		// true if a robot is hit and damaged, false if not hit.
		return false;  // This implementation compiles, but is incorrect.
	}
}

bool Player::isDead() const {
	// TODO: TRIVIAL: Return whether the player is dead.
	return false;  // This implementation compiles, but is incorrect.
}

void Player::setDead() {
	this->m_dead = true;
}
