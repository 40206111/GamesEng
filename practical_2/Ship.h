#pragma once
#include <SFML/Graphics.hpp>

//SHIP
class Ship : public sf::Sprite
{
protected:
	sf::IntRect _sprite;
	Ship();
	bool _exploded = false;
	
public:
	explicit Ship(sf::IntRect ir);

	virtual ~Ship() = 0;

	virtual void Update(const float &dt);

	bool is_exploded() const { return _exploded; }
	virtual void Explode();
};

//INVADER
class Invader : public Ship
{
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;

	static bool direction;
	static float speed;
};

//PLAYER
class Player : public Ship
{
public:
	Player();
	void Update(const float &dt) override;
};