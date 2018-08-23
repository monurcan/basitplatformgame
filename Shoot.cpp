#include "Shoot.h"

Shoot::Shoot(Player & player)
	: player(player), aim(sf::Vector2f(50, 50)), aimline(sf::Vector2f(60, 2)), theta(0), guncount(0)
{
	aimbgT.loadFromFile("aimbg.png");
	aim.setTexture(&aimbgT);
	aim.setOrigin(sf::Vector2f(-25.0f, 50.0f));
	aimline.setFillColor(sf::Color::Red);

	for (int i = 0; i < 5; i++) {
		gunc[i] = sf::RectangleShape(sf::Vector2f(6, 14));
		gunc[i].setFillColor(sf::Color(143, 125, 75));
		gunc[i].setPosition(player.getPosition().x - 250 + i*9, player.getPosition().y + 250);
	}
}

void Shoot::activate(sf::RenderWindow & window)
{
	if (guncount) {
		sf::Vector2f mouse_world = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		theta = 57.2957796f * atan((-mouse_world.y + player.getPosition().y) / (+mouse_world.x - player.getPosition().x - 25));
		theta = std::max(0.0f, std::min(90.0f, theta));
		aimline.setRotation(-theta);
		aimline.setPosition(player.getPosition().x + 25, player.getPosition().y);

		aim.setPosition(player.getPosition());
		window.draw(aim);
		window.draw(aimline);
	}
}

void Shoot::shoot() {
	if (guncount) {
		bullets.push_back(Bullet(theta, aimline.getPosition()));
		guncount--;
	}
}

void Shoot::charge()
{
	guncount = 5;
}

void Shoot::Update(float deltaTime, sf::RenderWindow & window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		this->activate(window);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		this->activate(window);
		this->shoot();
	}

	for (Bullet & b : bullets) {
		b.Update(deltaTime);
		b.draw(window);
	}

	for (int i = 0; i < guncount; i++) {
		gunc[i].setPosition(player.getPosition().x - 350 + i * 9, player.getPosition().y + 350);
		window.draw(gunc[i]);
	}
}

bool Shoot::isShoot(Collider & enemyc)
{
	bool isS = false;
	sf::Vector2f direction(0.0f, 0.0f);
	for (Bullet & b : bullets) {
		isS = b.getCollider().checkCollision(enemyc, direction, 0.0f);
	}

	return isS;
}

Shoot::~Shoot()
{
}
