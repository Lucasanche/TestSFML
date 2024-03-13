#pragma once
#include <SFML/Graphics.hpp>

class Collidable {
private:
	sf::RectangleShape& _origin_rect;
public: 
	Collidable(sf::RectangleShape origin_rect);
	bool CheckCollision(Collidable target_rect, float push);
	void move(float delta_x, float delta_y) { _origin_rect.move(delta_x, delta_y); }
	sf::Vector2f getPosition() { return _origin_rect.getPosition(); }
	sf::Vector2f getHalfSize() { return _origin_rect.getSize() / 2.0f; }
};

