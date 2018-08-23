#pragma once
#include<SFML\Graphics.hpp>
#include <math.h>
#include "Collider.h"

class Bullet
{
public:
	Bullet(float theta, sf::Vector2f iniPos);
	void Update(float deltaTime);
	void draw(sf::RenderWindow & window);
	Collider getCollider();
	~Bullet();

private:
	sf::RectangleShape bullet;
	sf::Vector2f velocity;
};

