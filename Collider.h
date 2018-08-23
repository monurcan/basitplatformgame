#pragma once
#include <SFML\Graphics.hpp>
class Collider
{
public:
	Collider(sf::RectangleShape &body);

	void Move(float dx, float dy);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;
	bool checkCollision(Collider &other, sf::Vector2f &direction, float push);

	~Collider();

private:
	sf::RectangleShape &body;
};

