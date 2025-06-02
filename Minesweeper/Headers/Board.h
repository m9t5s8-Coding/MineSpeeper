#pragma once
#include "Global.h"
class Board
{
private:
	sf::Sprite sprite;

public:
	Board();
	~Board();
	void Update();
	void Draw(sf::RenderTarget&);
};

