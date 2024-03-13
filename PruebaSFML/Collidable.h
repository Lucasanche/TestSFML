#pragma once
#include <SFML/Graphics.hpp>

class Collidable {

public: 
	virtual sf::FloatRect getBounds() const = 0;
	bool isCollision(Collidable& col) const;
};

