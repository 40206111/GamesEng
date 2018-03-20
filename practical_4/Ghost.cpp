#include "Ghost.h"
using namespace std;
using namespace sf;

int Ghost::amount = 0;
std::vector<sf::Color> Ghost::_colours = { Color::Blue, Color::Red, Color(255,179,220), Color(255,158,69) };

Ghost::Ghost() : _speed(200.0f), _g_id(amount), Entity(make_unique<CircleShape>(25.0f))
{
	_shape->setFillColor(_colours[_g_id]);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
	amount++;
	if (amount == 4)
	{
		amount = 0;
	}
}

void Ghost::update(double dt)
{

}

void Ghost::render(sf::RenderWindow &window) const
{
	window.draw(*_shape);
}