#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "game.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[2] =
{
	Keyboard::Left,
	Keyboard::Right
};

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships;

void Load()
{
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100, 100 });
	ships.push_back(inv);
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

	for (auto &s : ships)
	{
		s->Update(dt);
	}
}

void Render(RenderWindow &window)
{
	for (const auto s : ships)
	{
		window.draw(*s);
	}
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