#include "Tetris.h"

#include <ctime>
#include <cstdlib>

int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	Tetris game;
	game.play();
}