#ifndef _MOVEWAY_HPP_
#define _MOVEWAY_HPP_
#include "Constants.hpp"
#include "Game.hpp"
#include "Point.hpp"
#include "Frames.hpp"
class MoveWay
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

};

#endif
