#pragma once
#include <SFML\Graphics.hpp>
#include "Collidable.h"

class Enemy : public sf::Drawable, public Collidable
{
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _velocity;
	int _timeRespawn;
	int _speed;
	sf::Vector2f _newPosition;
	bool _flag;
public:
	Enemy();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();
	sf::FloatRect getBounds() const override;
};
