#include "Headers/Texture.h"


namespace Texture
{
	sf::Texture texture;
	void LoadTexture()
	{
		texture.loadFromFile("Image/minesweeper.png");
	}
};