#pragma once
#include "Global.h"
#include "AiMinesweeper.h"


class Board
{
private:
	sf::Sprite sprite;
	std::vector<std::vector<CELL>> cell;
	sf::RectangleShape boardRect;
	bool userClickedMine;
	sf::Vector2i clickedMinePosition;
	bool firstClick;
	AiMinesweeper* ai;
	sf::Clock aiClock;
	MOVES moves,hint;
	bool startGame;
	bool HClickedOnce, RClickedOnce,SpaceClickedOnce;
public:
	Board();
	~Board();
	void setBoard();
	void placeMines(sf::Vector2i);
	void calculateMines();
	void revealCell(sf::Vector2i);
	void flagCell(sf::Vector2i);
	void openNeighbour(sf::Vector2i);
	void revealBoard();
	void winCondition();
	void aiSetup();
	void restartGame();
	void setTexture(int, int);
	void Update();
	void Draw(sf::RenderTarget&);
};

