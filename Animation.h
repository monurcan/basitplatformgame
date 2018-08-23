#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	sf::IntRect uvRect;

	Animation(const sf::Texture& text, const sf::Vector2u & size, float sw_time);
	~Animation();
	void update(unsigned int an, float dTime, bool faceRight);
private:
	float sw_time;
	float total_time;
};