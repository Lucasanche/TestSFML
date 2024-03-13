#include <stdlib.h>
#include "Item.h"

Item::Item()
{
    _texture.loadFromFile("vida.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height/2);
}

void Item::update()
{
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Item::respawn()
{
    // divide a "rand()" por 700 y te da de resultado el resto (un numero entre 0 y 700), y se le puede sumar un número para subir el número más bajo
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, std::rand() % 500 + _sprite.getGlobalBounds().height);

}

sf::FloatRect Item::getBounds() const
{
    //Devuelve el tamaño del borde
    return _sprite.getGlobalBounds();
}
