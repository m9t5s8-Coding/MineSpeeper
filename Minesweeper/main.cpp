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
	char player;
	while (true)
	{
		std::cout << "Press 1 for Player and 2 for AI: ";
		std::cin >> player;

		if (player == '1')
		{
			aiEnabled = false;
			break;
		}
		else if (player == '2')
		{
			aiEnabled = true;
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter 1 or 2.\n";
		}
	}

	
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