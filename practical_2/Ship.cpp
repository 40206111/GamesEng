#include "Ship.h"
#include "game.h"

using namespace sf;
using namespace std;

//SHIP
Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite()
{
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;

//INVADER
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir)
{
	setOrigin(16, 16);
	setPosition(pos);
}

bool Invader::direction = true;
float Invader::speed = 24;

void Invader::Update(const float &dt)
{
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > (gameWidth - 16)) || (!direction && (getPosition().x < 16)))
	{
		for (int i = 0; i < ships.size(); ++i)
		direction = !direction;

		{
			ships[i]->move(0, 24);
		}
	}
}
}