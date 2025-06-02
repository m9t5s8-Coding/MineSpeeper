#include "Headers/Game.h"
Game::Game(sf::RenderWindow* window)
	:window(window)
{
	window->setFramerateLimit(60);
	board = new Board();
	
}
Game::~Game()
{
	delete board;
}
void Game::Update()
{
	board->Update();
}
void Game::Draw()
{
	window->clear();
	board->Draw(*window);
	window->display();
}