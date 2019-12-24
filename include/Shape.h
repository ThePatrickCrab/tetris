#pragma once
#include "Location.h"

/*
This Class is made for the class Tetris and requires the class Location
(Location.h). It generates and manipulates a shape and will update a
tetris game grid based on the shape and the existing values in the grid.
*/
class Shape
{
public:
	Shape(void); // Set lines to 0, and seed the random number table.
	~Shape(void);

	void generate(int[][22]); // Generate a new shape at the top.

	void rotate(bool, int[][22]); // Rotate the shape CW or CCW.
	void move(bool, int[][22]); // Move the block left or right.

	void drop(int[][22]); // Move the shape down 1 block.
	void quickDrop(int[][22]); // Move the shape straight down
	                           // as far as possible.

	void updateGrid(bool, int[][22]); // Update the grid.
	bool protect(int[][22]); // Make sure the shape does not
	                         // move into other blocks.
	void dropPreview(int[][22]); // Show where the block will be.

	void checkLines(int[][22]); // Check for any complete lines.
	void deleteLine(int, int[][22]); // Delete a line and move
	                                 // everything above it down.

	void resetLines(); // Reset the value of lines to 0.
	int getLines(); // Return the value of lines.
	bool gameOver(); // Return the boolean value indicating if the
	                 // game is over or not.

private:
	int shapeID; // Value holding the ID (color and state) of a block.
	int lines; // Value holding the number of lines completed.

	Location block[4]; // Location array for the current falling shape.
	Location temp[4]; // Temporary Location array for the current
	                  // falling shape.
	Location preview[4]; // Shows where the shape will be.

	bool over; // Indicates if the game has been lost yet.
};
