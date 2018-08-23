#pragma once
#include "Collider.h"
class Enemy
{
public:
	Enemy(sf::Vector2f position);
	void update(float deltaTime);
	void draw(sf::RenderWindow & window);
	Collider getCollider();
	~Enemy();

private:
	sf::RectangleShape body;
	sf::Texture texture;
	float inix;
	bool toright;
};

