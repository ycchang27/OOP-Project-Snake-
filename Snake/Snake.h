/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, Jose Sandoval, Edwin Ramirez
	Purpose: Represent a snake object
*/

#ifndef _SNAKE_H
#define _SNAKE_H

#include "Square.h"
#include <vector>
#include <algorithm>

using namespace std;

class Snake
{
private:
	// Private instance variables:

	// Snake's body (head is at index 0)
	vector<Square> snake;

	// Color of the snake
	double r, g, b;

public:
	// Constructor:

	// Insert a square into the vector (Represents the head).
	// Also insert tail and body in the middle;
	// The square (with side length 0.1) should be at the starting position.
	// Default color for snake would be white (1.0, 1.0, 1.0)
	Snake() : r(1.0), g(1.0), b(1.0)
	{
		// code here...
		snake.push_back(Square());
		snake.push_back(Square(0.0,-0.1));
		snake.push_back(Square(0.0, -0.2));
	}

	// Same except that color is specified
	Snake(double r, double g, double b)
	{
		// code here...
		this->r = r;
		this->g = g;
		this->b = b;
	}

	// Public methods:

	// Insert a square into the vector...
	// First, get the location of the last square of the vector (size-1).
	// Second, create a square offsetted by 0.1 from the last square (Make sure that
	// the location is valid). Then, push back into the vector
	void grow()
	{
		// code here...
		double lastX;
		double lastY;
		double slastX;
		double slastY;
		double xOffset;
		double yOffset;
		double x;
		double y;

		snake[snake.size() - 1].getLocation(lastX, lastY);
		snake[snake.size() - 2].getLocation(slastX, slastY);
		x = lastX;
		y = lastY;

		// decide what direction location should be shifted towards based on what current direction the last tail is currently in

		xOffset = slastX - lastX;
		yOffset = slastY - lastY;

		if (xOffset > 0)
			x -= 0.1;
		else if (xOffset < 0)
			x += 0.1;
		else if (yOffset > 0)
			y -= 0.1;
		else if (yOffset < 0)
			y += 0.1;
		
		if (x >= 1.0)
		{
			x -= 0.1;
			y -= 0.1;
		}
		else if (x <= -1)
		{
			x += 0.1;
			y -= 0.1;
		}

		if (y >= 1.0)
		{
			x -= 0.1;
			y -= 0.1;
		}
		else if (y <= -1)
		{
			x += 0.1;
			y += 0.1;
		}
		// check if location is valid first before putting in
		snake.push_back(Square(x, y));
	}

	// Move the snake by 0.1 in a specified direction...
	// First, store the head's (index = 0) location (There is a method called getLocation(...)).
	// Second, move the head to the new location and have its body/tail move to its 
	// previous location (the coordinates that just got stored). Remember that there is
	// a method that makes the head/body/tail move called move(...).
	// Third, repeat this process until all snake parts have moved to the new location.
	// Read Square.h for more details about the given methods.
	void move(Direction direction)
	{
		// code here...
		Direction myDirection = direction;
		double cX;
		double cY;
		double nX;
		double nY;
		double xOffset;
		double yOffset;

		// add check to make sure doesn't go in opposite direction of where it's currently heading
		snake[0].getLocation(cX, cY);
		snake[1].getLocation(nX, nY);

		xOffset = cX - nX;
		yOffset = cY - nY;

		if (xOffset > 0)
			myDirection = West;
		else if (xOffset < 0)
			myDirection = East;
		else if (yOffset > 0)
			myDirection = North;
		else if (yOffset < 0)
			myDirection = South;

		if ((myDirection == North && direction == South) || (myDirection == South && direction == North)
			|| (myDirection == West && direction == East) || (myDirection == East && direction == West))
			myDirection = direction;

		for (int i = 0; i < snake.size(); i++)
		{
			snake[i].getLocation(cX, cY);
			snake[i].move(myDirection, 0.1);

			if ((i + 1) >= snake.size())
				break;

			snake[i + 1].getLocation(nX, nY);

			xOffset = cX - nX;
			yOffset = cY - nY;

			if (xOffset > 0)
				myDirection = West;
			else if (xOffset < 0)
				myDirection = East;
			else if (yOffset > 0)
				myDirection = North;
			else if (yOffset < 0)
				myDirection = South;
		}
	}

	// Draw the snake...
	// For each square in the vector and call draw function. Read Square.h for more details
	void draw()
	{
		// code here...
		for_each(snake.begin(),snake.end(),drawEach);
	}
	void drawEach(Square& s)
	{
		s.draw(r,g,b);
	}
};

#endif // _SNAKE_H