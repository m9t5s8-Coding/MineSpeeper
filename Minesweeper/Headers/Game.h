#pragma once
#include"Global.h"
#include"Board.h"
class Game
{
private:
	sf::RenderWindow* window;
	Board* board;
	sf::Vector2f mousePosition;
	bool isLeftClicked, isRightClicked;
public:
	Game(sf::RenderWindow*);
	~Game();
	void getMousePosition();
	void handleClicks();
	void Update();
	void Draw();
};

