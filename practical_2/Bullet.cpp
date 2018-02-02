#include "Bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet::Bullet() {};

Bullet::Bullet(const::Vector2f &pos, const bool mode)
{
	setPosition(pos);
	setOrigin(16, 16);
	setTexture(spritesheet);
	if (mode)
	{
		setTextureRect(IntRect(32,32, 32, 32));
	}
	else
	{
		setTextureRect(IntRect(64, 32, 32, 32));
	}
}

void Bullet::_Update(const float &dt)
{
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32)
	{
		return;
	}
	else
	{
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships)
		{
			if (!_mode && s == ships[0])
			{
				continue;
			}
			if (_mode && s != ships[0])
			{
				continue;
			}
			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox))
			{
				s->Explode();
				setPosition(-100, -100);
				return;
			}
		}
	}
}