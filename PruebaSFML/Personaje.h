#pragma once
#include <SFML\Graphics.hpp>
#include "Collidable.h"
class Personaje: public sf::Drawable, public Collidable
{
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _velocity; // vector de 2 dimensiones para la posición x e y;
	// float _velocity = 10;
	int _energy;
	int _pasos;
	float _frame;
	float _frameMove;
public:
	Personaje();
	void update();
	void addEnergy(int);
	void removeEnergy(int);
	int getEnergy() { return _energy; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect getBounds() const override;
};

