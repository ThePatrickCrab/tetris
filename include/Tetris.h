#pragma once

#include "Shape.h"

#include <SFML/Graphics.hpp>

/*
The class Tetris is the game of tetris. It requires the class Shape
("Shape.h"). This class contains a main event loop with event polling
for user interaction with the game and basic functions of the game.
*/
class Tetris
{
public:
	Tetris(void); // Sets necessary variable values and sets
	              // the grid to its default value.
	~Tetris(void);

	void play(); // Main game loop.

private:
	void printGrid(); // Display the grid in the window.
	void resetGrid(); // Resets the grid to its default values.
	void displayGame(); // Dispalys the background and line
	                    // count.
	void drawNumbers(); // Draws the numbers to the window.

private:
	Shape shape; // Define a Shape

	// Boolean values indicating if a button is
	// pressed and if you should print the grid.
	bool pressed;
	bool print;

	int grid[12][22]; // Int array holding the value of every block
	                  // in the game area.

	// Int values holding a loop counter,
	// line counter and delay value.
	unsigned counter;
	unsigned lines;

	sf::RenderWindow window; // Window to display the game.

	sf::Texture gameOverDisp; // Texture for the game over display.
	sf::Texture gameBackground; // Texture for the game background.

	sf::Sprite block[16]; // Sprites for the game blocks.
	sf::Sprite num[10]; // Sprites for the numbers.
	sf::Sprite gOver; // Sprite for the game over display.
	sf::Sprite gBack; // Sprite for the game background.
};