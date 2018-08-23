#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#define MOVABLE_PLATFORM_SPEED 150.0f
#define MOVABLE_PLATFORM_RANGE 150.0f

class Platform
{
public:
	Platform(const sf::Texture& text, const sf::Vector2f & size, const sf::Vector2f & position, bool move = false);
	Platform(const sf::Color& color, const sf::Vector2f & size, const sf::Vector2f & position, bool move = false);
	~Platform();
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	Collider getCollider();

private:
	sf::RectangleShape body;
	float inix;
	bool move;
	bool toright;
};

