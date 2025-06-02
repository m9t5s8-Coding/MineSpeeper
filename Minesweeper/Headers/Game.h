#pragma once
#include"Global.h"
#include"Board.h"
class Game
{
private:
	sf::RenderWindow* window;
	Board* board;
public:
	Game(sf::RenderWindow*);
	~Game();
	void Update();
	void Draw();
};

