#include "Headers/Game.h"
Game::Game(sf::RenderWindow* window)
	:window(window),
	isLeftClicked(false),
	isRightClicked(false)
{
	window->setFramerateLimit(60);
	board = new Board();
	
}
Game::~Game()
{
	delete board;
}
void Game::getMousePosition()
{
	sf::Vector2i pixelPosition = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPosition);
}
void Game::handleClicks()
{
	bool isLeft = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	bool isRight = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

	//handle left click
	if (isLeft && !isRight && !isLeftClicked)
	{
		int row, col;
		row = (mousePosition.x - boardPosition.x) / CELL_SIZE;
		col = (mousePosition.y - boardPosition.y) / CELL_SIZE;
		if (col >= 0 && col < WIDTH && row >= 0 && row < HEIGHT)
		{
			board->revealCell(sf::Vector2i(col, row));
		}
		isLeftClicked = true;
	}
	else if (!isLeft)
	{
		isLeftClicked = false;
	}

	//handle right click
	if (isRight && !isLeft && !isRightClicked)
	{
		int row, col;
		row = (mousePosition.x - boardPosition.x) / CELL_SIZE;
		col = (mousePosition.y - boardPosition.y) / CELL_SIZE;
		if (col >= 0 && col < WIDTH && row >= 0 && row < HEIGHT)
		{
			board->flagCell(sf::Vector2i(col, row));
		}
		isRightClicked = true;
	}
	else if (!isRight)
	{
		isRightClicked = false;
	}


}
void Game::Update()
{
	
	if (!gameOver && !hasWon && !aiEnabled)
	{
		getMousePosition();
		handleClicks();
	}
	else if( gameOver)
	{
		
	}
	else if (hasWon)
	{
	}
	board->Update();
}
void Game::Draw()
{
	window->clear(sf::Color(113, 133, 153));
	board->Draw(*window);
	window->display();
}