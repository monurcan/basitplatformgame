#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	//temel tipleri const ref ile almana gerek yok zaten pointer gibi bi şi ref
	Player(const sf::Texture& text, const sf::Vector2u & size, float sw_time, float speed, float jumpHeight);
	~Player();
	void Update(float deltaTime);
	void draw( sf::RenderWindow &window);
	void onCollision(sf::Vector2f &direction);
	const sf::Vector2f getPosition() const;
	const bool isFall() const;
	Collider getCollider();
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

