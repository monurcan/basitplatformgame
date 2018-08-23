#include "Bullet.h"

Bullet::Bullet(float theta, sf::Vector2f iniPos)
	: bullet(sf::Vector2f(13, 8)), velocity(2000.0f*cos(theta / 57.2957796f), -2000.0f*sin(theta / 57.2957796f))
{
	bullet.setFillColor(sf::Color(143, 125, 75));
	bullet.setPosition(iniPos);
	bullet.setRotation(-theta);
}

void Bullet::Update(float deltaTime)
{
	bullet.move(velocity * deltaTime);

	velocity.y += 9 * 981.0f * deltaTime;
}

void Bullet::draw(sf::RenderWindow & window)
{
	window.draw(bullet);
}

Collider Bullet::getCollider()
{
	return Collider(bullet);
}

Bullet::~Bullet()
{
}
