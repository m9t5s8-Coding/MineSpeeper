#pragma once


#include<SFML/Graphics.hpp>
#include<iostream>
#include"Texture.h"
#include<vector>    // for vector
#include <utility>  // for std::pair
#include <set>      // for std::set
#include <cstdlib>  // for rand()

constexpr unsigned int SCREEN_WIDTH = 400;
constexpr unsigned int SCREEN_HEIGHT = 280;

constexpr unsigned char RESIZE = 3;
constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char WIDTH = 16;
constexpr unsigned char HEIGHT = 16;
constexpr unsigned char MINES = 4;

extern sf::Vector2f boardPosition;
extern bool gameOver,hasWon;