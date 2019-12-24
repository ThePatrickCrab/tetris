#include "Location.h"

// Set variables to 0
Location::Location(void)
{
	xCoord = yCoord = prevX = prevY = 1;
}

Location::~Location(void)
{}

/*
Take a given int value and store it as the x coordinate.
Values exceeding upper limit will be set to the upper limit.
Values below the lower limit will be set to the lower limit.
*/
void Location::setX(int x)
{
	setPrevX(xCoord);
	xCoord = x;
}

/*
Take a given int value and store it as the y coordinate.
Values exceeding upper limit will be set to the upper limit.
Values below the lower limit will be set to the lower limit.
*/
void Location::setY(int y)
{
	setPrevY(yCoord);
	yCoord = y;
}

// Set the location of the X and Y coordinates, this function follows
// the limit restrictions of setX() and setY().
void Location::setXY(int x, int y)
{
	setX(x);
	setY(y);
}

// Return the int value of the x coordinate.
int Location::getX()
{
	return xCoord;
}

// Return the int value of the y coordinate.
int Location::getY()
{
	return yCoord;
}

// Change the X and Y coordinates by the int values given.
void Location::move(int x, int y)
{
	setPrevX(xCoord);
	setPrevY(yCoord);
	xCoord += x;
	yCoord += y;
}

// Set the Previous X Coordinate
void Location::setPrevX(int x)
{
	prevX = x;
}

// Set the Previous Y Coordinate
void Location::setPrevY(int y)
{
	prevY = y;
}

// Return the previous X Coordinate
int Location::getPrevX()
{
	return prevX;
}

// Return the previous Y Coordinate
int Location::getPrevY()
{
	return prevY;
}