#include "Animation.h"
#include <iostream>

Animation::Animation(const sf::Texture& text, const sf::Vector2u & size, float sw_time)
	: sw_time(sw_time), uvRect(0, 0, text.getSize().x/size.x, text.getSize().y/size.y), total_time(0)
{
}

Animation::~Animation()
{
}


void Animation::update(unsigned int an, float dTime, bool faceRight) {
	total_time += dTime;

	if (total_time >= sw_time) {
		total_time -= sw_time;
		uvRect.top = uvRect.height * an;
		uvRect.width = faceRight ? abs(uvRect.width) : -abs(uvRect.width);
		uvRect.left += abs(uvRect.width);
	}
}