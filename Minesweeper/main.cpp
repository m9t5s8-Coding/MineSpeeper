#include "Headers/Game.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH*RESIZE , SCREEN_HEIGHT*RESIZE }), "MineSweeper");
	Texture::LoadTexture();
	Game game(&window);

	sf::View view;
	view.setSize({ SCREEN_WIDTH,SCREEN_HEIGHT });
	view.setCenter({ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f });

	sf::Clock clock;
	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		window.setView(view);
		game.Update();
		game.Draw();
	}
	return 0;
}