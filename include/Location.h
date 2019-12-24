/*
This class stores X and Y choordinates of a object.
You may request X or Y choordinates, set X and Y choordinates and
add or subtract to the value of the choordinates.
*/
#pragma once
class Location
{
public:
	Location(void);
	~Location(void);

	void setXY(int, int); // Sets the X and Y choordinate.
	void setX(int); // Sets the X choordinate.
	void setY(int); // Sets the Y choordinate.
	void setPrevX(int); // Stores the previous X choordinate.
	void setPrevY(int); // Stores the previous X choordinate.

	int getX(); // Returns the X choordinate.
	int getY(); // Returns the Y choordinate.
	int getPrevX(); // Returns the Previous X choordinate.
	int getPrevY(); // Returns the Previous Y choordinate.

	void move(int, int); // Allows you to move the choordinates.
	                     //( delta x, delta y )

private:
	int xCoord, yCoord; // Values storing X and Y choord values.
	int prevX, prevY; // Values storing the previous x and y choords.
};
