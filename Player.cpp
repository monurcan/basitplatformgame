#include "Player.h"


Player::Player(const sf::Texture& text, const sf::Vector2u & size, float sw_time, float speed, float jumpHeight)
	: animation(text, size, sw_time), speed(speed), row(0), faceRight(true), body(sf::Vector2f(48.0f, 78.0f)), jumpHeight(jumpHeight)
{
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(&text);
	//body.setPosition(4550, -160);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
	velocity.y += 981.0f * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		velocity.x += speed;

	if (velocity.x == 0)
		row = 1;
	else {
		row = 3;
		faceRight = (velocity.x > 0) ? true : false;
	}
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::draw( sf::RenderWindow & window)
{
	window.draw(body);
}

void Player::onCollision(sf::Vector2f &direction)
{
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;
		canJump = false;
	}
	else if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		canJump = true;
	}
}

const sf::Vector2f Player::getPosition() const
{
	return body.getPosition();
}

const bool Player::isFall() const
{
	return velocity.y > 1000.0f;
}

Collider Player::getCollider()
{
	canJump = false;
	return Collider(body);
}
