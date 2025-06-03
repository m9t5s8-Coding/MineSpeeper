#pragma once


#include<SFML/Graphics.hpp>
#include<iostream>
#include"Texture.h"
#include<vector>    // for vector
#include <utility>  // for std::pair
#include <set>      // for std::set
#include <cstdlib>  // for rand()
#include <random>
#include <map>
#include <algorithm>  // for std::set_difference
#include <iterator>   // for std::inserter
#include <conio.h>
constexpr unsigned int SCREEN_WIDTH = 400;
constexpr unsigned int SCREEN_HEIGHT = 280;

constexpr unsigned char RESIZE = 3;
constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char WIDTH = 16;
constexpr unsigned char HEIGHT = 16;
constexpr unsigned char MINES = 40;
constexpr int UNKNOWN = -1;
constexpr float aiDelay = 0.25f;
extern sf::Vector2f boardPosition;
extern bool gameOver,hasWon;

extern bool aiEnabled;

struct CELL
{
	bool isRevealed;
	bool isMine;
	bool isFlagged;
	unsigned short adjacentMines;
};
struct MOVES
{
	sf::Vector2i cellCord;
	bool isReveal;
	bool isValid;
};