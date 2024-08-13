#include "Game.hpp"
#include "Frames.hpp"
#include "Button.hpp"
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ sf::
Point Box[height][length];
Frames Places[height][length];
MoveWay Ways[height][length];
bool WhKingInDang = false;
bool BlKingInDang = false;
int kingWay = 0;
sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window"); //��������� ��� �������� ������ ����
int figure = -1;
int bestPuwn = -1;
int schet = 1;
 void Game::CrChessDesk()
{
	//Render window(sf::VideoMode(1920, 1080), "SFML Window"); //��������� ��� �������� ������ ����
	RenderWindow& win2 = window;
	Image heroimage; //������� ������ Image (�����������)
	heroimage.loadFromFile("ChessDesk.png");//��������� � ���� ����

	Texture herotexture;//������� ������ Texture (��������)
	herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)

	Sprite herosprite;//������� ������ Sprite(������)
	herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
	herosprite.setPosition(510, 25);//������ ��������� ���������� ��������� �������

	while (window.isOpen())
	{
		if (!BlCheckmate && !WhCheckmate)
		{
			Vector2i mousePos = Mouse::getPosition(window);
			window.clear(Color::White);
			window.draw(herosprite);//������� ������ �� �����
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
			Vector2i mousePos = Mouse::getPosition(window);
			window.clear(Color::White);
			if (BlCheckmate)
			{
				
				Font font;//����� 
				font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
				Text text("", font, 200);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
				text.setFillColor(sf::Color::Black);
				text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
				text.setString("Black Won");//������ ������ ������
				text.setPosition(375, 100);//������ ������� ������, ����� ������
				Image revImage; //������� ������ Image (�����������)
				revImage.loadFromFile("Revard.png");//��������� � ���� ����
				Texture revTexture;//������� ������ Texture (��������)
				revTexture.loadFromImage(revImage);//�������� � ���� ������ Image (�����������)
				Sprite revSprite;//������� ������ Sprite(������)
				revSprite.setTexture(revTexture);//������� � ���� ������ Texture (��������)
				revSprite.setPosition(810, 500);//������ ��������� ���������� ��������� �������
				sf::RectangleShape shape(sf::Vector2f(250, 150));
				shape.setPosition(100, 800);
				shape.setFillColor(Color::White);
				window.draw(shape);
				Font exfont;//����� 
				exfont.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
				Text extext("", exfont, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
				extext.setFillColor(sf::Color::Black);
				extext.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
				extext.setString("Exit");//������ ������ ������
				extext.setPosition(100, 800);//������ ������� ������, ����� ������
				window.draw(extext);//����� ���� �����
				window.draw(herosprite);//������� ������ �� �����
				window.draw(revSprite);//����� ���� �����
				window.draw(extext);//����� ���� �����
				window.draw(text);//����� ���� �����
				if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					window.close();
				}
			}
			else if (WhCheckmate)
			{
				
				Font font;//����� 
				font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
				Text text("", font, 200);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
				text.setFillColor(sf::Color::Black);
				text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
				text.setString("White Won");//������ ������ ������
				text.setPosition(375, 100);//������ ������� ������, ����� ������
				Image revImage; //������� ������ Image (�����������)
				revImage.loadFromFile("Revard.png");//��������� � ���� ����
				Texture revTexture;//������� ������ Texture (��������)
				revTexture.loadFromImage(revImage);//�������� � ���� ������ Image (�����������)
				Sprite revSprite;//������� ������ Sprite(������)
				revSprite.setTexture(revTexture);//������� � ���� ������ Texture (��������)
				revSprite.setPosition(810, 500);//������ ��������� ���������� ��������� �������
				sf::RectangleShape shape(sf::Vector2f(250, 150));
				shape.setPosition(100, 800);
				shape.setFillColor(Color::White);
				window.draw(shape);
				Font exfont;//����� 
				exfont.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
				Text extext("", exfont, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
				extext.setFillColor(sf::Color::Black);
				extext.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
				extext.setString("Exit");//������ ������ ������
				extext.setPosition(100, 800);//������ ������� ������, ����� ������
				window.draw(extext);//����� ���� �����
				window.draw(herosprite);//������� ������ �� �����
				window.draw(revSprite);//����� ���� �����
				window.draw(extext);//����� ���� �����
				window.draw(text);//����� ���� �����
				if (Mouse::isButtonPressed(Mouse::Left) && shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{			
					window.close();
				}

			}
			window.display();
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
}

void Game::CrSprites(Vector2i mousePos)
{
	if (!WhKingInDang && !BlKingInDang)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				Image heroimage; //������� ������ Image (�����������)
				heroimage.loadFromFile(Box[i][j].name);//��������� � ���� ����
				//Box[i][j].image = heroimage;
				Texture herotexture;//������� ������ Texture (��������)
				herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
				//Box[i][j].texture = herotexture;
				Sprite herosprite;//������� ������ Sprite(������)
				herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
				herosprite.setPosition(Box[i][j].sizeX, Box[i][j].sizeY);//������ ��������� ���������� ��������� �������
				//Box[i][j].sprite = herosprite;
				window.draw(herosprite);//������� ������ �� �����
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
	if (WhKingInDang)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				Image heroimage; //������� ������ Image (�����������)
				heroimage.loadFromFile(Box[i][j].name);//��������� � ���� ����
				//Box[i][j].image = heroimage;
				Texture herotexture;//������� ������ Texture (��������)
				herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
				//Box[i][j].texture = herotexture;
				Sprite herosprite;//������� ������ Sprite(������)
				herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
				herosprite.setPosition(Box[i][j].sizeX, Box[i][j].sizeY);//������ ��������� ���������� ��������� �������
				//Box[i][j].sprite = herosprite;
				window.draw(herosprite);//������� ������ �� �����
				if (Box[i][j].name == "WhKing.png")
				{
					figure = Box[i][j].sumKord;
					Time = 1;
					MakeMove = Time;
				}
			}
		}
	}
	else if (BlKingInDang)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				Image heroimage; //������� ������ Image (�����������)
				heroimage.loadFromFile(Box[i][j].name);//��������� � ���� ����
				//Box[i][j].image = heroimage;
				Texture herotexture;//������� ������ Texture (��������)
				herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
				//Box[i][j].texture = herotexture;
				Sprite herosprite;//������� ������ Sprite(������)
				herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
				herosprite.setPosition(Box[i][j].sizeX, Box[i][j].sizeY);//������ ��������� ���������� ��������� �������
				//Box[i][j].sprite = herosprite;
				window.draw(herosprite);//������� ������ �� �����
				if (Box[i][j].name == "BlKing.png")
				{
					figure = Box[i][j].sumKord;
					Time = -1;
					MakeMove = Time;
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
			Image heroimage; //������� ������ Image (�����������)
			heroimage.loadFromFile(Places[i][j].name);//��������� � ���� ����
			Texture herotexture;//������� ������ Texture (��������)
			herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
			Sprite herosprite;//������� ������ Sprite(������)
			herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
			herosprite.setPosition(Places[i][j].sizeX, Places[i][j].sizeY + 3);//������ ��������� ���������� ��������� �������
			if (Box[i][j].choose)
			{
				window.draw(herosprite);//������� ������ �� �����
			}
		}
	}
}
void Game::WrMove()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Font font;//����� 
	font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	if (Time > 0)
	{
		text.setString("Move:\nWhite");//������ ������ ������
	}
	else if (Time < 0)
	{
		text.setString("Move:\nBlack");//������ ������ ������
	}
	
	text.setPosition(100, 50);//������ ������� ������, ����� ������
	window.draw(text);//����� ���� �����
}
void Game::WrFigure()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Font font;//����� 
	font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (Box[i][j].sumKord == figure)
			{
				if (Box[i][j].name == "BlTower.png" || Box[i][j].name == "WhTower.png")
				{
					text.setString("Choose:\nRook");//������ ������ ������
				}
				else if (Box[i][j].name == "BlHorse.png" || Box[i][j].name == "WhHorse.png")
				{
					text.setString("Choose:\nKnight");//������ ������ ������
				}
				else if (Box[i][j].name == "BlPuwn.png" || Box[i][j].name == "WhPuwn.png")
				{
					text.setString("Choose:\nPuwn");//������ ������ ������
				}
				else if (Box[i][j].name == "BlBishop.png" || Box[i][j].name == "WhBishop.png")
				{
					text.setString("Choose:\nBishop");//������ ������ ������
				}
				else if (Box[i][j].name == "BlKing.png" || Box[i][j].name == "WhKing.png")
				{
					text.setString("Choose:\nKing");//������ ������ ������
				}
				else if (Box[i][j].name == "BlQueen.png" || Box[i][j].name == "WhQueen.png")
				{
					text.setString("Choose:\nQueen");//������ ������ ������
				}
			}
		}
	}

	text.setPosition(100, 300);//������ ������� ������, ����� ������
	window.draw(text);//����� ���� �����
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
					Font font;//����� 
					font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
					Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
					text.setFillColor(sf::Color::Black);
					text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
					text.setString("Cansel");//������ ������ ������
					text.setPosition(1500, 60);//������ ������� ������, ����� ������
					window.draw(text);//����� ���� �����
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
						//Font font;//����� 
						//font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
						//Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
						//text.setFillColor(sf::Color::Black);
						//text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
						//text.setString("Cansel");//������ ������ ������
						//text.setPosition(1500, 60);//������ ������� ������, ����� ������
						//window.draw(text);//����� ���� �����
						CrWays(mousePos);
					}
				}
				else 
				{
					sf::RectangleShape shape(sf::Vector2f(400, 150));
					shape.setPosition(1470, 60);
					shape.setFillColor(Color::White);
					window.draw(shape);
					Font font;//����� 
					font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
					Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
					text.setFillColor(sf::Color::Black);
					text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
					text.setString("Check\nof the\nKing");//������ ������ ������
					text.setPosition(1500, 60);//������ ������� ������, ����� ������
					window.draw(text);//����� ���� �����
					CrWays(mousePos);
					WhKingInDang = false;
					BlKingInDang = false;
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
			if (Box[i][j].sumKord == figure)
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
					kingWay = 0;
					if (Box[i][j - 1].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i, j - 1, 1.0f);
					}
					if (Box[i][j + 1].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i, j + 1, 1.0f);
					}
					if (Box[i + 1][j + 1].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + 1, j + 1, 1.0f);
					}
					if (Box[i + 1][j - 1].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + 1, j - 1, 1.0f);
					}
					if (Box[i - 1][j - 1].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i - 1, j - 1, 1.0f);
					}
					if (Box[i - 1][j + 1].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i - 1, j + 1, 1.0f);
					}
					if (Box[i + 1][j].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i + 1, j, 1.0f);
					}
					if (Box[i - 1][j].color != Box[i][j].color)
					{
						SelWays(mousePos, i, j, i - 1, j, 1.0f);
					}
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
}

void Game::ChangePlace(int xM, int yM, int xN, int yN)
{
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
	CanDeath();
}

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
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
				Ways[x][y].name = "BlFrame.png";
				Ways[x][y].sizeX = Box[x][y].sizeX;
				Ways[x][y].sizeY = Box[x][y].sizeY;
				Image heroimage; //������� ������ Image (�����������)
				heroimage.loadFromFile(Ways[x][y].name);//��������� � ���� ����
				Texture herotexture;//������� ������ Texture (��������)
				herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
				Sprite herosprite;//������� ������ Sprite(������)
				herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
				herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//������ ��������� ���������� ��������� �������
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
void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, double zero)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
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
			Image heroimage; //������� ������ Image (�����������)
			heroimage.loadFromFile(Ways[x][y].name);//��������� � ���� ����
			Texture herotexture;//������� ������ Texture (��������)
			herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
			Sprite herosprite;//������� ������ Sprite(������)
			herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
			herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//������ ��������� ���������� ��������� �������
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

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, std::string zero)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
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
				Image heroimage; //������� ������ Image (�����������)
				heroimage.loadFromFile(Ways[x][y].name);//��������� � ���� ����
				Texture herotexture;//������� ������ Texture (��������)
				herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
				Sprite herosprite;//������� ������ Sprite(������)
				herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
				herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//������ ��������� ���������� ��������� �������
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

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, int step)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
	{
		if (Box[x][y].name == "BlKing.png" && Box[i][j].WhDethNear)
		{
			/*MakeMove = Time;
			figure = -1;*/
		}
		else if (Box[x][y].name == "WhKing.png" && Box[i][j].BlDethNear)
		{
			//MakeMove = Time;
			//figure = -1;
		}
		else
		{
			Ways[i][j].name = "BlFrame.png";
			Ways[i][j].sizeX = Box[i][j].sizeX;
			Ways[i][j].sizeY = Box[i][j].sizeY;
			Image heroimage; //������� ������ Image (�����������)
			heroimage.loadFromFile(Ways[i][j].name);//��������� � ���� ����
			Texture herotexture;//������� ������ Texture (��������)
			herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
			Sprite herosprite;//������� ������ Sprite(������)
			herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
			herosprite.setPosition(Ways[i][j].sizeX, Ways[i][j].sizeY);//������ ��������� ���������� ��������� �������
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

void Game::SelWays(Vector2i mousePos, int i, int j, int x, int y, float zero)
{
	if (x < 8 && x > -1 && y < 8 && y > -1)
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
				Ways[x][y].name = "BlFrame.png";
				Ways[x][y].sizeX = Box[x][y].sizeX;
				Ways[x][y].sizeY = Box[x][y].sizeY;
				Image heroimage; //������� ������ Image (�����������)
				heroimage.loadFromFile(Ways[x][y].name);//��������� � ���� ����
				Texture herotexture;//������� ������ Texture (��������)
				herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
				Sprite herosprite;//������� ������ Sprite(������)
				herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
				herosprite.setPosition(Ways[x][y].sizeX, Ways[x][y].sizeY);//������ ��������� ���������� ��������� �������
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

void Game::Castling(int xM, int yM, int xN, int yN, int step)
{

	Box[xM][yM + step].name = Box[xM][yM].name;
	Box[xM][yM + step].color = Box[xM][yM].color;
	Box[xM][yM + step].moves = Box[xM][yM].moves + 1;
	Box[xN][yN + step].choose = false;
	Box[xM][yM].name = Box[xN][yN].name;
	Box[xM][yM].color = Box[xN][yN].color;
	Box[xM][yM].moves = Box[xN][yN].moves + 1;
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
					Box[i - 1][j - 1].WhDethNear = true;
					Box[i - 1][j + 1].WhDethNear = true;
				}
				else
				{
					Box[i - 1][j - 1].WhDethNear = true;			
					Box[i - 1][j + 1].WhDethNear = true;
				}
			}
			if (Box[i][j].name == "BlPuwn.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				if (Box[i][j].moves == 0)
				{
					Box[i + 1][j - 1].BlDethNear = true;									
					Box[i + 1][j + 1].BlDethNear = true;					
				}
				else
				{					
					Box[i + 1][j - 1].BlDethNear = true;					
					Box[i + 1][j + 1].BlDethNear = true;
				}
			}
			if (Box[i][j].name == "WhBishop.png" || Box[i][j].name == "BlBishop.png") // Box[i][j].name == "BlPuwn.png" || 
			{
				for (int z = -1; i + z > -1 && j + z > -1; z--)
				{
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
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
					if (Box[i + z][j + g].color == 0 || Box[i][j].color == 1 && Box[i + z][j + g].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + g].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + g].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + g].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + g].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + g].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + g].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
					g++;
				}
				int h = -1;
				for (int z = 1; i + z < 8 && j + h > -1; z++ || Box[i][j].color == 1 && Box[i + z][j + h].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + h].name == "WhKing.png")
				{
					if (Box[i + z][j + h].color == 0)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + h].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + h].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + h].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + h].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + h].BlDethNear = true;
						}
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
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
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
					if (Box[i][j].color == 1)
					{
						Box[i - 2][j - 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 2][j - 1].BlDethNear = true;
					}
				}
				if (Box[i - 2][j + 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i - 2][j + 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 2][j + 1].BlDethNear = true;
					}
				}
				if (Box[i - 1][j - 2].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i - 1][j - 2].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 1][j - 2].BlDethNear = true;
					}
				}
				if (Box[i + 1][j - 2].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 1][j - 2].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 1][j - 2].BlDethNear = true;
					}
				}
				if (Box[i + 2][j - 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 2][j - 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 2][j - 1].BlDethNear = true;
					}
				}
				if (Box[i + 2][j + 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 2][j + 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 2][j + 1].BlDethNear = true;
					}
				}
				if (Box[i - 1][j + 2].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i - 1][j + 2].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 1][j + 2].BlDethNear = true;
					}
				}
				if (Box[i + 1][j + 2].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 1][j + 2].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 1][j + 2].BlDethNear = true;
					}
				}
			}
			if (Box[i][j].name == "WhQueen.png" || Box[i][j].name == "BlQueen.png")
			{
				for (int z = -1; i + z > -1 && j + z > -1; z--)
				{
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
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
					if (Box[i + z][j + g].color == 0 || Box[i][j].color == 1 && Box[i + z][j + g].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + g].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + g].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + g].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + g].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + g].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + g].BlDethNear = true;
						}
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
					if (Box[i + z][j + h].color == 0 || Box[i][j].color == 1 && Box[i + z][j + h].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + h].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + h].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + h].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + h].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + h].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + h].BlDethNear = true;
						}
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
					if (Box[i + z][j + z].color == 0 || Box[i][j].color == 1 && Box[i + z][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
					}
					else if (Box[i + z][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j + z].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = -1; i + z > -1; z--)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; i + z < 8; z++)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; j + z < 8; z++)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = -1; j + z > -1; z--)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
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
					if (Box[i][j].color == 1)
					{
						Box[i][j - 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i][j - 1].BlDethNear = true;
					}
				}
				if (Box[i][j + 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i][j + 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i][j + 1].BlDethNear = true;
					}
				}
				if (Box[i + 1][j + 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 1][j + 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 1][j + 1].BlDethNear = true;
					}
				}
				if (Box[i + 1][j - 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 1][j - 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 1][j - 1].BlDethNear = true;
					}
				}
				if (Box[i - 1][j - 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i - 1][j - 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 1][j - 1].BlDethNear = true;
					}
				}
				if (Box[i - 1][j + 1].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i - 1][j + 1].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 1][j + 1].BlDethNear = true;
					}
				}
				if (Box[i + 1][j].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i + 1][j].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i + 1][j].BlDethNear = true;
					}
				}
				if (Box[i - 1][j].color != Box[i][j].color)
				{
					if (Box[i][j].color == 1)
					{
						Box[i - 1][j].WhDethNear = true;
					}
					else if (Box[i][j].color == -1)
					{
						Box[i - 1][j].BlDethNear = true;
					}					}
			}
			if (Box[i][j].name == "WhTower.png" || Box[i][j].name == "BlTower.png")
			{
				for (int z = -1; i + z > -1; z--)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; i + z < 8; z++)
				{
					if (Box[i + z][j].color == 0 || Box[i][j].color == 1 && Box[i + z][j].name == "BlKing.png" || Box[i][j].color == -1 && Box[i + z][j].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
					}
					else if (Box[i + z][j].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i + z][j].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i + z][j].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = 1; j + z < 8; z++)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
						break;
					}
					else
					{
						break;
					}
				}
				for (int z = -1; j + z > -1; z--)
				{
					if (Box[i][j + z].color == 0 || Box[i][j].color == 1 && Box[i][j + z].name == "BlKing.png" || Box[i][j].color == -1 && Box[i][j + z].name == "WhKing.png")
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
					}
					else if (Box[i][j + z].color != Box[i][j].color)
					{
						if (Box[i][j].color == 1)
						{
							Box[i][j + z].WhDethNear = true;
						}
						else if (Box[i][j].color == -1)
						{
							Box[i][j + z].BlDethNear = true;
						}
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
	Font font;//����� 
	font.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	text.setString("Choose\nFigure:");//������ ������ ������
	text.setPosition(1500, 60);//������ ������� ������, ����� ������
	window.draw(text);//����� ���� �����
	sf::RectangleShape queenShape(sf::Vector2f(400, 150));
	queenShape.setPosition(1470, 320);
	queenShape.setFillColor(Color::White);
	window.draw(queenShape);
	Font queenFont;//����� 
	queenFont.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text queenText("", queenFont, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	queenText.setFillColor(sf::Color::Black);
	queenText.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	queenText.setString("Queen");//������ ������ ������
	queenText.setPosition(1500, 320);//������ ������� ������, ����� ������
	window.draw(queenText);//����� ���� �����
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
	Font bishopFont;//����� 
	bishopFont.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text bishopText("", bishopFont, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	bishopText.setFillColor(sf::Color::Black);
	bishopText.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	bishopText.setString("Bishop");//������ ������ ������
	bishopText.setPosition(1500, 470);//������ ������� ������, ����� ������
	window.draw(bishopText);//����� ���� �����
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
	Font knightFont;//����� 
	knightFont.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text knightText("", knightFont, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	knightText.setFillColor(sf::Color::Black);
	knightText.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	knightText.setString("Knight");//������ ������ ������
	knightText.setPosition(1500, 620);//������ ������� ������, ����� ������
	window.draw(knightText);//����� ���� �����
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
	Font rookFont;//����� 
	rookFont.loadFromFile("Sunday-Regular.ttf");//�������� ������ ������ ���� ������
	Text rookText("", rookFont, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	rookText.setFillColor(sf::Color::Black);
	rookText.setStyle(sf::Text::Bold);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	rookText.setString("Rook");//������ ������ ������
	rookText.setPosition(1500, 780);//������ ������� ������, ����� ������
	window.draw(rookText);//����� ���� �����
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
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (Box[i][j].name == "WhKing.png")
			{
				if (Box[i][j].BlDethNear)
				{
					WhKingInDang = true;
				}
			}
			else if (Box[i][j].name == "BlKing.png")
			{
				if (Box[i][j].WhDethNear)
				{
					BlKingInDang = true;
				}
			}
		}
	}
}
void Game::Start()
{
	CrPoints();
	CrChessDesk();
}
