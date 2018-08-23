#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Shoot.h"
#include "Platform.h"
#include "Enemy.h"

constexpr float VIEW_HEIGHT = 812.0f;
int gameState = 2;

void Menu(sf::RenderWindow &window) {
	window.setView(sf::View(sf::Vector2f(VIEW_HEIGHT / 2, VIEW_HEIGHT / 2), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)));
	sf::Font font;

	if (!font.loadFromFile("calibri.ttf")){
		std::cout << "Error loading font\n";
	}
	sf::Text title;
	title.setFont(font);
	title.setString("ONURCAN'IN OYUNU");
	title.setCharacterSize(54);
	title.setFillColor(sf::Color::Magenta);
	title.setStyle(sf::Text::Bold);

	sf::Text text;
	text.setPosition(200, 160);
	text.setFont(font);
	text.setString("Play Game");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	while (window.isOpen())
	{
		sf::Event evt;

		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				gameState = 0;
				return;
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
				gameState = 2;
				return;
			}
		}

		window.clear();
		window.draw(text);
		window.draw(title);
		window.display();
	}
}

void Game(sf::RenderWindow &window) {
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture tuxTecture;
	tuxTecture.setRepeated(1);
	tuxTecture.loadFromFile("za.png");

	sf::Texture flagt;
	flagt.loadFromFile("enesabi.png");

	sf::Texture chest;
	chest.loadFromFile("chest.png");

	Player player(tuxTecture, sf::Vector2u(9, 4), 0.1f, 200.0f, 150.0f);
	std::vector<Platform> platformVec;
	platformVec.reserve(10);
	platformVec.emplace_back(sf::Color::Blue, sf::Vector2f(250.0f, 50.0f), sf::Vector2f(-100.0f, 50.0f));
	platformVec.emplace_back(sf::Color::Red, sf::Vector2f(460.0f, 60.0f), sf::Vector2f(300.0f, 20.0f));
	platformVec.emplace_back(sf::Color::Green, sf::Vector2f(490.0f, 40.0f), sf::Vector2f(1120.0f, 20.0f));
	platformVec.emplace_back(sf::Color::Color(130, 226, 14), sf::Vector2f(490.0f, 40.0f), sf::Vector2f(1850.0f, -80.0f));
	platformVec.emplace_back(sf::Color::Green, sf::Vector2f(490.0f, 10.0f), sf::Vector2f(1850.0f, 20.0f));
	platformVec.emplace_back(sf::Color::Color(230, 126, 34), sf::Vector2f(490.0f, 40.0f), sf::Vector2f(2550.0f, -130.0f));
	platformVec.emplace_back(sf::Color::Yellow, sf::Vector2f(490.0f, 10.0f), sf::Vector2f(2550.0f, 45.0f));
	platformVec.emplace_back(sf::Color(231, 76, 60), sf::Vector2f(80.0f, 200.0f), sf::Vector2f(2795.0f, -50.0f));
	platformVec.emplace_back(sf::Color::Red, sf::Vector2f(490.0f, 30.0f), sf::Vector2f(3550.0f, -20.0f));
	platformVec.emplace_back(sf::Color::Green, sf::Vector2f(490.0f, 40.0f), sf::Vector2f(4250.0f, 20.0f));
	std::vector<Platform> movplatformVec;
	movplatformVec.reserve(1);
	movplatformVec.emplace_back(sf::Color(225, 177, 44), sf::Vector2f(80.0f, 30.0f), sf::Vector2f(3050.0f, -250.0f), true);
	Platform obs(sf::Color::Black, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(450.0f, -35.0f));
	std::vector<Platform*> armorVec;
	armorVec.reserve(2);
	armorVec.emplace_back(new Platform(chest, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(-100.0f, -20.0f)));
	armorVec.emplace_back(new Platform(chest, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(2700.0f, 0.0f)));
	Platform flag(flagt, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(4650.0f, -20.0f));
	std::vector<Enemy*> enemyVec;
	enemyVec.reserve(2);
	enemyVec.emplace_back(new Enemy(sf::Vector2f(150.0f, -70.0f)));
	enemyVec.emplace_back(new Enemy(sf::Vector2f(2350.0f, -210.0f)));
	Shoot shootobj(player);

	sf::Clock clock;
	while (window.isOpen())
	{
		float dTime = clock.restart().asSeconds();
		if (dTime > 1.0f / 20.0f)
			dTime = 1.0f / 20.0f;
		sf::Event evt;

		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				gameState = 0;
				return;
				break;
			case sf::Event::Resized:
				view.setSize(float(window.getSize().x) / float(window.getSize().y) * VIEW_HEIGHT, VIEW_HEIGHT);
				break;
			}
		}


		player.Update(dTime);
		for (Enemy* &e : enemyVec) if(e) e->update(dTime);
		for (Platform &b : movplatformVec) b.update(dTime);

		sf::Vector2f direction;

		if (player.isFall()) {
			gameState = 1;
			return;
		}

		Collider playerCol = player.getCollider();
		for (Platform &plat : platformVec)
			if (plat.getCollider().checkCollision(playerCol, direction, 1.0f))
				player.onCollision(direction);

		for (Platform &plat : movplatformVec)
			if (plat.getCollider().checkCollision(playerCol, direction, 1.0f))
				player.onCollision(direction);
		
		if (obs.getCollider().checkCollision(playerCol, direction, 0.5f))
			player.onCollision(direction);

		if(flag.getCollider().checkCollision(playerCol, direction, 1.0f)){
			gameState = 3;
			return;
		}
		
		for(Platform* &armor : armorVec)
		if (armor && armor->getCollider().checkCollision(playerCol, direction, 1.0f)) {
			shootobj.charge();
			delete armor;
			armor = nullptr;
		}

		for(Enemy* &e : enemyVec)
			if (e) {
				if (e->getCollider().checkCollision(playerCol, direction, 1.0f)) {
					gameState = 1;
					return;
				}

				Collider eCol = e->getCollider();
				if (shootobj.isShoot(eCol)) {
					delete e;
					e = nullptr;
				}
			}

		view.setCenter(player.getPosition());
		window.setView(view);
		window.clear(sf::Color(150, 150, 150));

		player.draw(window);
		shootobj.Update(dTime, window);
		for (Enemy* &e : enemyVec) if(e) e->draw(window);
		for (Platform &plat : platformVec) plat.draw(window);
		for (Platform &plat : movplatformVec) plat.draw(window);
		for (Platform* &armor : armorVec) if(armor) armor->draw(window);
		obs.draw(window);
		flag.draw(window);
		window.display();
	}
}


void Victory(sf::RenderWindow &window) {
	window.setView(sf::View(sf::Vector2f(VIEW_HEIGHT / 2, VIEW_HEIGHT / 2), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)));
	sf::Font z;

	if (!z.loadFromFile("calibri.ttf")) {
		std::cout << "Error loading font\n";
	}
	sf::Text vic;
	vic.setPosition(0.0f, 0.0f);
	vic.setFont(z);
	vic.setString("enes abiyi kaptin tebrikler!");
	vic.setCharacterSize(34);
	vic.setFillColor(sf::Color::Yellow);
	vic.setStyle(sf::Text::Bold);
	while (window.isOpen())
	{
		sf::Event evt;

		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				gameState = 0;
				return;
				break;
			}
		}

		window.clear(sf::Color::Green);
		window.draw(vic);
		window.display();
	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "za!", sf::Style::Resize | sf::Style::Close);
	window.setFramerateLimit(30);

	while (gameState) {
		switch (gameState) {
			case 1:
				Menu(window);
				break;

			case 2:
				Game(window);
				break;
			case 3:
				Victory(window);
				break;
		}
	}

	return EXIT_SUCCESS;
}