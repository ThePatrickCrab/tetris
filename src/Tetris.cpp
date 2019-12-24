#include "Tetris.h"

// Upon creation set variables to default values and set the grid
// to its default (empty) state.
Tetris::Tetris(void)
{
	counter = 0;
	pressed = false;
	print = true;
	resetGrid();
}

Tetris::~Tetris(void)
{}

/*
This function will initialize the tetris game, it is called from main in
order to setup the game. It will load textures and assign them to
sprites, if any texture fails to load then it will return a true and the
program will quit with an EXIT_FAILURE. If it loads everything
sucessfully then it will create a window and return a false so that the
program knows to continue.
*/
bool Tetris::initialize()
{
	// Load .png files to the textures.
	// If a file fails to load return a true value.
	if(!texture[0].loadFromFile("red.png"))
		return true;
	if(!texture[1].loadFromFile("orange.png"))
		return true;
	if(!texture[2].loadFromFile("yellow.png"))
		return true;
	if(!texture[3].loadFromFile("green.png"))
		return true;
	if(!texture[4].loadFromFile("blue.png"))
		return true;
	if(!texture[5].loadFromFile("indigo.png"))
		return true;
	if(!texture[6].loadFromFile("violet.png"))
		return true;
	if(!texture[7].loadFromFile("back.png"))
		return true;
	if(!texture[8].loadFromFile("fallingRed.png"))
		return true;
	if(!texture[9].loadFromFile("fallingOrange.png"))
		return true;
	if(!texture[10].loadFromFile("fallingYellow.png"))
		return true;
	if(!texture[11].loadFromFile("fallingGreen.png"))
		return true;
	if(!texture[12].loadFromFile("fallingBlue.png"))
		return true;
	if(!texture[13].loadFromFile("fallingIndigo.png"))
		return true;
	if(!texture[14].loadFromFile("fallingViolet.png"))
		return true;
	if(!texture[15].loadFromFile("falling.png"))
		return true;

	if(!numbers[0].loadFromFile("num0.png"))
		return true;
	if(!numbers[1].loadFromFile("num1.png"))
		return true;
	if(!numbers[2].loadFromFile("num2.png"))
		return true;
	if(!numbers[3].loadFromFile("num3.png"))
		return true;
	if(!numbers[4].loadFromFile("num4.png"))
		return true;
	if(!numbers[5].loadFromFile("num5.png"))
		return true;
	if(!numbers[6].loadFromFile("num6.png"))
		return true;
	if(!numbers[7].loadFromFile("num7.png"))
		return true;
	if(!numbers[8].loadFromFile("num8.png"))
		return true;
	if(!numbers[9].loadFromFile("num9.png"))
		return true;

	if(!gameBackground.loadFromFile("tetrisBackground.png"))
		return true;

	// Assign textures to sprites.
	for(int i = 0; i < 16; i++)
	{
		block[i].setTexture(texture[i]);

		if(i < 10)
			num[i].setTexture(numbers[i]);
	}

	gBack.setTexture(gameBackground);

	// Create the window for the game.
	window.create(sf::VideoMode(273, 366, 32), "Tetris");

	// Return a false value indicating that this process
	// was completed correctly.
	return false;
}

// Main game loop, contains event polling for user interaction with the
// game.
void Tetris::play()
{
	shape.generate(grid);

	while(window.isOpen())
	{
		sf::Event Event;

		/*
		Event polling loop. When an event happens (ex: a button is
		pressed) then enter this loop and if any defined events happened
		then execute code based on that.
		*/
		while(window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:

				if(!pressed)
				{
					pressed = true;

					if(!print)
					{
						print = true;
						shape.resetLines();
						shape.generate(grid);
					}

					if(Event.key.code == sf::Keyboard::Left)
						shape.move(false, grid);

					if(Event.key.code == sf::Keyboard::Right)
						shape.move(true, grid);

					if(Event.key.code == sf::Keyboard::Z)
						shape.rotate(false, grid);

					if(Event.key.code == sf::Keyboard::X)
						shape.rotate(true, grid);

					if(Event.key.code == sf::Keyboard::Down)
					{
						shape.drop(grid);
					}

					if(Event.key.code == sf::Keyboard::Space)
					{
						shape.quickDrop(grid);
					}
				}
				break;

			case sf::Event::KeyReleased:
				pressed = false;
				break;
			default:
				break;
			}
		}

		// If print variable is true then print game graphics.
		if(print)
		{
			// Set the delay length.
			delay = 10000 / (shape.getLines() + 10) + 250;

			// If pre incremented counter is equal to delay then drop the
			// shape 1 block and reset counter to 0.
			if(++counter > delay)
			{
				shape.drop(grid);
				counter = 0;
			}

			// Display the background graphics and line count.
			displayGame();

			print = !shape.gameOver();
			if(!print)
			{
				resetGrid();
			}

			// If game is not over then print the tetris grid.
			else
			{
				shape.updateGrid(false, grid);
				printGrid();
			}
		}

		else
			displayGame();

		// Update the window.
		window.display();
	}
}

// Prints the grid in the window. It print each block.
void Tetris::printGrid()
{
	for(int i = 1; i < 11; i++)
		for(int j = 1; j < 21; j++)
			if(grid[i][j] >= 0 && grid[i][j] < 16)
			{
				block[grid[i][j]].setPosition(18 * i - 15, 18 * j - 15);

				window.draw(block[grid[i][j]]);

				if(grid[i][j] > 7)
					grid[i][j] = 7;
			}
}

// Resets the grid to its blank values.
void Tetris::resetGrid()
{
	for(int i = 1; i < 11; i++)
		for(int j = 1; j < 21; j++)
			grid[i][j] = 7;

	for(int i = 0; i < 12; i++)
		grid[i][0] = grid[i][21] = -1;

	for(int j = 0; j < 22; j++)
		grid[0][j] = grid[11][j] = -1;
}

// Display to show when game is over.
void Tetris::displayGame()
{
	window.clear();
	window.draw(gBack);

	drawNumbers();
}

// Draws the numbers to the window.
void Tetris::drawNumbers()
{
	int temp = shape.getLines();
	int digit = 0;
	int i;

	if(temp == 0)
	{
		num[0].setPosition(240, 45);
		window.draw(num[0]);
	}

	while(temp > 0)
	{
		i = temp % 10;
		temp -= i;
		temp /= 10;

		num[i].setPosition(240 - (digit++ * 20), 45);
		window.draw(num[i]);
	}
}