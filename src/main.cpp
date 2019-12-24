#include "Tetris.h"

#include <SFML/Graphics.hpp>

#include <stdlib.h>

int main()
{
	srand(time(NULL));

	Tetris game;
	game.play();
}