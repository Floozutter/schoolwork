#include <string>
#include <iostream>
#include "globals.h"
#include "Arena.h"
#include "Player.h"
#include "Game.h"

Game::Game(int rows, int cols, int nRobots) {
	if (nRobots > MAX_ROBOTS) {
		std::cout << "***** Trying to create Game with " << nRobots;
		std::cout << " robots; only " << MAX_ROBOTS;
		std::cout << " are allowed!" << std::endl;
		std::exit(1);
	}
	// Create arena.
	this->m_arena = new Arena(rows, cols);
	// Add player.
	int rPlayer = std::rand() % rows + 1;
	int cPlayer = std::rand() % cols + 1;
	this->m_arena->addPlayer(rPlayer, cPlayer);
	// Populate with robots.
	while (nRobots > 0) {
		int r = std::rand() % rows + 1;
		int c = std::rand() % cols + 1;
		  // Don't put a robot where the player is
		if (r == rPlayer && c == cPlayer) {
			continue;
		}
		this->m_arena->addRobot(r, c);
		--nRobots;
	}
}

Game::~Game() {
	delete this->m_arena;
}

void Game::play() {
	Player* p = this->m_arena->player();
	if (p == nullptr) {
		this->m_arena->display("");
		return;
	}
	std::string msg = "";
	do {
		this->m_arena->display(msg);
		msg = "";
		std::cout << std::endl << "Move (u/d/l/r/su/sd/sl/sr/c//q): ";
		std::string action;
		std::getline(std::cin, action);
		if (action.size() == 0) {
			p->stand();
		} else {
			switch (action.at(0)) {
				case 'q':  // Quit.
					return;
				case 'c':  // Computer moves place.
					msg = p->takeComputerChosenTurn();
					break;
				case 'u':
				case 'd':
				case 'l':
				case 'r':
					p->move(decodeDirection(action[0]));
					break;
				case 's':
					if (action.size() < 2) {
						// If no direction, nobody moves.
						std::cout << '\a' << std::endl;  // Beep!
						continue;
					}
					switch (action.at(1)) {
						case 'u':
						case 'd':
						case 'l':
						case 'r':
							if (p->shoot(decodeDirection(action.at(1)))) {
								msg = "Hit!";
							} else {
								msg = "Missed!";
							}
							break;
						default:
							// If bad direction, nobody moves.
							std::cout << '\a' << std::endl;  // Beep!
							continue;
					}
					break;
				default:
					std::cout << '\a' << std::endl;  // Beep!
					continue;
			}
		}
		this->m_arena->moveRobots();  // May be skipped by continue!
	} while (
		!this->m_arena->player()->isDead() && this->m_arena->robotCount() > 0
	);
	this->m_arena->display(msg);
}
