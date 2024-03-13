#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Collidable.h"

class Wall
{
private:
	sf::RectangleShape body;
	float speed;
	sf::Vector2f velocity;
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
public:
	Wall() {
		body.setSize({ 20,200 });
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition({ 100,300 });
		body.setFillColor(sf::Color::White);
		speed = 200.0f;
	}
	void Draw(sf::RenderWindow& window) {
		window.draw(body);
	}
	Collidable getCollidable() { return Collidable(body); }
};

