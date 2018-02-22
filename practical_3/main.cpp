#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;
std::vector<Entity *> entities;

void Render(RenderWindow &window)
{
	for (auto &e : entities)
	{
		e->render(window);
	}
}

void Load()
{
	Entity *player = new Player();
	entities.push_back(player);
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