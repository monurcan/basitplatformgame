#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Shoot.h"
#include "Platform.h"
#include "Enemy.h"

constexpr float VIEW_HEIGHT = 812.0f;
int gameState = 1;

void Menu(sf::RenderWindow &window) {
	window.setView(sf::View(sf::Vector2f(VIEW_HEIGHT / 2, VIEW_HEIGHT / 2), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)));

	sf::Texture bgt;
	bgt.loadFromFile("menubg.png");
	sf::Sprite bg;
	bg.setTexture(bgt);

	sf::Font font;

	if (!font.loadFromFile("Minecraft.ttf")){
		std::cout << "Error loading font\n";
	}

	sf::CircleShape act(6, 3);
	act.setRotation(90);

	sf::Text b1;
	b1.setPosition(141, 321);
	b1.setFont(font);
	b1.setString("PLAY GAME");
	b1.setCharacterSize(21);

	sf::Text b2;
	b2.setPosition(115, 360);
	b2.setFont(font);
	b2.setString("HOW TO PLAY");
	b2.setCharacterSize(21);

	sf::Text b3;
	b3.setPosition(166, 398);
	b3.setFont(font);
	b3.setString("CREDITS");
	b3.setCharacterSize(21);

	sf::Text b4;
	b4.setPosition(205, 706);
	b4.setFont(font);
	b4.setString("QUIT");
	b4.setFillColor(sf::Color(242, 56, 45));
	b4.setCharacterSize(21);
	sf::Cursor mouseH, mouse;
	mouseH.loadFromSystem(sf::Cursor::Type::Hand);
	mouse.loadFromSystem(sf::Cursor::Type::Arrow);
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
		window.setMouseCursor(mouse);
		act.setPosition(-10, -10);
		if (b1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			window.setMouseCursor(mouseH);
			act.setPosition(131, 327);
		}
		else if (b2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			window.setMouseCursor(mouseH);
			act.setPosition(105, 366);
		}
		else if (b3.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			window.setMouseCursor(mouseH);
			act.setPosition(156, 404);
		}
		else if (b4.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			window.setMouseCursor(mouseH);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (b1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
				gameState = 2;
				window.setMouseCursor(mouse);
				return;
			}else if (b3.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
				gameState = 4;
				window.setMouseCursor(mouse);
				return;
			}else if (b4.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
				window.close();
				gameState = 0;
				return;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			gameState = 2;
			window.setMouseCursor(mouse);
			return;
		}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			gameState = 0;
			return;
		}

		window.clear();
		window.draw(bg);
		window.draw(b1);
		window.draw(b2);
		window.draw(b3);
		window.draw(b4);
		window.draw(act);
		window.display();
	}
}

void Game(sf::RenderWindow &window) {
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture tuxTecture;
	tuxTecture.setRepeated(1);
	tuxTecture.loadFromFile("za.png");

	sf::Texture bgt;
	bgt.loadFromFile("bg.png");
	bgt.setRepeated(1);
	sf::Sprite bg;
	bg.setTexture(bgt);

	sf::Texture flagt;
	flagt.loadFromFile("enesabi.png");

	sf::Texture chest;
	chest.loadFromFile("chest.png");

	sf::Texture grass;
	grass.loadFromFile("grass.png");

	sf::Texture movt;
	movt.loadFromFile("mov.png");

	Player player(tuxTecture, sf::Vector2u(9, 4), 0.1f, 200.0f, 150.0f);
	std::vector<Platform> platformVec;
	platformVec.reserve(10);
	platformVec.emplace_back(grass, sf::Vector2f(250.0f, 450.0f), sf::Vector2f(-100.0f, 280.0f));
	platformVec.emplace_back(grass, sf::Vector2f(460.0f, 460.0f), sf::Vector2f(300.0f, 220.0f));
	platformVec.emplace_back(grass, sf::Vector2f(490.0f, 440.0f), sf::Vector2f(1120.0f, 220.0f));
	platformVec.emplace_back(sf::Color::Color(123, 170, 28), sf::Vector2f(490.0f, 40.0f), sf::Vector2f(1850.0f, -80.0f));
	platformVec.emplace_back(grass, sf::Vector2f(490.0f, 410.0f), sf::Vector2f(1850.0f, 220.0f));
	platformVec.emplace_back(sf::Color::Color(207, 253, 69), sf::Vector2f(490.0f, 40.0f), sf::Vector2f(2550.0f, -130.0f));
	platformVec.emplace_back(grass, sf::Vector2f(490.0f, 410.0f), sf::Vector2f(2550.0f, 245.0f));
	platformVec.emplace_back(sf::Color::Color(70, 40, 56), sf::Vector2f(30.0f, 600.0f), sf::Vector2f(2810.0f, 150.0f));
	platformVec.emplace_back(grass, sf::Vector2f(490.0f, 430.0f), sf::Vector2f(3550.0f, 180.0f));
	platformVec.emplace_back(grass, sf::Vector2f(490.0f, 440.0f), sf::Vector2f(4850.0f, 220.0f));
	std::vector<Platform> movplatformVec;
	movplatformVec.reserve(2);
	movplatformVec.emplace_back(movt, sf::Vector2f(80.0f, 30.0f), sf::Vector2f(3050.0f, -250.0f), true);
	movplatformVec.emplace_back(movt, sf::Vector2f(280.0f, 30.0f), sf::Vector2f(4100.0f, -150.0f), true);
	Platform obs(sf::Color::Color(207, 253, 69), sf::Vector2f(50.0f, 50.0f), sf::Vector2f(450.0f, -35.0f));
	std::vector<Platform*> armorVec;
	armorVec.reserve(2);
	armorVec.emplace_back(new Platform(chest, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(-190.0f, 40.0f)));
	armorVec.emplace_back(new Platform(chest, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(2700.0f, 25.0f)));
	Platform flag(flagt, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(5310.0f, -150.0f));
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

		bg.setTextureRect(sf::IntRect(view.getCenter().x / 3, 0, 812, 812));
		bg.setPosition(player.getPosition().x - VIEW_HEIGHT / 2, player.getPosition().y - VIEW_HEIGHT / 2);
		window.draw(bg);

		player.draw(window);
		for (Enemy* &e : enemyVec) if(e) e->draw(window);
		for (Platform &plat : platformVec) plat.draw(window);
		for (Platform &plat : movplatformVec) plat.draw(window);
		for (Platform* &armor : armorVec) if(armor) armor->draw(window);
		obs.draw(window);
		flag.draw(window);
		shootobj.Update(dTime, window);
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

	sf::Text back;
	back.setPosition(0.0f, 0.0f);
	back.setFont(z);
	back.setString("<- back to menu!");
	back.setCharacterSize(34);
	back.setFillColor(sf::Color::Magenta);
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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			gameState = 1;
			return;
		}

		window.clear(sf::Color::Green);
		window.draw(vic);
		window.draw(back);
		window.display();
	}
}

void Credits(sf::RenderWindow &window) {
	window.setView(sf::View(sf::Vector2f(VIEW_HEIGHT / 2, VIEW_HEIGHT / 2), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)));
	sf::Font z;

	if (!z.loadFromFile("calibri.ttf")) {
		std::cout << "Error loading font\n";
	}
	sf::Text vic;
	vic.setPosition(0.0f, 0.0f);
	vic.setFont(z);
	vic.setString("dev: mok, tester: eek");
	vic.setCharacterSize(34);
	vic.setFillColor(sf::Color::Yellow);
	vic.setStyle(sf::Text::Bold);

	sf::Text back;
	back.setPosition(0.0f, 50.0f);
	back.setFont(z);
	back.setString("<- back to menu!");
	back.setCharacterSize(34);
	back.setFillColor(sf::Color::White);
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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			gameState = 1;
			return;
		}

		window.clear(sf::Color::Color(211, 122, 154));
		window.draw(vic);
		window.draw(back);
		window.display();
	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "Prof's Adventures", sf::Style::Resize | sf::Style::Close);
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
			case 4:
				Credits(window);
				break;
		}
	}

	return EXIT_SUCCESS;
}