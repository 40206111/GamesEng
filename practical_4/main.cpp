#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Ghost.h"
#include <iostream>
using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

std::vector<Entity *> entities;

void Render(RenderWindow &window)
{
	for (Entity* e : entities)
	{
		e->render(window);
	}
}

void Load()
{
	Player *player = new Player();
	entities.push_back(new Player());
	entities[entities.size() - 1]->setPosition(sf::Vector2f(400, 350));
	for (int i = 0; i < 4; i++)
	{
		entities.push_back(new Ghost());
		entities[entities.size() - 1]->setPosition(sf::Vector2f(200 + (i * 100), 250));
	}
	std::cout << std::to_string(entities[entities.size() - 1]->getPosition().y) << std::endl;

}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	for (Entity* e : entities)
	{
		e->update(dt);
	}

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

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
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