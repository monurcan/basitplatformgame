#include "Enemy.h"


Enemy::Enemy(sf::Vector2f position)
	: body(sf::Vector2f(80, 46)), inix(position.x), toright(true)
{
	texture.loadFromFile("enemy.png");
	body.setPosition(position);
	body.setTexture(&texture);
}

void Enemy::update(float deltaTime)
{
	if (abs(body.getPosition().x - inix) < 100.0f) {
		if(toright) body.move(sf::Vector2f(50.0f * deltaTime, 0));
		else body.move(sf::Vector2f(-50.0f * deltaTime, 0));
	}

	if (body.getPosition().x - inix >= 100.0f) {
		toright = false;
		body.move(sf::Vector2f(-50.0f * deltaTime, 0));
	}

	if (body.getPosition().x - inix < 0.0f) {
		toright = true;
		body.move(sf::Vector2f(50.0f * deltaTime, 0));
	}
}

void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(body);
}


Collider Enemy::getCollider()
{
	return Collider(body);
}


Enemy::~Enemy()
{
}
