#include "Shape.h"
#include <time.h>
#include <cstdlib>


//Upon construction seed the random number generator and set lines to 0.
Shape::Shape(void)
{
	lines = 0;
	srand( time( NULL ) );
}


Shape::~Shape(void)
{
}

/*
Generate a shapeID and Coordinates of that shape. Call the protect
function to see if it is making the shape on used blocks then call the
updateGrid function.
*/
void Shape::generate( int grid[][22] )
{
	over = false;

	//Generate a random shapeID
	shapeID = rand() % 7 + 8;

	//Set the coordinates of a shape based on the shapeID
	switch( shapeID )
	{
		case 8:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 6, 1 );
			temp[2].setXY( 5, 2 );
			temp[3].setXY( 4, 2 );
			break;
		case 9:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 4, 1 );
			temp[2].setXY( 6, 1 );
			temp[3].setXY( 6, 2 );
			break;
		case 10:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 6, 1 );
			temp[2].setXY( 5, 2 );
			temp[3].setXY( 6, 2 );
			break;
		case 11:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 4, 1 );
			temp[2].setXY( 5, 2 );
			temp[3].setXY( 6, 2 );
			break;
		case 12:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 4, 1 );
			temp[2].setXY( 6, 1 );
			temp[3].setXY( 7, 1 );
			break;
		case 13:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 4, 1 );
			temp[2].setXY( 6, 1 );
			temp[3].setXY( 4, 2 );
			break;
		case 14:
			temp[0].setXY( 5, 1 );
			temp[1].setXY( 4, 1 );
			temp[2].setXY( 5, 2 );
			temp[3].setXY( 6, 1 );
			break;
		default:
			break;
	}


	//If the shape is put on top of another shape then set over to true.
	if( protect( grid ) )
		over = true;
}


/*
Sets the temp location left or right based on the boolean value passed
to the function. It then calls the protect function and the updateGrid
function.
*/
void Shape::move( bool dir, int grid[][22] )
{
	for( int i = 0; i < 4; i++ )
	{
		if( dir )
			temp[i].setXY( block[i].getX() + 1, block[i].getY() );

		else
			temp[i].setXY( block[i].getX() - 1, block[i].getY() );	
	}
	
	protect( grid );
}

/*
Sets the temp location rotated clockwise or counterclockwise based on a
boolean value passed to the function. It then calls the protect function
and the updateGrid function.
*/
void Shape::rotate( bool clockwise, int grid[][22] )
{
	int xOrigin = block[0].getX();
	int yOrigin = block[0].getY();
	int x, y;

	if( clockwise )
		for( int i = 0; i < 4; i++ )
		{
			x = block[i].getX();
			y = block[i].getY();

			temp[i].setX( xOrigin + yOrigin - y );
			temp[i].setY( x + yOrigin - xOrigin );
		}

	else
		for( int i = 0; i < 4; i++ )
		{
			x = block[i].getX();
			y = block[i].getY();

			temp[i].setX( y + xOrigin - yOrigin );
			temp[i].setY( yOrigin + xOrigin - x );
		}
	
	protect( grid );
}

//Sets the temp location 1 block down and then calls the protect and
//updateGrid functions.
void Shape::drop( int grid[][22] )
{
	for( int i = 0; i < 4; i++ )
		temp[i].setXY( block[i].getX(), block[i].getY() + 1 );

	updateGrid( protect( grid ), grid );
}

//Same as drop but it drops the shape until it cannot go down any
//further.
void Shape::quickDrop( int grid[][22] )
{	
	bool done = false;

	do
	{
		for( int i = 0; i < 4; i++ )
			temp[i].setXY( block[i].getX(), block[i].getY() + 1 );

		done = protect( grid );
		updateGrid( done, grid );

	}while( !done );
}

/*
If any of the temporary values are in the same location as a block
already on the grid then return with a true value. If not then set the
block coordinates the same as the temp coordinates and return false.
*/
bool Shape::protect( int grid[][22] )
{
	for( int i = 0; i < 4; i++ )
		if( grid[temp[i].getX()][temp[i].getY()] < 7 )
			return true;

	for( int i = 0; i < 4; i++ )
		block[i].setXY( temp[i].getX(), temp[i].getY() );

	return false;
}

/*
If the bool value passed to this function is false then set the previous
position of the blocks to the background and the new location to
whatever the shapeID is, then return. Otherwise set a permID based on
the shapeID then call the generate function. Set a permanent location on
the grid with the previous locations of block and the permID value
determined earlier.
*/
void Shape::updateGrid( bool done, int grid[][22] )
{
	if( !done )
	{
		dropPreview( grid );

		for( int i = 0; i < 4; i++ )
			grid[preview[i].getX()][preview[i].getY()] = 15;

		for( int i = 0; i < 4; i++ )
			grid[block[i].getX()][block[i].getY()] = shapeID;

		return;
	}	
	
	int permID = shapeID - 8;
	generate( grid );

	for( int i = 0; i < 4; i++ )
	{
		grid[block[i].getPrevX()][block[i].getPrevY()] = permID;
	}
		
	checkLines( grid );
}

//Check for any complete lines and call the delete line function when a
//complete line is found.
void Shape::checkLines( int grid[][22] )
{
	int blocks;
	
	for( int j = 1; j < 21; j++ )
	{
		blocks = 0;
		
		for( int i = 1; i < 11; i++ )
			if( grid[i][j] < 7 )
				blocks++;
				
		if( blocks == 10 )
			deleteLine( j--, grid );
	}	
}

//Deletes the indicated line, and increments the value of the variable
//lines.
void Shape::deleteLine( int y, int grid[][22] )
{
	for( int j = y; j > 1; j-- )
		for( int i = 1; i < 11; i++ )
			grid[i][j] = grid[i][j - 1];
			
	
	for( int i = 1; i < 11; i++ )
		grid[i][1] = 7;
		
	for( int i = 0; i < 4; i++ )
		block[i].setPrevY( block[i].getY() + 1 );
		
	lines++;
}

//Resets the value of the variable lines to 0.
void Shape::resetLines()
{
	lines = 0;
}

//Returns the current number of lines.
int Shape::getLines()
{
	return lines;
}

//Returns the boolean value over.
bool Shape::gameOver()
{
	return over;
}

//Shows where the shape will be if dropped straight down.
void Shape::dropPreview( int grid[][22] )
{
	bool x = true;

	for( int i = 0; i < 4; i++ )
		temp[i].setXY( block[i].getX(), block[i].getY() );

	while( x )
	{
		for( int i = 0; i < 4; i++ )
			temp[i].move( 0, 1 );

		for( int i = 0; i < 4; i++ )
			if( grid[temp[i].getX()][temp[i].getY()] < 7 )
				x = false;
	}

	for( int i = 0; i < 4; i++ )
		preview[i].setXY( temp[i].getX(), temp[i].getY() - 1 );
}