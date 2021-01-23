#include <cstdlib>
#include <ctime>
#include "Game.h"

int main() {
	// Initialize the random number generator.
	std::srand(static_cast<unsigned int>(std::time(0)));
	// Create game.
	Game g(15, 18, 80);  // Mini: 3, 3, 2.
	// Play the game!
	g.play();
}
