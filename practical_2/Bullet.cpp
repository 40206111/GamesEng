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

void Bullet::Update(const float &dt)
{
	move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
}