#include "StdAfx.h"
//#include "GameOver.h"
class GameOver
{
public:
	//void ShowFirst(sf::RenderWindow& window);
	void Show(sf::RenderWindow& window);
};

void GameOver::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture image;
	if (image.loadFromFile("images/GameOver.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}