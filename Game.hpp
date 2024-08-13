#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "Constants.hpp"
#include "Point.hpp"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "MoveWay.hpp"
using namespace sf;
class Game
{
public:
	Game()
	{
		Start();
	}
	void Start();
	void CrChessDesk();
	void CrPoints();
	void CrSprites(Vector2i mousePos);
	void SetFrame();
	int MakeMove = 1;
	int Time = 1;
	void WrMove();
	void WrFigure();
	void IfChoose(Vector2i mousePos);
	void CrWays(Vector2i mousePos);
	void ChangePlace(int xM, int yM, int xN, int yN);
	void SelWays(Vector2i mousePos, int i, int j, int x, int y);
	void SelWays(Vector2i mousePos, int i, int j, int x, int y, std::string zero);
	void SelWays(Vector2i mousePos, int i, int j, int x, int y, double zero);
	void SelWays(Vector2i mousePos, int i, int j, int x, int y, int step);
	void SelWays(Vector2i mousePos, int i, int j, int x, int y, float zero);
	void Castling(int xM, int yM, int xN, int yN, int step);
	void CanDeath();
	void ChangeFigure(int xM, int yM, int color, Vector2i mousePos);
	void Shah();
	bool WhCheckmate = false;
	bool BlCheckmate = false;
private:

};
#endif

