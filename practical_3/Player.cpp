#include "Player.h"
using namespace sf;
using namespace std;

void Player::update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		move(Vector2f(100 * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		move(Vector2f(-100 * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		move(Vector2f(0, -100 * dt));
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		move(Vector2f(0, 100 * dt));
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