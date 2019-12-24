#include <SFML/Graphics.hpp>
#include "Tetris.h"

int main()
{
	Tetris game;
	
	//If the game does not initialize quit with an EXIT_FAILURE
	if( game.initialize() )
		return EXIT_FAILURE;
		
	//Play the game.
	game.play();
	
	return 0;
}