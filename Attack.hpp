#ifndef _ATTACK_HPP_
#define _ATTACK_HPP_
#include "Constants.hpp"
#include "Game.hpp"
#include "Point.hpp"
#include "Frames.hpp"
class Attack
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