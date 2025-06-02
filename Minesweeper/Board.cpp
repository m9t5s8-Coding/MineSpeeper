#include "Headers/Board.h"


Board::Board()
	:sprite(Texture::texture)
{

}

Board::~Board()
{

}
void Board::Update()
{

}
void Board::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
}