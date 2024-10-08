#include "Game.hpp"
#include "Frames.hpp"
#include "Button.hpp"
#include "Attack.hpp"
using namespace sf;
Point Box[height][length];
Point Dox[height][length];
Frames Places[height][length];
MoveWay Ways[height][length];
Attack Path[height][length];
bool WhKingInDang = false;
bool BlKingInDang = false;
int kingWay = 0;
sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window");
int figure = -1;
int bestPuwn = -1;
int schet = 1;
bool check = false;
bool WhDeffCheck = false;
bool BlDeffCheck = false;
bool menu = true;
bool pause = false;
int mainSumKord = -1;
std::string mainName = " ";
int mainMoves = 0;
int mainColor = 0;
int nextSumKord = -1;
std::string nextName = " ";
int nextMoves = 0;
int nextColor = 0;
void Game::CrChessDesk()
{
	//Render window(sf::VideoMode(1920, 1080), "SFML Window");
	RenderWindow& win2 = window;
	Image heroimage;
	heroimage.loadFromFile("ChessDesk.png");

	Texture herotexture;
	herotexture.loadFromImage(heroimage);

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setPosition(510, 25);

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);
		window.clear(Color::White);
		if (menu)
		{
			Menu(mousePos);
		}
		else
		{
			if (pause)
			{
				Pause(mousePos);
			}
			else
			{
				if (!BlCheckmate && !WhCheckmate)
				{
					if (WhKingInDang || BlKingInDang)
					{
						if (WhKingInDang && Time == -1)
						{
							Return();
						}
						else if (BlKingInDang && Time == 1)
						{
							Return();
						}
					}
					window.draw(herosprite);
					WrMove();
					Shah();
					CanDeath();
					CrSprites(mousePos);
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < length; j++)
						{
							if (Box[i][j].name == "BlPuwn.png")
							{
								if (i == 7)
								{
									bestPuwn = Box[i][j].sumKord;
									ChangeFigure(i, j, Box[i][j].color, mousePos);
								}
							}
							else if (Box[i][j].name == "WhPuwn.png")
							{
								if (i == 0)
								{
									bestPuwn = Box[i][j].sumKord;
									ChangeFigure(i, j, Box[i][j].color, mousePos);
								}
							}
						}
					}
					if (check)
					{
						WrPath();
						WrCheck(mousePos);
					}
					IfChoose(mousePos);
					window.display();
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < length; j++)
						{
							if (figure == Box[i][j].sumKord)
							{
								Box[i][j].choose = true;
							}
						}
					}
				}
				else
				{
					if (BlCheckmate)
					{

						Font font;
						font.loadFromFile("Sunday-Regular.ttf");
						Text text("", font, 200);
						text.setFillColor(sf::Color::Black);
						text.setStyle(sf::Text::Bold);
						text.setString("Black Won");
						text.setPosition(375, 100);
						Image revImage;
						revImage.loadFromFile("Revard.png");
						Texture revTexture;
						revTexture.loadFromImage(revImage);
						Sprite revSprite;
						revSprite.setTexture(revTexture);
						revSprite.setPosition(810, 500);
						sf::RectangleShape shape(sf::Vector2f(250, 150));
						shape.setPosition(100, 800);
						shape.setFillColor(Color::White);
						window.draw(shape);
						Font exfont;//шрифт 
						exfont.loadFromFile("Sunday-Regular.ttf");
						Text extext("", exfont, 100);
						extext.setFillColor(sf::Color::Black);
						extext.setStyle(sf::Text::Bold);
						extext.setString("Exit");
						extext.setPosition(100, 800);
						window.draw(extext);
						window.draw(herosprite);
						window.draw(revSprite);
						window.draw(extext);
						window.draw(text);
						window.display();
						if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
						{
							window.close();
						}
					}
					else if (WhCheckmate)
					{

						Font font;
						font.loadFromFile("Sunday-Regular.ttf");
						Text text("", font, 200);
						text.setFillColor(sf::Color::Black);
						text.setStyle(sf::Text::Bold);
						text.setString("White Won");
						text.setPosition(375, 100);
						Image revImage;
						revImage.loadFromFile("Revard.png");
						Texture revTexture;
						revTexture.loadFromImage(revImage);
						Sprite revSprite;
						revSprite.setTexture(revTexture);
						revSprite.setPosition(810, 500);
						sf::RectangleShape shape(sf::Vector2f(250, 150));
						shape.setPosition(100, 800);
						shape.setFillColor(Color::White);
						window.draw(shape);
						Font exfont;
						exfont.loadFromFile("Sunday-Regular.ttf");
						Text extext("", exfont, 100);
						extext.setFillColor(sf::Color::Black);
						extext.setStyle(sf::Text::Bold);
						extext.setString("Exit");
						extext.setPosition(100, 800);
						window.draw(extext);
						window.draw(herosprite);
						window.draw(revSprite);
						window.draw(extext);
						window.draw(text);
						window.display();
						if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
						{
							window.close();
						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					pause = true;
					//window.close();
				}
			}
		}
	}
}

void Game::CrPoints()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Box[i][j].arrX = i;
			Box[i][j].arrY = j;
			Box[i][j].sumKord = i * 10 + j;
		}
	}
	Box[0][0].name = "BlTower.png";
	Box[0][0].color = -1;
	Box[0][0].sizeX = 545;
	Box[0][0].sizeY = 63;

	Box[0][1].name = "BlHorse.png";
	Box[0][1].color = -1;
	Box[0][1].sizeX = 645;
	Box[0][1].sizeY = 63;

	Box[0][2].name = "BlBishop.png";
	Box[0][2].color = -1;
	Box[0][2].sizeX = 745;
	Box[0][2].sizeY = 63;

	Box[0][3].name = "BlQueen.png";
	Box[0][3].color = -1;
	Box[0][3].sizeX = 845;
	Box[0][3].sizeY = 63;

	Box[0][4].name = "BlKing.png";
	Box[0][4].color = -1;
	Box[0][4].sizeX = 945;
	Box[0][4].sizeY = 63;

	Box[0][5].name = "BlBishop.png";
	Box[0][5].color = -1;
	Box[0][5].sizeX = 1045;
	Box[0][5].sizeY = 63;

	Box[0][6].name = "BlHorse.png";
	Box[0][6].color = -1;
	Box[0][6].sizeX = 1145;
	Box[0][6].sizeY = 63;

	Box[0][7].name = "BlTower.png";
	Box[0][7].color = -1;
	Box[0][7].sizeX = 1245;
	Box[0][7].sizeY = 63;

	Box[1][0].name = "BlPuwn.png";
	Box[1][0].color = -1;
	Box[1][0].sizeX = 545;
	Box[1][0].sizeY = 168;

	Box[1][1].name = "BlPuwn.png";
	Box[1][1].color = -1;
	Box[1][1].sizeX = 645;
	Box[1][1].sizeY = 168;

	Box[1][2].name = "BlPuwn.png";
	Box[1][2].color = -1;
	Box[1][2].sizeX = 745;
	Box[1][2].sizeY = 168;

	Box[1][3].name = "BlPuwn.png";
	Box[1][3].color = -1;
	Box[1][3].sizeX = 845;
	Box[1][3].sizeY = 168;

	Box[1][4].name = "BlPuwn.png";
	Box[1][4].color = -1;
	Box[1][4].sizeX = 945;
	Box[1][4].sizeY = 168;

	Box[1][5].name = "BlPuwn.png";
	Box[1][5].color = -1;
	Box[1][5].sizeX = 1045;
	Box[1][5].sizeY = 168;

	Box[1][6].name = "BlPuwn.png";
	Box[1][6].color = -1;
	Box[1][6].sizeX = 1145;
	Box[1][6].sizeY = 168;

	Box[1][7].name = "BlPuwn.png";
	Box[1][7].color = -1;
	Box[1][7].sizeX = 1245;
	Box[1][7].sizeY = 168;

	Box[2][0].sizeX = 545;
	Box[2][0].sizeY = 273;

	Box[2][1].sizeX = 645;
	Box[2][1].sizeY = 273;

	Box[2][2].sizeX = 745;
	Box[2][2].sizeY = 273;

	Box[2][3].sizeX = 845;
	Box[2][3].sizeY = 273;

	Box[2][4].sizeX = 945;
	Box[2][4].sizeY = 273;

	Box[2][5].sizeX = 1045;
	Box[2][5].sizeY = 273;

	Box[2][6].sizeX = 1145;
	Box[2][6].sizeY = 273;

	Box[2][7].sizeX = 1245;
	Box[2][7].sizeY = 273;
	//---------------------------

	Box[3][0].sizeX = 545;
	Box[3][0].sizeY = 378;
	Box[3][1].sizeX = 645;
	Box[3][1].sizeY = 378;
	Box[3][2].sizeX = 745;
	Box[3][2].sizeY = 378;
	Box[3][3].sizeX = 845;
	Box[3][3].sizeY = 378;
	Box[3][4].sizeX = 945;
	Box[3][4].sizeY = 378;
	Box[3][5].sizeX = 1045;
	Box[3][5].sizeY = 378;
	Box[3][6].sizeX = 1145;
	Box[3][6].sizeY = 378;
	Box[3][7].sizeX = 1245;
	Box[3][7].sizeY = 378;

	//---------------------------
	Box[4][0].sizeX = 545;
	Box[4][0].sizeY = 483;
	Box[4][1].sizeX = 645;
	Box[4][1].sizeY = 483;
	Box[4][2].sizeX = 745;
	Box[4][2].sizeY = 483;
	Box[4][3].sizeX = 845;
	Box[4][3].sizeY = 483;
	Box[4][4].sizeX = 945;
	Box[4][4].sizeY = 483;
	Box[4][5].sizeX = 1045;
	Box[4][5].sizeY = 483;
	Box[4][6].sizeX = 1145;
	Box[4][6].sizeY = 483;
	Box[4][7].sizeX = 1245;
	Box[4][7].sizeY = 483;

	//--------------------------
	Box[5][0].sizeX = 545;
	Box[5][0].sizeY = 588;
	Box[5][1].sizeX = 645;
	Box[5][1].sizeY = 588;
	Box[5][2].sizeX = 745;
	Box[5][2].sizeY = 588;
	Box[5][3].sizeX = 845;
	Box[5][3].sizeY = 588;
	Box[5][4].sizeX = 945;
	Box[5][4].sizeY = 588;
	Box[5][5].sizeX = 1045;
	Box[5][5].sizeY = 588;
	Box[5][6].sizeX = 1145;
	Box[5][6].sizeY = 588;
	Box[5][7].sizeX = 1245;
	Box[5][7].sizeY = 588;
	//-------------------------

	Box[6][0].name = "WhPuwn.png";
	Box[6][0].color = 1;
	Box[6][0].sizeX = 545;
	Box[6][0].sizeY = 693;

	Box[6][1].name = "WhPuwn.png";
	Box[6][1].color = 1;
	Box[6][1].sizeX = 645;
	Box[6][1].sizeY = 693;

	Box[6][2].name = "WhPuwn.png";
	Box[6][2].color = 1;
	Box[6][2].sizeX = 745;
	Box[6][2].sizeY = 693;

	Box[6][3].name = "WhPuwn.png";
	Box[6][3].color = 1;
	Box[6][3].sizeX = 845;
	Box[6][3].sizeY = 693;

	Box[6][4].name = "WhPuwn.png";
	Box[6][4].color = 1;
	Box[6][4].sizeX = 945;
	Box[6][4].sizeY = 693;

	Box[6][5].name = "WhPuwn.png";
	Box[6][5].color = 1;
	Box[6][5].sizeX = 1045;
	Box[6][5].sizeY = 693;

	Box[6][6].name = "WhPuwn.png";
	Box[6][6].color = 1;
	Box[6][6].sizeX = 1145;
	Box[6][6].sizeY = 693;

	Box[6][7].name = "WhPuwn.png";
	Box[6][7].color = 1;
	Box[6][7].sizeX = 1245;
	Box[6][7].sizeY = 693;
	//----------------------------

	Box[7][0].name = "WhTower.png";
	Box[7][0].color = 1;
	Box[7][0].sizeX = 545;
	Box[7][0].sizeY = 798;

	Box[7][1].name = "WhHorse.png";
	Box[7][1].color = 1;
	Box[7][1].sizeX = 645;
	Box[7][1].sizeY = 798;

	Box[7][2].name = "WhBishop.png";
	Box[7][2].color = 1;
	Box[7][2].sizeX = 745;
	Box[7][2].sizeY = 798;

	Box[7][3].name = "WhQueen.png";
	Box[7][3].color = 1;
	Box[7][3].sizeX = 845;
	Box[7][3].sizeY = 798;

	Box[7][4].name = "WhKing.png";
	Box[7][4].color = 1;
	Box[7][4].sizeX = 945;
	Box[7][4].sizeY = 798;

	Box[7][5].name = "WhBishop.png";
	Box[7][5].color = 1;
	Box[7][5].sizeX = 1045;
	Box[7][5].sizeY = 798;

	Box[7][6].name = "WhHorse.png";
	Box[7][6].color = 1;
	Box[7][6].sizeX = 1145;
	Box[7][6].sizeY = 798;

	Box[7][7].name = "WhTower.png";
	Box[7][7].color = 1;
	Box[7][7].sizeX = 1245;
	Box[7][7].sizeY = 798;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Dox[i][j].arrX = Box[i][j].arrX;
			Dox[i][j].arrY = Box[i][j].arrY;
			Dox[i][j].sumKord = Box[i][j].sumKord;
			Dox[i][j].name = Box[i][j].name;
			Dox[i][j].color = Box[i][j].color;
			Dox[i][j].sizeX = Box[i][j].sizeX;
			Dox[i][j].sizeY = Box[i][j].sizeY;
			Dox[i][j].moves = Box[i][j].moves;
		}
	}
}

void Game::CrSprites(Vector2i mousePos)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Image heroimage; //создаем объект Image (изображение)
			heroimage.loadFromFile(Box[i][j].name);//загружаем в него файл
			//Box[i][j].image = heroimage;
			Texture herotexture;//создаем объект Texture (текстура)
			herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
			//Box[i][j].texture = herotexture;
			Sprite herosprite;//создаем объект Sprite(спрайт)
			herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
			herosprite.setPosition(Box[i][j].sizeX, Box[i][j].sizeY);//задаем начальные координаты появления спрайта
			//Box[i][j].sprite = herosprite;
			window.draw(herosprite);//выводим спрайт на экран
			if (Box[i][j].color == MakeMove)
			{

				if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					figure = Box[i][j].sumKord;
				}
				else
				{
					continue;
				}
			}
		}
	}
}
void Game::SetFrame()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Places[i][j].name = "YeFrame.png";
			Places[i][j].sizeX = Box[i][j].sizeX;
			Places[i][j].sizeY = Box[i][j].sizeY;
			Image heroimage; //создаем объект Image (изображение)
			heroimage.loadFromFile(Places[i][j].name);//загружаем в него файл
			Texture herotexture;//создаем объект Texture (текстура)
			herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
			Sprite herosprite;//создаем объект Sprite(спрайт)
			herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
			herosprite.setPosition(Places[i][j].sizeX, Places[i][j].sizeY + 3);//задаем начальные координаты появления спрайта
			if (Box[i][j].choose)
			{
				window.draw(herosprite);//выводим спрайт на экран
			}
		}
	}
}
void Game::WrMove()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Font font;//шрифт 
	font.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	if (Time > 0)
	{
		text.setString("Move:\nWhite");//задает строку тексту
	}
	else if (Time < 0)
	{
		text.setString("Move:\nBlack");//задает строку тексту
	}

	text.setPosition(100, 50);//задаем позицию текста, центр камеры
	window.draw(text);//рисую этот текст
}
void Game::WrFigure()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Font font;//шрифт 
	font.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].sumKord == figure)
			{
				if (Box[i][j].name == "BlTower.png" || Box[i][j].name == "WhTower.png")
				{
					text.setString("Choose:\nRook");//задает строку тексту
				}
				else if (Box[i][j].name == "BlHorse.png" || Box[i][j].name == "WhHorse.png")
				{
					text.setString("Choose:\nKnight");//задает строку тексту
				}
				else if (Box[i][j].name == "BlPuwn.png" || Box[i][j].name == "WhPuwn.png")
				{
					text.setString("Choose:\nPawn");//задает строку тексту
				}
				else if (Box[i][j].name == "BlBishop.png" || Box[i][j].name == "WhBishop.png")
				{
					text.setString("Choose:\nBishop");//задает строку тексту
				}
				else if (Box[i][j].name == "BlKing.png" || Box[i][j].name == "WhKing.png")
				{
					text.setString("Choose:\nKing");//задает строку тексту
				}
				else if (Box[i][j].name == "BlQueen.png" || Box[i][j].name == "WhQueen.png")
				{
					text.setString("Choose:\nQueen");//задает строку тексту
				}
			}
		}
	}

	text.setPosition(100, 300);//задаем позицию текста, центр камеры
	window.draw(text);//рисую этот текст
}
void Game::IfChoose(Vector2i mousePos)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].choose)
			{
				MakeMove = 0;
				WrFigure();
				SetFrame();
				if (!WhKingInDang && !BlKingInDang)
				{
					sf::RectangleShape shape(sf::Vector2f(400, 150));
					shape.setPosition(1470, 60);
					shape.setFillColor(Color::White);
					window.draw(shape);
					Font font;//шрифт 
					font.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
					Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
					text.setFillColor(sf::Color::Black);
					text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
					text.setString("Cansel");//задает строку тексту
					text.setPosition(1500, 60);//задаем позицию текста, центр камеры
					window.draw(text);//рисую этот текст
					if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Box[i][j].choose = false;
						MakeMove = Time;
						figure = -1;
					}
					else
					{
						//sf::RectangleShape shape(sf::Vector2f(400, 150));
						//shape.setPosition(1470, 60);
						//shape.setFillColor(Color::White);
						//window.draw(shape);
						//Font font;//шрифт 
						//font.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
						//Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
						//text.setFillColor(sf::Color::Black);
						//text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
						//text.setString("Cansel");//задает строку тексту
						//text.setPosition(1500, 60);//задаем позицию текста, центр камеры
						//window.draw(text);//рисую этот текст
						CrWays(mousePos);
					}
				}
				else
				{
					sf::RectangleShape shape(sf::Vector2f(400, 150));
					shape.setPosition(1470, 60);
					shape.setFillColor(Color::White);
					window.draw(shape);
					Font font;//шрифт 
					font.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
					Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
					text.setFillColor(sf::Color::Black);
					text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
					text.setString("Cansel");//задает строку тексту
					text.setPosition(1500, 60);//задаем позицию текста, центр камеры
					window.draw(text);
					if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Box[i][j].choose = false;
						MakeMove = Time;
						figure = -1;
					}
					else
					{
						CrWays(mousePos);
					}
					WhKingInDang = false;
					BlKingInDang = false;
					check = false;
				}
			}
		}
	}
}
void Game::CrWays(Vector2i mousePos)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].name == "WhPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				if (Box[i][j].moves == 0)
				{
					for (int z = -1; z >= -2; z--)
					{
						if (Box[i + z][j].color == 0)
						{
							if (z == -2)
							{
								SelWays(mousePos, i, j, i + z, j, " ");
							}
							else
							{
								SelWays(mousePos, i, j, i + z, j);
							}
						}
						else
						{
							break;
						}
					}
					if (Box[i - 1][j - 1].color == Box[i][j].color - 2)
					{
						SelWays(mousePos, i, j, i - 1, j - 1);
					}
					if (Box[i - 1][j + 1].color == Box[i][j].color - 2)
					{
						SelWays(mousePos, i, j, i - 1, j + 1);
					}
				}
				else
				{
					for (int z = -1; z >= -1; z--)
					{
						if (Box[i + z][j].color == 0)
						{
							SelWays(mousePos, i, j, i + z, j);
						}
						else
						{
							break;
						}
					}
					if (Box[i - 1][j - 1].color == Box[i][j].color - 2)
					{
						SelWays(mousePos, i, j, i - 1, j - 1);
					}
					if (Box[i - 1][j + 1].color == Box[i][j].color - 2)
					{
						SelWays(mousePos, i, j, i - 1, j + 1);
					}
					if (i == 3)
					{
						if (Box[i][j + 1].color == Box[i][j].color - 2 && Box[i][j + 1].TakeOnMove)
						{
							SelWays(mousePos, i, j, i - 1, j + 1, 1.0);
						}
						if (Box[i][j - 1].color == Box[i][j].color - 2 && Box[i][j - 1].TakeOnMove)
						{
							SelWays(mousePos, i, j, i - 1, j - 1, -1.0);
						}
					}

				}
			}
			if (Box[i][j].name == "BlPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				if (Box[i][j].moves == 0)
				{
					for (int z = 1; z <= 2; z++)
					{
						if (Box[i + z][j].color == 0)
						{
							if (z == 2)
							{
								SelWays(mousePos, i, j, i + z, j, " ");
							}
							else
							{
								SelWays(mousePos, i, j, i + z, j);
							}
						}
						else
						{
							break;
						}
					}
					if (Box[i + 1][j - 1].color == Box[i][j].color + 2)
					{
						SelWays(mousePos, i, j, i + 1, j - 1);
					}
					if (Box[i + 1][j + 1].color == Box[i][j].color + 2)
					{
						SelWays(mousePos, i, j, i + 1, j + 1);
					}
				}
				else
				{
					for (int z = 1; z <= 1; z++)
					{

						if (Box[i + z][j].color == 0)
						{
							SelWays(mousePos, i, j, i + z, j);
						}
						else
						{
							break;
						}
					}
					if (Box[i + 1][j - 1].color == Box[i][j].color + 2)
					{
						SelWays(mousePos, i, j, i + 1, j - 1);
					}
					if (Box[i + 1][j + 1].color == Box[i][j].color + 2)
					{
						SelWays(mousePos, i, j, i + 1, j + 1);
					}
					if (i == 4)
					{
						if (Box[i][j + 1].color == Box[i][j].color + 2 && Box[i][j + 1].TakeOnMove)
						{
							SelWays(mousePos, i, j, i + 1, j + 1, 1.0);
						}
						if (Box[i][j - 1].color == Box[i][j].color + 2 && Box[i][j - 1].TakeOnMove)
						{
							SelWays(mousePos, i, j, i + 1, j - 1, -1.0);
						}
					}
				}
			}
			if (Box[i][j].name == "WhBishop.png" || Box[i][j].name == "BlBishop.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				for (int z = -1; i + z > -1 && j + z > -1; z--)
				{
					if (Box[i + z][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + z);
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + z);
						break;
					}
					else
					{
						break;
					}
				}
				int g = 1;
				for (int z = -1; i + z > -1 && j + g < 8; z--)
				{
					if (Box[i + z][j + g].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + g);
					}
					else if (Box[i + z][j + g].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + g);
						break;
					}
					else
					{
						break;
					}
					g++;
				}
				int h = -1;
				for (int z = 1; i + z < 8 && j + h > -1; z++)
				{
					if (Box[i + z][j + h].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + h);
					}
					else if (Box[i + z][j + h].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + h);
						break;
					}
					else
					{
						break;
					}
					h--;
				}
				for (int z = 1; i + z < 8 && j + z < 8; z++)
				{
					if (Box[i + z][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + z);
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + z);
						break;
					}
					else
					{
						break;
					}
				}
			}
			if (Box[i][j].name == "WhHorse.png" || Box[i][j].name == "BlHorse.png")
			{
				if (Box[i - 2][j - 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 2, j - 1);
				}
				if (Box[i - 2][j + 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 2, j + 1);
				}
				if (Box[i - 1][j - 2].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 1, j - 2);
				}
				if (Box[i + 1][j - 2].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 1, j - 2);
				}
				if (Box[i + 2][j - 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 2, j - 1);
				}
				if (Box[i + 2][j + 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 2, j + 1);
				}
				if (Box[i - 1][j + 2].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 1, j + 2);
				}
				if (Box[i + 1][j + 2].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 1, j + 2);
				}
			}
			if (Box[i][j].name == "WhQueen.png" || Box[i][j].name == "BlQueen.png")
			{
				for (int z = -1; i + z > -1 && j + z > -1; z--)
				{
					if (Box[i + z][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + z);
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + z);
						break;
					}
					else
					{
						break;
					}
				}
				int g = 1;
				for (int z = -1; i + z > -1 && j + g < 8; z--)
				{
					if (Box[i + z][j + g].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + g);
					}
					else if (Box[i + z][j + g].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + g);
						break;
					}
					else
					{
						break;
					}
					g++;
				}
				int h = -1;
				for (int z = 1; i + z < 8 && j + h > -1; z++)
				{
					if (Box[i + z][j + h].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + h);
					}
					else if (Box[i + z][j + h].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + h);
						break;
					}
					else
					{
						break;
					}
					h--;
				}
				for (int z = 1; i + z < 8 && j + z < 8; z++)
				{
					if (Box[i + z][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j + z);
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j + z);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = -1; i + z > -1; z--)
				{
					if (Box[i + z][j].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j);
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; i + z < 8; z++)
				{
					if (Box[i + z][j].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j);
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; j + z < 8; z++)
				{
					if (Box[i][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i, j + z);
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i, j + z);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = -1; j + z > -1; z--)
				{
					if (Box[i][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i, j + z);
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i, j + z);
						break;
					}
					else
					{
						break;
					}
				}
			}
			if (Box[i][j].name == "WhKing.png" || Box[i][j].name == "BlKing.png")
			{
				if (Box[i][j - 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i, j - 1);
				}
				if (Box[i][j + 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i, j + 1);
				}
				if (Box[i + 1][j + 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 1, j + 1);
				}
				if (Box[i + 1][j - 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 1, j - 1);
				}
				if (Box[i - 1][j - 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 1, j - 1);
				}
				if (Box[i - 1][j + 1].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 1, j + 1);
				}
				if (Box[i + 1][j].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i + 1, j);
				}
				if (Box[i - 1][j].color != Box[i][j].color)
				{
					SelWays(mousePos, i, j, i - 1, j);
				}
				for (int z = 0; z < height; z++)
				{
					for (int p = 0; p < length; p++)
					{
						if (Box[z][p].name == "BlTower.png" && Box[z][p].color == Box[i][j].color)
						{
							int n = 0;
							int step = 0;
							if (Box[z][p].moves == 0 && Box[i][j].moves == 0)
							{
								if (Box[z][p].sumKord < Box[i][j].sumKord)
								{
									step = 1;
								}
								else if (Box[z][p].sumKord > Box[i][j].sumKord)
								{
									step = -1;
								}
								for (int r = p + step; r != j; r = r + step)
								{
									if (Box[i][r].name != " ")
									{
										n++;
									}
								}
								if (n == 0)
								{
									SelWays(mousePos, z, p, i, j, step);
								}
							}

						}
						else if (Box[z][p].name == "WhTower.png" && Box[z][p].color == Box[i][j].color)
						{
							int n = 0;
							int step = 0;
							if (Box[z][p].moves == 0 && Box[i][j].moves == 0)
							{
								if (Box[z][p].sumKord < Box[i][j].sumKord)
								{
									step = 1;
								}
								else if (Box[z][p].sumKord > Box[i][j].sumKord)
								{
									step = -1;
								}
								for (int r = p + step; r != j; r = r + step)
								{
									if (Box[i][r].name != " ")
									{
										n++;
									}
								}
								if (n == 0)
								{
									SelWays(mousePos, z, p, i, j, step);
								}
							}
						}
					}
				}
			}
			if (Box[i][j].name == "WhTower.png" || Box[i][j].name == "BlTower.png")
			{
				for (int z = -1; i + z > -1; z--)
				{
					if (Box[i + z][j].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j);
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; i + z < 8; z++)
				{
					if (Box[i + z][j].color == 0)
					{
						SelWays(mousePos, i, j, i + z, j);
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + z, j);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; j + z < 8; z++)
				{
					if (Box[i][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i, j + z);
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i, j + z);
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = -1; j + z > -1; z--)
				{
					if (Box[i][j + z].color == 0)
					{
						SelWays(mousePos, i, j, i, j + z);
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i, j + z);
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

void Game::ChangePlace(int xM, int yM, int xN, int yN)
{
	mainSumKord = Box[xM][yM].sumKord;
	mainName = Box[xM][yM].name;
	mainMoves = Box[xM][yM].moves;
	mainColor = Box[xM][yM].color;
	nextSumKord = Box[xN][yN].sumKord;
	nextName = Box[xN][yN].name;
	nextMoves = Box[xN][yN].moves;
	nextColor = Box[xN][yN].color;
	Box[xN][yN].name = Box[xM][yM].name;
	Box[xN][yN].color = Box[xM][yM].color;
	Box[xN][yN].moves = Box[xM][yM].moves + 1;
	Box[xN][yN].choose = false;
	Box[xM][yM].name = " ";
	Box[xM][yM].color = 0;
	Box[xM][yM].moves = 0;
	Box[xM][yM].choose = false;
	/*for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].name == "BlPuwn.png")
			{
				if (i == 7)
				{
					ChangeFigure(i, j, Box[i][j].color);
				}
			}
			else if (Box[i][j].name == "WhPuwn.png")
			{
				if (i == 0)
				{
					ChangeFigure(i, j, Box[i][j].color);
				}
			}
		}
	}*/
	if (Time > 0)
	{
		Time = -1;
		MakeMove = Time;
		figure = -1;
	}
	else
	{
		Time = 1;
		MakeMove = Time;
		figure = -1;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Dox[i][j].arrX = Box[i][j].arrX;
			Dox[i][j].arrY = Box[i][j].arrY;
			Dox[i][j].sumKord = Box[i][j].sumKord;
			Dox[i][j].name = Box[i][j].name;
			Dox[i][j].color = Box[i][j].color;
			Dox[i][j].sizeX = Box[i][j].sizeX;
			Dox[i][j].sizeY = Box[i][j].sizeY;
			Dox[i][j].moves = Box[i][j].moves;
		}
	}
	CanDeath();
	Shah();
}

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
	{
			if (!check)
			{
				/*if (IsDang(i, j, x, y))
				{*/
					if (Box[i][j].sumKord == figure)
					{
						if (Box[x][y].name != "BlKing.png" && Box[x][y].name != "WhKing.png")
						{

								if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
								{
									/*MakeMove = Time;
									figure = -1;*/
								}
								else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
								{
									/*MakeMove = Time;
									figure = -1;*/
								}
								else
								{
									if (x == 0 && y == 5)
									{
										Ways[0][5].name = "BlFrame.png";
										Ways[0][5].name = "BlFrame.png";
										Ways[0][5].sizeX = Box[0][5].sizeX;
										Ways[0][5].sizeY = Box[0][5].sizeY;
										Image heroimage; //создаем объект Image (изображение)
										heroimage.loadFromFile(Ways[0][5].name);//загружаем в него файл
										Texture herotexture;//создаем объект Texture (текстура)
										herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
										Sprite herosprite;//создаем объект Sprite(спрайт)
										herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
										herosprite.setPosition(Ways[0][5].sizeX, Ways[0][5].sizeY);//задаем начальные координаты появления спрайта
										window.draw(herosprite);
										if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
										{
											ChangePlace(i, j, x, y);
											for (int g = 0; g < height; g++)
											{
												for (int h = 0; h < height; h++)
												{
													Box[g][h].TakeOnMove = false;
												}
											}
										}
									}
									else
									{
										Ways[x][y].name = "BlFrame.png";
										Ways[x][y].sizeX = Box[x][y].sizeX;
										Ways[x][y].sizeY = Box[x][y].sizeY;
										Image heroimage; //создаем объект Image (изображение)
										heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
										Texture herotexture;//создаем объект Texture (текстура)
										herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
										Sprite herosprite;//создаем объект Sprite(спрайт)
										herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
										herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
										window.draw(herosprite);
										if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
										{
											ChangePlace(i, j, x, y);
											for (int g = 0; g < height; g++)
											{
												for (int h = 0; h < height; h++)
												{
													Box[g][h].TakeOnMove = false;
												}
											}
										}
									}
								}
						}
					}
				//}
			}
			else
			{
				if ((Box[i][j].name == "WhKing.png" && WhKingInDang) || (Box[i][j].name == "BlKing.png" && BlKingInDang))
				{
					if (Box[x][y].name != "BlKing.png" && Box[x][y].name != "WhKing.png")
					{
						if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
						{
							/*MakeMove = Time;
							figure = -1;*/
						}
						else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
						{
							/*MakeMove = Time;
							figure = -1;*/
						}
						else
						{
							kingWay++;
							if (Box[i][j].sumKord == figure)
							{
								if (x == 0 && y == 5)
								{
									Ways[0][5].name = "BlFrame.png";
									Ways[0][5].name = "BlFrame.png";
									Ways[0][5].sizeX = Box[0][5].sizeX;
									Ways[0][5].sizeY = Box[0][5].sizeY;
									Image heroimage; //создаем объект Image (изображение)
									heroimage.loadFromFile(Ways[0][5].name);//загружаем в него файл
									Texture herotexture;//создаем объект Texture (текстура)
									herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
									Sprite herosprite;//создаем объект Sprite(спрайт)
									herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
									herosprite.setPosition(Ways[0][5].sizeX, Ways[0][5].sizeY);//задаем начальные координаты появления спрайта
									window.draw(herosprite);
									if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
									{
										ChangePlace(i, j, x, y);
										for (int g = 0; g < height; g++)
										{
											for (int h = 0; h < height; h++)
											{
												Box[g][h].TakeOnMove = false;
											}
										}
									}
								}
								else
								{
									Ways[x][y].name = "BlFrame.png";
									Ways[x][y].sizeX = Box[x][y].sizeX;
									Ways[x][y].sizeY = Box[x][y].sizeY;
									Image heroimage; //создаем объект Image (изображение)
									heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
									Texture herotexture;//создаем объект Texture (текстура)
									herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
									Sprite herosprite;//создаем объект Sprite(спрайт)
									herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
									herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
									window.draw(herosprite);
									if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
									{
										ChangePlace(i, j, x, y);
										for (int g = 0; g < height; g++)
										{
											for (int h = 0; h < height; h++)
											{
												Box[g][h].TakeOnMove = false;
											}
										}
									}
								}
							}
						}
					}
				}
				else if (Path[x][y].name == "RedFrame.png" && Box[i][j].color == Time)
				{
					kingWay++;
					if (Box[i][j].sumKord == figure)
					{
						if (Box[x][y].name != "BlKing.png" && Box[x][y].name != "WhKing.png")
						{
							if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
							{
								/*MakeMove = Time;
								figure = -1;*/
							}
							else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
							{
								/*MakeMove = Time;
								figure = -1;*/
							}
							else
							{
								if (x == 0 && y == 5)
								{
									Ways[0][5].name = "BlFrame.png";
									Ways[0][5].name = "BlFrame.png";
									Ways[0][5].sizeX = Box[0][5].sizeX;
									Ways[0][5].sizeY = Box[0][5].sizeY;
									Image heroimage; //создаем объект Image (изображение)
									heroimage.loadFromFile(Ways[0][5].name);//загружаем в него файл
									Texture herotexture;//создаем объект Texture (текстура)
									herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
									Sprite herosprite;//создаем объект Sprite(спрайт)
									herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
									herosprite.setPosition(Ways[0][5].sizeX, Ways[0][5].sizeY);//задаем начальные координаты появления спрайта
									window.draw(herosprite);
									if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
									{
										ChangePlace(i, j, x, y);
										for (int g = 0; g < height; g++)
										{
											for (int h = 0; h < height; h++)
											{
												Box[g][h].TakeOnMove = false;
											}
										}
									}
								}
								else
								{
									Ways[x][y].name = "BlFrame.png";
									Ways[x][y].sizeX = Box[x][y].sizeX;
									Ways[x][y].sizeY = Box[x][y].sizeY;
									Image heroimage; //создаем объект Image (изображение)
									heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
									Texture herotexture;//создаем объект Texture (текстура)
									herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
									Sprite herosprite;//создаем объект Sprite(спрайт)
									herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
									herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
									window.draw(herosprite);
									if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
									{
										ChangePlace(i, j, x, y);
										for (int g = 0; g < height; g++)
										{
											for (int h = 0; h < height; h++)
											{
												Box[g][h].TakeOnMove = false;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		//}
	}
}
void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, double zero)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
	{
		if (!check)
		{
			if (Box[i][j].sumKord == figure)
			{
				if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
				{
					/*MakeMove = Time;
					figure = -1;*/
				}
				else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
				{
					//MakeMove = Time;
					//figure = -1;
				}
				else
				{
					Ways[x][y].name = "BlFrame.png";
					Ways[x][y].sizeX = Box[x][y].sizeX;
					Ways[x][y].sizeY = Box[x][y].sizeY;
					Image heroimage; //создаем объект Image (изображение)
					heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
					Texture herotexture;//создаем объект Texture (текстура)
					herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
					Sprite herosprite;//создаем объект Sprite(спрайт)
					herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
					herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
					window.draw(herosprite);
					int n;
					if (zero == 1.0)
					{
						n = 1;
					}
					else if (zero == -1.0)
					{
						n = -1;
					}
					if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						ChangePlace(i, j + n, x, y);
						if (Time > 0)
						{
							Time = -1;
							MakeMove = 0;
						}
						else
						{
							Time = 1;
							MakeMove = 0;
						}
						ChangePlace(i, j, x, y);
						for (int g = 0; g < height; g++)
						{
							for (int h = 0; h < height; h++)
							{
								Box[g][h].TakeOnMove = false;
							}
						}
					}
				}
			}
		}
		else
		{
			if (Path[x][y].name == "RedFrame.png" && Box[i][j].color == Time)
			{
				kingWay++;
				if (Box[i][j].sumKord == figure)
				{
					if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
					{
						/*MakeMove = Time;
						figure = -1;*/
					}
					else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
					{
						//MakeMove = Time;
						//figure = -1;
					}
					else
					{
						Ways[x][y].name = "BlFrame.png";
						Ways[x][y].sizeX = Box[x][y].sizeX;
						Ways[x][y].sizeY = Box[x][y].sizeY;
						Image heroimage; //создаем объект Image (изображение)
						heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
						Texture herotexture;//создаем объект Texture (текстура)
						herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
						Sprite herosprite;//создаем объект Sprite(спрайт)
						herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
						herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
						window.draw(herosprite);
						int n;
						if (zero == 1.0)
						{
							n = 1;
						}
						else if (zero == -1.0)
						{
							n = -1;
						}
						if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
						{
							ChangePlace(i, j + n, x, y);
							if (Time > 0)
							{
								Time = -1;
								MakeMove = 0;
							}
							else
							{
								Time = 1;
								MakeMove = 0;
							}
							ChangePlace(i, j, x, y);
							for (int g = 0; g < height; g++)
							{
								for (int h = 0; h < height; h++)
								{
									Box[g][h].TakeOnMove = false;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, std::string zero)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
	{
		if (!check)
		{
			if (Box[i][j].sumKord == figure)
			{
				if (Box[x][y].name != "BlKing.png" && Box[x][y].name != "WhKing.png")
				{
					if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
					{
						/*MakeMove = Time;
						figure = -1;*/
					}
					else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
					{
						//MakeMove = Time;
						//figure = -1;
					}
					else
					{
						Ways[x][y].name = "BlFrame.png";
						Ways[x][y].sizeX = Box[x][y].sizeX;
						Ways[x][y].sizeY = Box[x][y].sizeY;
						Image heroimage; //создаем объект Image (изображение)
						heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
						Texture herotexture;//создаем объект Texture (текстура)
						herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
						Sprite herosprite;//создаем объект Sprite(спрайт)
						herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
						herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
						window.draw(herosprite);
						if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
						{
							for (int g = 0; g < height; g++)
							{
								for (int h = 0; h < height; h++)
								{
									Box[g][h].TakeOnMove = false;
								}
							}
							Box[x][y].TakeOnMove = true;
							ChangePlace(i, j, x, y);
						}
					}
				}
			}
		}
		else
		{
			if (Path[x][y].name == "RedFrame.png" && Box[i][j].color == Time)
			{

				kingWay++;
				if (Box[i][j].sumKord == figure)
				{
					if (Box[x][y].name != "BlKing.png" && Box[x][y].name != "WhKing.png")
					{
						if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
						{
							/*MakeMove = Time;
							figure = -1;*/
						}
						else if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
						{
							//MakeMove = Time;
							//figure = -1;
						}
						else
						{
							Ways[x][y].name = "BlFrame.png";
							Ways[x][y].sizeX = Box[x][y].sizeX;
							Ways[x][y].sizeY = Box[x][y].sizeY;
							Image heroimage; //создаем объект Image (изображение)
							heroimage.loadFromFile(Ways[x][y].name);//загружаем в него файл
							Texture herotexture;//создаем объект Texture (текстура)
							herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
							Sprite herosprite;//создаем объект Sprite(спрайт)
							herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
							herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//задаем начальные координаты появления спрайта
							window.draw(herosprite);
							if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
							{
								for (int g = 0; g < height; g++)
								{
									for (int h = 0; h < height; h++)
									{
										Box[g][h].TakeOnMove = false;
									}
								}
								Box[x][y].TakeOnMove = true;
								ChangePlace(i, j, x, y);
							}
						}
					}
				}
			}
		}
	}
}

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, int step)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
	{
		if (Box[x][y].sumKord == figure)
		{
			if (Box[x][y].name == "BlKing.png" && Box[x][y - step * 2].WhDethNear)
			{
				/*MakeMove = Time;
				figure = -1;*/
			}
			else if (Box[x][y].name == "WhKing.png" && Box[x][y - step * 2].BlDethNear)
			{
				//MakeMove = Time;
				//figure = -1;
			}
			else
			{
				if (Box[x][y].color == 1 && WhKingInDang)
				{
					//MakeMove = Time;
					//figure = -1;
				}
				else if (Box[x][y].color == -1 && BlKingInDang)
				{
					//MakeMove = Time;
					//figure = -1;
				}
				else
				{
					Ways[x][y - step * 2].name = "BlFrame.png";
					Ways[x][y - step * 2].sizeX = Box[x][y - step * 2].sizeX;
					Ways[x][y - step * 2].sizeY = Box[x][y - step * 2].sizeY;
					Image heroimage; //создаем объект Image (изображение)
					heroimage.loadFromFile(Ways[x][y - step * 2].name);//загружаем в него файл
					Texture herotexture;//создаем объект Texture (текстура)
					herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
					Sprite herosprite;//создаем объект Sprite(спрайт)
					herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
					herosprite.setPosition(Ways[x][y - step * 2].sizeX, Ways[x][y - step * 2].sizeY);//задаем начальные координаты появления спрайта
					window.draw(herosprite);
					if (Mouse::isButtonPressed(Mouse::Left) && herosprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Castling(i, j, x, y, step);
						for (int g = 0; g < height; g++)
						{
							for (int h = 0; h < height; h++)
							{
								Box[g][h].TakeOnMove = false;
							}
						}
					}
				}
			}
		}
	}
}

void Game::SelWays(int i, int j, int x, int y, float zero)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
	{

		//if (Box[x][y].name != "BlKing.png" && Box[x][y].name != "WhKing.png")
		//{
		if (Box[i][j].name == "BlKing.png" && Box[x][y].WhDethNear)
		{
		}
		else
		{
			kingWay++;
		}
		if (Box[i][j].name == "WhKing.png" && Box[x][y].BlDethNear)
		{
		}
		else
		{
			kingWay++;
		}
		//}

	}
}

void Game::Castling(int xM, int yM, int xN, int yN, int step)
{

	Box[xN][yN - step].name = Box[xM][yM].name;
	Box[xN][yN - step].color = Box[xM][yM].color;
	Box[xN][yN - step].moves = Box[xM][yM].moves + 1;
	Box[xN][yN - step].choose = false;
	Box[xN][yN - step * 2].name = Box[xN][yN].name;
	Box[xN][yN - step * 2].color = Box[xN][yN].color;
	Box[xN][yN - step * 2].moves = Box[xN][yN].moves + 1;
	Box[xN][yN - step * 2].choose = false;
	Box[xM][yM].name = " ";
	Box[xM][yM].color = 0;
	Box[xM][yM].moves = 0;
	Box[xM][yM].choose = false;
	Box[xN][yN].name = " ";
	Box[xN][yN].color = 0;
	Box[xN][yN].moves = 0;
	Box[xN][yN].choose = false;
	if (Time > 0)
	{
		Time = -1;
		MakeMove = Time;
		figure = -1;
	}
	else
	{
		Time = 1;
		MakeMove = Time;
		figure = -1;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Dox[i][j].arrX = Box[i][j].arrX;
			Dox[i][j].arrY = Box[i][j].arrY;
			Dox[i][j].sumKord = Box[i][j].sumKord;
			Dox[i][j].name = Box[i][j].name;
			Dox[i][j].color = Box[i][j].color;
			Dox[i][j].sizeX = Box[i][j].sizeX;
			Dox[i][j].sizeY = Box[i][j].sizeY;
			Dox[i][j].moves = Box[i][j].moves;
		}
	}
	CanDeath();
}

void Game::CanDeath()
{

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Box[i][j].BlDethNear = false;
			Box[i][j].WhDethNear = false;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].name == "WhPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				if (Box[i][j].moves == 0)
				{
					if (i - 1 < 8 && i - 1 > -1 && j - 1 < 8 && j - 1 > -1)
					{
						Box[i - 1][j - 1].WhDethNear = true;
						if (Box[i - 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i - 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
						}
					}
					if (i - 1 < 8 && i - 1 > -1 && j + 1 < 8 && j + 1 > -1)
					{
						Box[i - 1][j + 1].WhDethNear = true;
						if (Box[i - 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i - 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
						}
					}
					
				}
				else
				{
					if (i - 1 < 8 && i - 1 > -1 && j - 1 < 8 && j - 1 > -1)
					{
						Box[i - 1][j - 1].WhDethNear = true;
						if (Box[i - 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i - 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
						}
					}
					if (i - 1 < 8 && i - 1 > -1 && j + 1 < 8 && j + 1 > -1)
					{
						Box[i - 1][j + 1].WhDethNear = true;
						if (Box[i - 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i - 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
						}
					}
				}
			}
			if (Box[i][j].name == "BlPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				if (Box[i][j].moves == 0)
				{
					if (i + 1 < 8 && i + 1 > -1 && j - 1 < 8 && j - 1 > -1)
					{
						Box[i + 1][j - 1].BlDethNear = true;
						if (Box[i + 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i + 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
						}
					}
					if (i + 1 < 8 && i + 1 > -1 && j + 1 < 8 && j + 1 > -1)
					{
						Box[i + 1][j + 1].BlDethNear = true;
						if (Box[i + 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i + 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
						}

					}
				}
				else
				{
					if (i + 1 < 8 && i + 1 > -1 && j - 1 < 8 && j - 1 > -1)
					{
						Box[i + 1][j - 1].BlDethNear = true;
						if (Box[i + 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i + 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
						}
					}
					if (i + 1 < 8 && i + 1 > -1 && j + 1 < 8 && j + 1 > -1)
					{
						Box[i + 1][j + 1].BlDethNear = true;
						if (Box[i + 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
						{
							Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
						}
						else if (Box[i + 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
						{
							Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
						}
					}
				}
			}
			if (Box[i][j].name == "WhBishop.png" || Box[i][j].name == "BlBishop.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				for (int z = -1; i + z > -1 && j + z > -1; z--)
				{
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}

							}
						}
					}
					else// if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				int g = 1;
				for (int z = -1; i + z > -1 && j + g < 8; z--)
				{
					if (Box[i + z][j + g].color == 0 || Box[i][j].color == 1 && Box[i + z][j + g].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + g].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + g < 8 && j + g > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + g].WhDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + g].BlDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j + g].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + g < 8 && j + g > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + g].WhDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + g].BlDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
					g++;
				}
				int h = -1;
				for (int z = 1; i + z < 8 && j + h > -1; z++ || Box[i][j].color == 1 && Box[i + z][j + h].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + h].name == "WhKing.png")
				{
					if (Box[i + z][j + h].color == 0)
					{
						if (i + z < 8 && i + z > -1 && j + h < 8 && j + h > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + h].WhDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + h].BlDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j + h].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + h < 8 && j + h > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + h].WhDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + h].BlDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
					h--;
				}
				for (int z = 1; i + z < 8 && j + z < 8; z++)
				{
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + 1][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
			}
			if (Box[i][j].name == "WhHorse.png" || Box[i][j].name == "BlHorse.png")
			{
				if (Box[i][j].color == 1)
				{
					Box[i - 2][j - 1].WhDethNear = true;
					if (Box[i - 2][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 2][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 2][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 2][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 2][j - 1].BlDethNear = true;
					if (Box[i - 2][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 2][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 2][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 2][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				if (Box[i][j].color == 1)
				{
					Box[i - 2][j + 1].WhDethNear = true;
					if (Box[i - 2][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 2][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 2][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 2][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 2][j + 1].BlDethNear = true;
					if (Box[i - 2][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 2][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 2][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 2][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				if (Box[i][j].color == 1)
				{
					Box[i - 1][j - 2].WhDethNear = true;
					if (Box[i - 1][j - 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j - 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j - 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j - 2].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 1][j - 2].BlDethNear = true;
					if (Box[i - 1][j - 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j - 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j - 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j - 2].attacker = Box[i][j].sumKord;
					}
				}
				if (Box[i][j].color == 1)
				{
					Box[i + 1][j - 2].WhDethNear = true;
					if (Box[i + 1][j - 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j - 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j - 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j - 2].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i + 1][j - 2].BlDethNear = true;
					if (Box[i + 1][j - 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j - 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j - 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j - 2].attacker = Box[i][j].sumKord;
					}
				}
				if (Box[i][j].color == 1)
				{
					Box[i + 2][j - 1].WhDethNear = true;
					if (Box[i + 2][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 2][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 2][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 2][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i + 2][j - 1].BlDethNear = true;
					if (Box[i + 2][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 2][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 2][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 2][j - 1].attacker = Box[i][j].sumKord;
					}
				}
		        if (Box[i][j].color == 1)
		        {
		        	Box[i + 2][j + 1].WhDethNear = true;
		        	if (Box[i + 2][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
		        	{
		        		Box[i + 2][j + 1].attacker = Box[i][j].sumKord;
		        	}
		        	else if (Box[i + 2][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
		        	{
		        		Box[i + 2][j + 1].attacker = Box[i][j].sumKord;
		        	}
		        }
		        else if (Box[i][j].color == -1)
		        {
		        	Box[i + 2][j + 1].BlDethNear = true;
		        	if (Box[i + 2][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
		        	{
		        		Box[i + 2][j + 1].attacker = Box[i][j].sumKord;
		        	}
		        	else if (Box[i + 2][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
		        	{
		        		Box[i + 2][j + 1].attacker = Box[i][j].sumKord;
		        	}
		        }
				if (Box[i][j].color == 1)
				{
					Box[i - 1][j + 2].WhDethNear = true;
					if (Box[i - 1][j + 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j + 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j + 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j + 2].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 1][j + 2].BlDethNear = true;
					if (Box[i - 1][j + 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j + 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j + 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j + 2].attacker = Box[i][j].sumKord;
					}
				}
				if (Box[i][j].color == 1)
				{
					Box[i + 1][j + 2].WhDethNear = true;
					if (Box[i + 1][j + 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j + 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j + 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j + 2].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i + 1][j + 2].BlDethNear = true;
					if (Box[i + 1][j + 2].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j + 2].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j + 2].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j + 2].attacker = Box[i][j].sumKord;
					}
				}
				
			}
			if (Box[i][j].name == "WhQueen.png" || Box[i][j].name == "BlQueen.png")
			{
				for (int z = -1; i + z > -1 && j + z > -1; z--)
				{
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				int g = 1;
				for (int z = -1; i + z > -1 && j + g < 8; z--)
				{
					if (Box[i + z][j + g].color == 0 || Box[i][j].color == 1 && Box[i + z][j + g].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + g].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + g < 8 && j + g > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + g].WhDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + g].BlDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j + g].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + g < 8 && j + g > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + g].WhDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + g].BlDethNear = true;
								if (Box[i + z][j + g].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + g].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + g].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
					g++;
				}
				int h = -1;
				for (int z = 1; i + z < 8 && j + h > -1; z++)
				{
					if (Box[i + z][j + h].color == 0 || Box[i][j].color == 1 && Box[i + z][j + h].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + h].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + h < 8 && j + h > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + h].WhDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + h].BlDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j + h].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + h < 8 && j + h > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + h].WhDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + h].BlDethNear = true;
								if (Box[i + z][j + h].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + h].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + h].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
					h--;
				}
				for (int z = 1; i + z < 8 && j + z < 8; z++)
				{
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j + z].WhDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j + z].BlDethNear = true;
								if (Box[i + z][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = -1; i + z > -1; z--)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = 1; i + z < 8; z++)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = 1; j + z < 8; z++)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i][j + z].color != Box[i][j].color)
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = -1; j + z > -1; z--)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i][j + z].color != Box[i][j].color)
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
			}
			if (Box[i][j].name == "WhKing.png" || Box[i][j].name == "BlKing.png")
			{
				if (Box[i][j].color == 1)
				{
					Box[i][j - 1].WhDethNear = true;
					if (Box[i][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i][j - 1].BlDethNear = true;
					if (Box[i][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				
				if (Box[i][j].color == 1)
				{
					Box[i][j + 1].WhDethNear = true;
					if (Box[i][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i][j + 1].BlDethNear = true;
					if (Box[i][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				
				if (Box[i][j].color == 1)
				{
					Box[i + 1][j + 1].WhDethNear = true;
					if (Box[i + 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i + 1][j + 1].BlDethNear = true;
					if (Box[i + 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				
				if (Box[i][j].color == 1)
				{
					Box[i + 1][j - 1].WhDethNear = true;
					if (Box[i + 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i + 1][j - 1].BlDethNear = true;
					if (Box[i + 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				
				if (Box[i][j].color == 1)
				{
					Box[i - 1][j - 1].WhDethNear = true;
					if (Box[i - 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 1][j - 1].BlDethNear = true;
					if (Box[i - 1][j - 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j - 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j - 1].attacker = Box[i][j].sumKord;
					}
				}
				
				if (Box[i][j].color == 1)
				{
					Box[i - 1][j + 1].WhDethNear = true;
					if (Box[i - 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 1][j + 1].BlDethNear = true;
					if (Box[i - 1][j + 1].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j + 1].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j + 1].attacker = Box[i][j].sumKord;
					}
				}
						
				if (Box[i][j].color == 1)
				{
					Box[i + 1][j].WhDethNear = true;
					if (Box[i + 1][j].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i + 1][j].BlDethNear = true;
					if (Box[i + 1][j].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i + 1][j].attacker = Box[i][j].sumKord;
					}
					else if (Box[i + 1][j].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i + 1][j].attacker = Box[i][j].sumKord;
					}
				}
				
				if (Box[i][j].color == 1)
				{
					Box[i - 1][j].WhDethNear = true;
					if (Box[i - 1][j].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j].attacker = Box[i][j].sumKord;
					}
				}
				else if (Box[i][j].color == -1)
				{
					Box[i - 1][j].BlDethNear = true;
					if (Box[i - 1][j].name == "BlKing.png" && Box[i][j].color == 1)
					{
						Box[i - 1][j].attacker = Box[i][j].sumKord;
					}
					else if (Box[i - 1][j].name == "WhKing.png" && Box[i][j].color == -1)
					{
						Box[i - 1][j].attacker = Box[i][j].sumKord;
					}
				}
			}
			if (Box[i][j].name == "WhTower.png" || Box[i][j].name == "BlTower.png")
			{
				for (int z = -1; i + z > -1; z--)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}

					}
					else// if (Box[i + z][j].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = 1; i + z < 8; z++)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i + z][j].color != Box[i][j].color)
					{
						if (i + z < 8 && i + z > -1 && j < 8 && j > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i + z][j].WhDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i + z][j].BlDethNear = true;
								if (Box[i + z][j].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
								else if (Box[i + z][j].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i + z][j].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = 1; j + z < 8; z++)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i][j + z].color != Box[i][j].color)
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
				for (int z = -1; j + z > -1; z--)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
					}
					else// if (Box[i][j + z].color != Box[i][j].color)
					{
						if (i < 8 && i > -1 && j + z < 8 && j + z > -1)
						{
							if (Box[i][j].color == 1)
							{
								Box[i][j + z].WhDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
							else if (Box[i][j].color == -1)
							{
								Box[i][j + z].BlDethNear = true;
								if (Box[i][j + z].name == "BlKing.png" && Box[i][j].color == 1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
								else if (Box[i][j + z].name == "WhKing.png" && Box[i][j].color == -1)
								{
									Box[i][j + z].attacker = Box[i][j].sumKord;
								}
							}
						}
						break;
					}
					/*else
					{
						break;
					}*/
				}
			}
		}
	}
}

void Game::ChangeFigure(int xM, int yM, int color, Vector2i mousePos)
{
	if (schet == 1)
	{
		if (MakeMove == -1)
		{
			Time = 1;
		}
		else if (MakeMove == 1)
		{
			Time = -1;
		}
	}
	MakeMove = 0;
	/*sf::RectangleShape shape(sf::Vector2f(400, 150));
	shape.setPosition(1470, 60);
	shape.setFillColor(Color::White);
	window.draw(shape);*/
	Font font;//шрифт 
	font.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	text.setString("Choose\nFigure:");//задает строку тексту
	text.setPosition(1500, 60);//задаем позицию текста, центр камеры
	window.draw(text);//рисую этот текст
	sf::RectangleShape queenShape(sf::Vector2f(400, 150));
	queenShape.setPosition(1470, 320);
	queenShape.setFillColor(Color::White);
	window.draw(queenShape);
	Font queenFont;//шрифт 
	queenFont.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text queenText("", queenFont, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	queenText.setFillColor(sf::Color::Black);
	queenText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	queenText.setString("Queen");//задает строку тексту
	queenText.setPosition(1500, 320);//задаем позицию текста, центр камеры
	window.draw(queenText);//рисую этот текст
	if (Mouse::isButtonPressed(Mouse::Left) && queenShape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (Box[i][j].sumKord == bestPuwn)
				{
					if (Box[i][j].color == 1)
					{
						Box[i][j].name = "WhQueen.png";
						MakeMove = -1;
						Time = -1;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i][j].name = "BlQueen.png";
						MakeMove = 1;
						Time = 1;
					}
				}
			}
		}

	}
	sf::RectangleShape bishopShape(sf::Vector2f(400, 150));
	bishopShape.setPosition(1470, 470);
	bishopShape.setFillColor(Color::White);
	window.draw(bishopShape);
	Font bishopFont;//шрифт 
	bishopFont.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text bishopText("", bishopFont, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	bishopText.setFillColor(sf::Color::Black);
	bishopText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	bishopText.setString("Bishop");//задает строку тексту
	bishopText.setPosition(1500, 470);//задаем позицию текста, центр камеры
	window.draw(bishopText);//рисую этот текст
	if (Mouse::isButtonPressed(Mouse::Left) && bishopShape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (Box[i][j].sumKord == bestPuwn)
				{
					if (Box[i][j].color == 1)
					{
						Box[i][j].name = "WhBishop.png";
						MakeMove = -1;
						Time = -1;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i][j].name = "BlBishop.png";
						MakeMove = 1;
						Time = 1;
					}
				}
			}
		}
	}
	sf::RectangleShape knightShape(sf::Vector2f(400, 150));
	knightShape.setPosition(1470, 620);
	knightShape.setFillColor(Color::White);
	window.draw(knightShape);
	Font knightFont;//шрифт 
	knightFont.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text knightText("", knightFont, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	knightText.setFillColor(sf::Color::Black);
	knightText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	knightText.setString("Knight");//задает строку тексту
	knightText.setPosition(1500, 620);//задаем позицию текста, центр камеры
	window.draw(knightText);//рисую этот текст
	if (Mouse::isButtonPressed(Mouse::Left) && knightShape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (Box[i][j].sumKord == bestPuwn)
				{
					if (Box[i][j].color == 1)
					{
						Box[i][j].name = "WhHorse.png";
						MakeMove = -1;
						Time = -1;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i][j].name = "BlHorse.png";
						MakeMove = 1;
						Time = 1;
					}
				}
			}
		}
	}
	sf::RectangleShape rookShape(sf::Vector2f(400, 150));
	rookShape.setPosition(1470, 780);
	rookShape.setFillColor(Color::White);
	window.draw(rookShape);
	Font rookFont;//шрифт 
	rookFont.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text rookText("", rookFont, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	rookText.setFillColor(sf::Color::Black);
	rookText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	rookText.setString("Rook");//задает строку тексту
	rookText.setPosition(1500, 780);//задаем позицию текста, центр камеры
	window.draw(rookText);//рисую этот текст
	if (Mouse::isButtonPressed(Mouse::Left) && rookShape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (Box[i][j].sumKord == bestPuwn)
				{
					if (Box[i][j].color == 1)
					{
						Box[i][j].name = "WhTower.png";
						MakeMove = -1;
						Time = -1;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i][j].name = "BlTower.png";
						MakeMove = 1;
						Time = 1;
					}
				}
			}
		}
	}
}

void Game::Shah()
{
	check = false;
	WhKingInDang = false;
	BlKingInDang = false;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (Box[i][j].name == "WhKing.png")
			{
				if (Box[i][j].BlDethNear)
				{
					WhKingInDang = true;
					check = true;
				}
			}
			else if (Box[i][j].name == "BlKing.png")
			{
				if (Box[i][j].WhDethNear)
				{
					BlKingInDang = true;
					check = true;
				}
			}
			else
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < length; j++)
					{
						Path[i][j].name = " ";
					}
				}
			}
		}
	}
}
void Game::WrCheck(Vector2i mousePos)
{
	sf::RectangleShape Checkshape(sf::Vector2f(400, 150));
	Checkshape.setPosition(1470, 210);
	Checkshape.setFillColor(Color::White);
	window.draw(Checkshape);
	Font Checkfont;//шрифт 
	Checkfont.loadFromFile("Sunday-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text Checktext("", Checkfont, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	Checktext.setFillColor(sf::Color::Black);
	Checktext.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	Checktext.setString("Check\nof the\nKing");//задает строку тексту
	Checktext.setPosition(1500, 210);//задаем позицию текста, центр камеры
	window.draw(Checktext);//рисую этот текст
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].name == "WhKing.png" || Box[i][j].name == "BlKing.png")
			{
				kingWay = 0;
				CrWays(mousePos);
				if (kingWay == 0)
				{
					if (Box[i][j].color == 1 && WhKingInDang)
					{
						BlCheckmate = true;

					}
					if (Box[i][j].color == -1 && BlKingInDang)
					{
						WhCheckmate = true;
					}
				}
			}
		}
	}

}
void Game::WrPath()
{
	int kingX, kingY;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if ((Box[i][j].name == "BlKing.png" && BlKingInDang) || (Box[i][j].name == "WhKing.png" && WhKingInDang))
			{
				for (int p = 0; p < height; p++)
				{
					for (int r = 0; r < length; r++)
					{
						if (Box[p][r].sumKord == Box[i][j].attacker)
						{
							CrRedFrame(p, r);
							if (Box[p][r].name == "WhQueen.png" || Box[p][r].name == "BlQueen.png")
							{
								if (j == r && i < p)
								{
									for (int z = -1; p + z > -1; z--)
									{
										if (Box[p + z][r].color == 0)
										{
											CrRedFrame(p + z, r);
										}
										else
										{
											CrRedFrame(p + z, r);
											break;
										}
									}
								}
								else if (j == r && i > p)
								{
									for (int z = 1; p + z < 8; z++)
									{
										if (Box[p + z][r].color == 0)
										{
											CrRedFrame(p + z, r);
										}
										else
										{
											CrRedFrame(p + z, r);
											break;
										}
									}
								}
								else if (j > r && i == p)
								{
									for (int z = 1; p + z < 8; z++)
									{
										if (Box[p][r + z].color == 0)
										{
											CrRedFrame(p, r + z);
										}
										else
										{
											CrRedFrame(p, r + z);
											break;
										}

									}
								}
								else if (j < r && i == p)
								{
									for (int z = -1; r + z > -1; z--)
									{
										if (Box[p][r + z].color == 0)
										{
											CrRedFrame(p, r + z);
										}
										else
										{
											CrRedFrame(p, r + z);
											break;
										}
									}
								}
								else if (j < r && i < p)
								{
									for (int z = -1; p + z > -1 && r + z > -1; z--)
									{
										if (Box[p + z][r + z].color == 0)
										{
											CrRedFrame(p + z, r + z);
										}
										else
										{
											CrRedFrame(p + z, r + z);
											break;
										}
									}
								}
								else if (j > r && i > p)
								{
									for (int z = 1; p + z < 8 && r + z < 8; z++)
									{
										if (Box[p + z][r + z].color == 0)
										{
											CrRedFrame(p + z, r + z);
										}
										else
										{
											CrRedFrame(p + z, r + z);
											break;
										}
									}
								}
								else if (j > r && i < p)
								{
									int g = -1;
									for (int z = 1; p + g > -1 && r + z < 8; z++)
									{
										if (Box[p + g][r + z].color == 0)
										{
											CrRedFrame(p + g, r + z);
										}
										else
										{
											CrRedFrame(p + g, r + z);
											break;
										}
										g--;
									}
								}
								else if (j < r && i > p)
								{
									int g = 1;
									for (int z = -1; p + g < 8 && r + z > -1; z--)
									{
										if (Box[p + g][r + z].color == 0)
										{
											CrRedFrame(p + g, r + z);
										}
										else
										{
											CrRedFrame(p + g, r + z);
											break;
										}
										g++;
									}
								}
							}
							if (Box[p][r].name == "WhPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
							{
								if (p - 1 < 8 && p - 1 > -1 && r - 1 < 8 && r - 1 > -1)
								{
									if (Box[p - 1][r - 1].name == "BlKing.png")
									{
										CrRedFrame(p - 1, r - 1);
									}
								}
								if (i - 1 < 8 && i - 1 > -1 && j + 1 < 8 && j + 1 > -1)
								{
									if (Box[p - 1][r + 1].name == "BlKing.png")
									{
										CrRedFrame(p - 1, r + 1);
									}
								}
							}
							if (Box[p][r].name == "BlPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
							{
								if (p - 1 < 8 && p - 1 > -1 && r - 1 < 8 && r - 1 > -1)
								{
									if (Box[p + 1][r - 1].name == "WhKing.png")
									{
										CrRedFrame(p + 1, r - 1);
									}
								}
								if (i - 1 < 8 && i - 1 > -1 && j + 1 < 8 && j + 1 > -1)
								{
									if (Box[p + 1][r + 1].name == "WhKing.png")
									{
										CrRedFrame(p + 1, r + 1);
									}
								}
							}
							if (Box[p][r].name == "WhBishop.png" || Box[p][r].name == "BlBishop.png")
							{
								if (j < r && i < p)
								{
									for (int z = -1; p + z > -1 && r + z > -1; z--)
									{
										if (Box[p + z][r + z].color == 0)
										{
											CrRedFrame(p + z, r + z);
										}
										else
										{
											CrRedFrame(p + z, r + z);
											break;
										}
									}
								}
								else if (j > r && i > p)
								{
									for (int z = 1; p + z < 8 && r + z < 8; z++)
									{
										if (Box[p + z][r + z].color == 0)
										{
											CrRedFrame(p + z, r + z);
										}
										else
										{
											CrRedFrame(p + z, r + z);
											break;
										}
									}
								}
								else if (j > r && i < p)
								{
									int g = -1;
									for (int z = 1; p + g > -1 && r + z < 8; z++)
									{
										if (Box[p + g][r + z].color == 0)
										{
											CrRedFrame(p + g, r + z);
										}
										else
										{
											CrRedFrame(p + g, r + z);
											break;
										}
										g--;
									}
								}
								else if (j < r && i > p)
								{
									int g = 1;
									for (int z = -1; p + g < 8 && r + z > -1; z--)
									{
										if (Box[p + g][r + z].color == 0)
										{
											CrRedFrame(p + g, r + z);
										}
										else
										{
											CrRedFrame(p + g, r + z);
											break;
										}
										g++;
									}
								}
							}
							if (Box[p][r].name == "BlTower.png" || Box[p][r].name == "WhTower.png")
							{
								if (j == r && i < p)
								{
									for (int z = -1; p + z > -1; z--)
									{
										if (Box[p + z][r].color == 0)
										{
											CrRedFrame(p + z, r);
										}
										else
										{
											CrRedFrame(p + z, r);
											break;
										}
									}
								}
								else if (j == r && i > p)
								{
									for (int z = 1; p + z < 8; z++)
									{
										if (Box[p + z][r].color == 0)
										{
											CrRedFrame(p + z, r);
										}
										else
										{
											CrRedFrame(p + z, r);
											break;
										}
									}
								}
								else if (j > r && i == p)
								{
									for (int z = 1; p + z < 8; z++)
									{
										if (Box[p][r + z].color == 0)
										{
											CrRedFrame(p, r + z);
										}
										else
										{
											CrRedFrame(p, r + z);
											break;
										}

									}
								}
								else if (j < r && i == p)
								{
									for (int z = -1; r + z > -1; z--)
									{
										if (Box[p][r + z].color == 0)
										{
											CrRedFrame(p, r + z);
										}
										else
										{
											CrRedFrame(p, r + z);
											break;
										}
									}
								}
							}
							if (Box[p][r].name == "BlHorse.png" || Box[p][r].name == "WhHorse.png")
							{
								if (Box[p - 2][r - 1].name == "WhKing.png" || Box[p - 2][r - 1].name == "BlKing.png")
								{
									CrRedFrame(p - 2, r - 1);
								}
								else if (Box[p - 2][r + 1].name == "WhKing.png" || Box[p - 2][r + 1].name == "BlKing.png")
								{
									CrRedFrame(p - 2, r + 1);
								}
								else if (Box[p - 1][r - 2].name == "WhKing.png" || Box[p - 1][r - 2].name == "BlKing.png")
								{
									CrRedFrame(p - 1, r - 2);
								}
								else if (Box[p + 1][r - 2].name == "WhKing.png" || Box[p + 1][r - 2].name == "BlKing.png")
								{
									CrRedFrame(p + 1, r - 2);
								}
								else if (Box[p + 2][r - 1].name == "WhKing.png" || Box[p + 2][r - 1].name == "BlKing.png")
								{
									CrRedFrame(p + 2, r - 1);
								}
								else if (Box[p + 2][r + 1].name == "WhKing.png" || Box[p + 2][r + 1].name == "BlKing.png")
								{
									CrRedFrame(p + 2, r + 1);
								}
								else if (Box[p - 1][r + 2].name == "WhKing.png" || Box[p - 1][r + 2].name == "BlKing.png")
								{
									CrRedFrame(p - 1, r + 2);
								}
								else if (Box[p + 1][r + 2].name == "WhKing.png" || Box[p + 1][r + 2].name == "BlKing.png")
								{
									CrRedFrame(p + 1, r + 2);
								}
							}
						}
					}
				}
			}
		}
	}
}
void Game::CrRedFrame(int i, int j)
{
	if (i == 0 && j == 5)
	{
		Path[0][5].name = "RedFrame.png";
		Path[0][5].name = "RedFrame.png";
		Path[0][5].sizeX = Box[0][5].sizeX;
		Path[0][5].sizeY = Box[0][5].sizeY;
		Image heroimage; //создаем объект Image (изображение)
		heroimage.loadFromFile(Path[0][5].name);//загружаем в него файл
		Texture herotexture;//создаем объект Texture (текстура)
		herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
		Sprite herosprite;//создаем объект Sprite(спрайт)
		herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
		herosprite.setPosition(Path[0][5].sizeX, Path[0][5].sizeY);//задаем начальные координаты появления спрайта
		window.draw(herosprite);//выводим спрайт на экран
	}
	else
	{
		Path[i][j].name = "RedFrame.png";
		Path[i][j].sizeX = Box[i][j].sizeX;
		Path[i][j].sizeY = Box[i][j].sizeY;
		Image heroimage; //создаем объект Image (изображение)
		heroimage.loadFromFile(Path[i][j].name);//загружаем в него файл
		Texture herotexture;//создаем объект Texture (текстура)
		herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
		Sprite herosprite;//создаем объект Sprite(спрайт)
		herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
		herosprite.setPosition(Path[i][j].sizeX, Path[i][j].sizeY);//задаем начальные координаты появления спрайта
		window.draw(herosprite);//выводим спрайт на экран
	}
}
void Game::Start()
{
	CrPoints();
	CrChessDesk();
}

void Game::Menu(Vector2i mousePos)
{
	Image heroimage; //создаем объект Image (изображение)
	heroimage.loadFromFile("Ikon.png");//загружаем в него файл

	Texture herotexture;//создаем объект Texture (текстура)
	herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)

	Sprite herosprite;//создаем объект Sprite(спрайт)
	herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
	herosprite.setPosition(200, 200);//задаем начальные координаты появления спрайта

	Font font;
	font.loadFromFile("Sunday-Regular.ttf");
	Text text("", font, 300);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setString("CHESS");
	text.setPosition(1020, 25);

	sf::RectangleShape stshape(sf::Vector2f(450, 270));
	stshape.setPosition(1400, 400);
	stshape.setFillColor(Color::White);
	Font stfont;
	stfont.loadFromFile("Sunday-Regular.ttf");
	Text sttext("", stfont, 200);
	sttext.setFillColor(sf::Color::Black);
	sttext.setStyle(sf::Text::Bold);
	sttext.setString("Play");
	sttext.setPosition(1400, 400);


	sf::RectangleShape shape(sf::Vector2f(450, 270));
	shape.setPosition(1400, 700);
	shape.setFillColor(Color::White);
	Font exfont;
	exfont.loadFromFile("Sunday-Regular.ttf");
	Text extext("", exfont, 200);
	extext.setFillColor(sf::Color::Black);
	extext.setStyle(sf::Text::Bold);
	extext.setString("Exit");
	extext.setPosition(1400, 700);

	window.draw(text);
	window.draw(herosprite);
	window.draw(shape);
	window.draw(extext);
	window.draw(stshape);
	window.draw(sttext);
	window.display();
	if (Mouse::isButtonPressed(Mouse::Left) && stshape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		menu = false;
	}
	else if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		window.close();
	}
}

void Game::Pause(Vector2i mousePos)
{
	window.clear(Color::White);
	Font font;
	font.loadFromFile("Sunday-Regular.ttf");
	Text text("", font, 250);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setString("PAUSE");
	text.setPosition(600, 25);

	sf::RectangleShape stshape(sf::Vector2f(450, 270));
	stshape.setPosition(540, 400);
	stshape.setFillColor(Color::White);
	Font stfont;
	stfont.loadFromFile("Sunday-Regular.ttf");
	Text sttext("", stfont, 200);
	sttext.setFillColor(sf::Color::Black);
	sttext.setStyle(sf::Text::Bold);
	sttext.setString("Continue");
	sttext.setPosition(540, 400);


	sf::RectangleShape shape(sf::Vector2f(450, 270));
	shape.setPosition(760, 700);
	shape.setFillColor(Color::White);
	Font exfont;
	exfont.loadFromFile("Sunday-Regular.ttf");
	Text extext("", exfont, 200);
	extext.setFillColor(sf::Color::Black);
	extext.setStyle(sf::Text::Bold);
	extext.setString("Exit");
	extext.setPosition(760, 700);

	window.draw(text);
	window.draw(shape);
	window.draw(extext);
	window.draw(stshape);
	window.draw(sttext);
	window.display();
	if (Mouse::isButtonPressed(Mouse::Left) && stshape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		pause = false;
	}
	else if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		window.close();
	}
}

void Game::Return()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].sumKord == mainSumKord)
			{
				Box[i][j].moves = mainMoves;
				Box[i][j].name = mainName;
				Box[i][j].color = mainColor;
			}
			else if (Box[i][j].sumKord == nextSumKord)
			{
				Box[i][j].moves = nextMoves;
				Box[i][j].name = nextName;
				Box[i][j].color = nextColor;
			}
		}
	}
	if (Time == 1)
	{
		Time = -1;
		MakeMove = Time;
	}
	else if (Time == -1)
	{
		Time = 1;
		MakeMove = Time;
	}
}


