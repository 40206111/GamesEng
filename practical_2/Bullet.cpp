#include "Bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet::Bullet() {};

unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];

void Bullet::Fire(const::Vector2f &pos, const bool mode)
{
	bullets[bulletPointer].setPosition(pos);
	bullets[bulletPointer].setOrigin(16, 16);
	bullets[bulletPointer].setTexture(spritesheet);
	if (mode)
	{
		bullets[bulletPointer].setTextureRect(IntRect(32,32, 32, 32));
	}
	else
	{
		bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));
	}
	bullets[bulletPointer]._mode = mode;
	bulletPointer += 1;
}

void Bullet::Render(sf::RenderWindow &window)
{
	for (Bullet b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Update(const float &dt)
{
	for (Bullet b : bullets)
	{
		b._Update(dt);
	}
}

void Ship::Explode()
{
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
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