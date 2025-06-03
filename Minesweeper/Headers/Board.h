#pragma once
#include "Global.h"

struct CELL
{
	bool isRevealed;
	bool isMine;
	bool isFlagged;
	unsigned short adjacentMines;
};

class Board
{
private:
	sf::Sprite sprite;
	std::vector<std::vector<CELL>> cell;
	sf::RectangleShape boardRect;
	bool userClickedMine;
	sf::Vector2i clickedMinePosition;
	bool firstClick;
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
	void setTexture(int, int);
	void Update();
	void Draw(sf::RenderTarget&);
};

