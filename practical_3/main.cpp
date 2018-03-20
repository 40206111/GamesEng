#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "levelsystem.h"
using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 500;
std::vector<Entity *> entities;

void Render(RenderWindow &window)
{
	ls::render(window);
	for (auto &e : entities)
	{
		e->render(window);
	}
}

void Load()
{
	Entity *player = new Player();
	entities.push_back(player);

	ls::loadLevelFile("res/maze_2.txt");

	//print the level to console
	for (size_t y = 0; y < ls::getHeight(); ++y)
	{
		for (size_t x = 0; x < ls::getWidth(); ++x)
		{
			cout << ls::getTile({ x, y });
			if (ls::getTile({ x,y }) == 1)
			{
				Vector2f pos = ls::getTilePosition(sf::Vector2ul(x, y));
				entities[0]->setPosition(Vector2f(pos.x + 50, pos.y + 50));
			}
		}
		cout << endl;
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

	for (auto &e : entities)
	{
		e->update(dt);
	}
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "MAZE");
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