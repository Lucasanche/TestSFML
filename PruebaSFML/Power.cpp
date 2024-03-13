#include <stdlib.h>
#include "Power.h"

Power::Power()
{
	_texture.loadFromFile("energy.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}

void Power::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Power::respawn()
{
	_sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, std::rand() % 500 + _sprite.getGlobalBounds().height);
}

sf::FloatRect Power::getBounds() const
{
	return _sprite.getGlobalBounds();
}
