#include "Ship.h"
#include "game.h"
#include "Bullet.h"

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

	if (_exploded)
	{
		if (fadeTime <= 0)
		{
			setPosition(-111, -111);
		}
		else
		{
			fadeTime -= dt;
		}
	}

	if (fadeTime > 0.0f)
	{
		move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

		if ((direction && getPosition().x > (gameWidth - 16)) || (!direction && (getPosition().x < 16)))
		{
			direction = !direction;

			for (int i = 1; i < ships.size(); ++i)
			{
				ships[i]->move(0, 24);
			}
		}
	}

	if (!_exploded)
	{
		static float firetime = 0.0f;
		firetime -= dt;
		if (firetime <= 0 && rand() % 100 == 0)
		{
			Bullet::Fire(getPosition(), true);
			firetime = 4.0f + (rand() % 60);
		}
	}
}


//PLAYER
Player::Player() : Ship(IntRect(160, 32, 32, 32))
{
	setPosition({ gameHeight * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt)
{
	Ship::Update(dt);
	if (_exploded)
	{
		if (fadeTime <= 0)
		{
			setPosition(-111, -111);
		}
		else
		{
			fadeTime -= dt;
		}
	}
	if (!_exploded)
	{
		static float firetime = 0.0f;
		firetime -= dt;
		if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)))
		{
			move(100 * dt, 0);
		}

		if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)))
		{
			move(-100 * dt, 0);
		}

		if (firetime <= 0 && (Keyboard::isKeyPressed(Keyboard::Space)))
		{
			sf::Vector2f pos = getPosition();
			pos.x += 16;
			Bullet::Fire(pos, false);
			firetime = 0.7f;
		}
	}
}