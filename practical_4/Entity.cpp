#include "Entity.h"
#include "levelsystem.h"
using namespace std;
using namespace sf;

bool Entity::validmove(Vector2f pos)
{
	return (ls::getTileAt(pos) != ls::WALL);
}
 
const Vector2f Entity::getPosition() { return _position;  }
void Entity::setPosition(const Vector2f &pos) { _position = pos; }
void Entity::update(const double dt)
{
	_shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}