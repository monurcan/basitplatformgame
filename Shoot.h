#pragma once
#include "Player.h"
#include "Bullet.h"

class Shoot
{
public:
	Shoot(Player &player);
	void activate(sf::RenderWindow & window);
	void shoot();
	void charge();
	void Update(float deltaTime, sf::RenderWindow & window);
	bool isShoot(Collider &enemyc);
	~Shoot();

private:
	Player &player;
	sf::RectangleShape aim;
	sf::Texture aimbgT;
	sf::RectangleShape aimline;
	std::vector<Bullet> bullets;
	sf::RectangleShape gunc[5];
	float theta;
	char guncount;
};

