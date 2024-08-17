#ifndef _FRAMES_HPP_
#define _FRAMES_HPP_
#include "Point.hpp"
#include "Constants.hpp"
#include "Game.hpp"
class Frames
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
	//ЗДЕСЬ БЫЛ ИГОРЬ
};

#endif
