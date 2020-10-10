#ifndef GAME_H
#define GAME_H

class Arena;

class Game {
	public:
		Game(int rows, int cols, int nRobots);
		~Game();
		void play();
	private:
		Arena * m_arena;
};

#endif
