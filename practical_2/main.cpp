#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[2] =
{
	Keyboard::Left,
	Keyboard::Right
};

int gameWidth = 800;
int gameHeight = 600;

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships;

void Load()
{
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
}

void Render(RenderWindow &window)
{
	window.draw(invader);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();

	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}