#include "Collider.h"
#include <iostream>


Collider::Collider(sf::RectangleShape &body)
	: body(body)
{
}


void Collider::Move(float dx, float dy)
{
	body.move(dx, dy);
}

const sf::Vector2f & Collider::getPosition() const
{
	return body.getPosition();
}

const sf::Vector2f & Collider::getSize() const
{
	return body.getSize();
}

bool Collider::checkCollision(Collider &other, sf::Vector2f &direction, float push)
{
	float deltaX = getPosition().x - other.getPosition().x;
	float deltaY = getPosition().y - other.getPosition().y;
	float intersectX = abs(deltaX) - (getSize().x + other.getSize().x) / 2.0f;
	float intersectY = abs(deltaY) - (getSize().y + other.getSize().y) / 2.0f;

	if (intersectX < 0.0f && intersectY < 0.0f) {
		
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY) {
			if (deltaX < 0.0f) {
				Move(intersectX*(1.0f - push), 0.0f);
				other.Move(-intersectX*push, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				Move(-intersectX*(1.0f - push), 0.0f);
				other.Move(intersectX*push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY < 0.0f) {
				Move(0.0f,intersectY*(1.0f - push));
				other.Move(0.0f,-intersectY * push);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				other.Move(0.0f, intersectY*push);
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}

		return true;
	}

	return false;
}

Collider::~Collider()
{
}
