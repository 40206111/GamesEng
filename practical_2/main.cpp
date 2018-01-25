#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "game.h"
using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships;

void Load()
{
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	auto player = new Player();

	ships.push_back(player);

	for (int r = 0; r < invaders_rows; ++r)
	{
		auto rect = IntRect(0 + (r*32), 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c)
		{
			Vector2f position = Vector2f((((gameWidth/2)-((invaders_columns/2) * 40)) + 16) + (c * 40), 100 + (r * 40));
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
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