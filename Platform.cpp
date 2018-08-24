#include "Platform.h"


Platform::Platform(const sf::Texture & text, const sf::Vector2f & size, const sf::Vector2f & position, bool move)
	: inix(position.x), move(move), toright(true)
{
	body.setSize(size);
	body.setTexture(&text);
	body.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
}

Platform::Platform(const sf::Color &color, const sf::Vector2f & size, const sf::Vector2f & position, bool move)
	: inix(position.x), move(move), toright(true)
{
	body.setSize(size);
	body.setFillColor(color);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
}


Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Platform::update(float deltaTime)
{
	if (move) {
		if (abs(body.getPosition().x - inix) < MOVABLE_PLATFORM_RANGE) {
			if (toright) body.move(sf::Vector2f(MOVABLE_PLATFORM_SPEED * deltaTime, 0));
			else body.move(sf::Vector2f(-MOVABLE_PLATFORM_SPEED * deltaTime, 0));
		}

		if (body.getPosition().x - inix >= MOVABLE_PLATFORM_RANGE) {
			toright = false;
			body.move(sf::Vector2f(-MOVABLE_PLATFORM_SPEED * deltaTime, 0));
		}

		if (body.getPosition().x - inix < 0.0f) {
			toright = true;
			body.move(sf::Vector2f(MOVABLE_PLATFORM_SPEED * deltaTime, 0));
		}
	}
}

Collider Platform::getCollider()
{
	return Collider(body);
}
