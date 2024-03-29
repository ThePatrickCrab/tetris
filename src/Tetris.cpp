#include "Tetris.h"

#include <boost/dll.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <exception>

// Upon creation set variables to default values and set the grid
// to its default (empty) state.
Tetris::Tetris(void)
    : shape()
    , pressed(false)
    , print(true)
    , counter(0)
    , lines(0)
    , window(sf::VideoMode(273, 366, 32), "Tetris")
{
	const boost::filesystem::path basepath =
	    boost::dll::program_location().parent_path() / "resources";
	// Load .png files to the textures.
	// If a file fails to load return a true value.
	if(!texture[0].loadFromFile((basepath / "red.png").string()) ||
	    !texture[1].loadFromFile((basepath / "orange.png").string()) ||
	    !texture[2].loadFromFile((basepath / "yellow.png").string()) ||
	    !texture[3].loadFromFile((basepath / "green.png").string()) ||
	    !texture[4].loadFromFile((basepath / "blue.png").string()) ||
	    !texture[5].loadFromFile((basepath / "indigo.png").string()) ||
	    !texture[6].loadFromFile((basepath / "violet.png").string()) ||
	    !texture[7].loadFromFile((basepath / "back.png").string()) ||
	    !texture[8].loadFromFile((basepath / "fallingRed.png").string()) ||
	    !texture[9].loadFromFile((basepath / "fallingOrange.png").string()) ||
	    !texture[10].loadFromFile((basepath / "fallingYellow.png").string()) ||
	    !texture[11].loadFromFile((basepath / "fallingGreen.png").string()) ||
	    !texture[12].loadFromFile((basepath / "fallingBlue.png").string()) ||
	    !texture[13].loadFromFile((basepath / "fallingIndigo.png").string()) ||
	    !texture[14].loadFromFile((basepath / "fallingViolet.png").string()) ||
	    !texture[15].loadFromFile((basepath / "falling.png").string()) ||
	    !numbers[0].loadFromFile((basepath / "num0.png").string()) ||
	    !numbers[1].loadFromFile((basepath / "num1.png").string()) ||
	    !numbers[2].loadFromFile((basepath / "num2.png").string()) ||
	    !numbers[3].loadFromFile((basepath / "num3.png").string()) ||
	    !numbers[4].loadFromFile((basepath / "num4.png").string()) ||
	    !numbers[5].loadFromFile((basepath / "num5.png").string()) ||
	    !numbers[6].loadFromFile((basepath / "num6.png").string()) ||
	    !numbers[7].loadFromFile((basepath / "num7.png").string()) ||
	    !numbers[8].loadFromFile((basepath / "num8.png").string()) ||
	    !numbers[9].loadFromFile((basepath / "num9.png").string()) ||
	    !gameBackground.loadFromFile(
	        (basepath / "tetrisBackground.png").string()))
	{
		throw std::runtime_error("Couldn't load resources");
	}

	// Assign textures to sprites.
	for(int i = 0; i < 16; i++)
	{
		block[i].setTexture(texture[i]);
		if(i < 10)
		{
			num[i].setTexture(numbers[i]);
		}
	}
	gBack.setTexture(gameBackground);

	counter = 0;
	pressed = false;
	print = true;
	resetGrid();
}

Tetris::~Tetris(void)
{}

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
			unsigned delay = 10000 / (shape.getLines() + 10) + 250;

			// If pre incremented counter is equal to delay then drop the
			// shape 1 block and reset counter to 0.
			if(++counter > delay)
			{
				shape.drop(grid);
				counter = 0;
			}

			// Display the background graphics and line count.
			displayGame();

			if(shape.gameOver())
			{
				resetGrid();
			}
			else
			{
				// If game is not over then print the tetris grid.
				shape.updateGrid(false, grid);
				printGrid();
			}
		}
		else
		{
			displayGame();
		}

		// Update the window.
		window.display();
	}
}

// Prints the grid in the window. It print each block.
void Tetris::printGrid()
{
	for(int i = 1; i < 11; i++)
	{
		for(int j = 1; j < 21; j++)
		{
			if(grid[i][j] >= 0 && grid[i][j] < 16)
			{
				block[grid[i][j]].setPosition(static_cast<float>(18 * i - 15),
				    static_cast<float>(18 * j - 15));

				window.draw(block[grid[i][j]]);

				if(grid[i][j] > 7)
				{
					grid[i][j] = 7;
				}
			}
		}
	}
}

// Resets the grid to its blank values.
void Tetris::resetGrid()
{
	for(int i = 1; i < 11; i++)
	{
		for(int j = 1; j < 21; j++)
		{
			grid[i][j] = 7;
		}
	}

	for(int i = 0; i < 12; i++)
	{
		grid[i][0] = grid[i][21] = -1;
	}

	for(int j = 0; j < 22; j++)
	{
		grid[0][j] = grid[11][j] = -1;
	}
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

		num[i].setPosition(
		    static_cast<float>(240 - (digit++ * 20)), static_cast<float>(45));
		window.draw(num[i]);
	}
}