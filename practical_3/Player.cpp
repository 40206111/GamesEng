#include "Player.h"
#include "levelsystem.h"
using namespace sf;
using namespace std;

bool validmove(Vector2f pos)
{
	return (ls::getTileAt(pos) != ls::WALL);
}

void Player::update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		Vector2f testpos = this->getPosition() + Vector2f(100 * dt, 0);
		testpos.x += 25;
		if (validmove(testpos))
		{
			move(Vector2f(100 * dt, 0));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		Vector2f testpos = this->getPosition() + Vector2f(-100 * dt, 0);
		testpos.x -= 25;
		if (validmove(testpos))
		{
			move(Vector2f(-100 * dt, 0));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		Vector2f testpos = this->getPosition() + Vector2f(0, -100 * dt);
		testpos.y += 5;
		if (validmove(testpos))
		{
			move(Vector2f(0, -100 * dt));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		Vector2f testpos = this->getPosition() + Vector2f(0, 100 * dt);
		testpos.y += 55;
		if (validmove(testpos))
		{
			move(Vector2f(0, 100 * dt));
		}
	}
	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f))
{
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const
{
	window.draw(*_shape);
}

