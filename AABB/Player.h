#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Collidable.h"

class Player
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
	Player() {
		body.setSize({ 50,50 });
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition({ 500,300 });
		body.setFillColor(sf::Color::White);
		speed = 200.0f;
	}
	void Draw(sf::RenderWindow& window) {
		window.draw(body);
	}
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	sf::Vector2f getVelocity() { return velocity; }
	Collidable getCollidable() { return Collidable(body); }
	void update(float delta_time) {
		velocity = { 0,0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !right) {
			left = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				velocity.x += speed * delta_time;
			}
			else {
				velocity.x += -speed * delta_time;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !left) {
			right = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				velocity.x += -speed * delta_time;
			}
			else {
				velocity.x += speed * delta_time;
			}
		}
		else {
			right = left = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !up) {
			down = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				velocity.y += -speed * delta_time;
			}
			else {
				velocity.y += speed * delta_time;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !down) {
			up = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				velocity.y += speed * delta_time;
			}
			else {
				velocity.y += -speed * delta_time;
			}
		}
		else {
			up = down = false;
		}
		body.move(velocity);
	}
};

