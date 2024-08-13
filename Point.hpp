#ifndef _POINT_HPP_
#define _POINT_HPP_
#include "Game.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MoveWay.hpp";
class Point
{
public:
	std::string name = " ";
	int color = 0;
	int arrX, arrY;
	int sizeX, sizeY;
	int moves = 0;
	bool choose = false;
	bool canMove = false;
	int sumKord;
	bool WhDethNear = false;
	bool BlDethNear = false;
	bool TakeOnMove = false;
};

#endif
