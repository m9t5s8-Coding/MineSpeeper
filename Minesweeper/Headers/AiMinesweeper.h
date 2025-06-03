#pragma once
#include "Global.h"

struct AICELL
{
	bool isRevealed;
	bool isFlagged;
	int adjacentMines;
};

struct Vector2iCompare {
	bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const {
		if (a.x != b.x) return a.x < b.x;
		return a.y < b.y;
	}
};
class AiMinesweeper
{
private:
	std::vector<std::vector<AICELL>> aiCell;
	std::mt19937 gen;
	
public:
	AiMinesweeper();
	~AiMinesweeper();
	void copyBoard(const std::vector<std::vector<CELL>>&);
	MOVES getRandomMoves();
	MOVES lookNeighbour();
	MOVES subsetElimination();
	MOVES getHint();
};

