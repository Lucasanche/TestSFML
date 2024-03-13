#include "Personaje.h"

Personaje::Personaje()
{
	_texture.loadFromFile("carlos.png"); // carga la textura para el sprite
	_sprite.setTexture(_texture); //setea la textura del sprite (duh)
    _velocity = { 10,10 }; // constructor de velocidad
    _sprite.setTextureRect({ 0, 0, 50, 49 });
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height); //setea el eje de origen en el medio horizontalmente
    _sprite.setPosition(150, 400);
    _energy = 50;
    _pasos = 0;
    _frame = 0;
    _frameMove = 0;
}
// El origen arriba a la izquierda es 0, para abajo y a la izquierda es positivo.
void Personaje::update()
{
    _frame += 0.1;

    if (_frame >= 4) {
        _frame = 0;
    }
    _sprite.setTextureRect({50 + int(_frame) * 50, 50 , 50, 50});
    _velocity = { 0,0 };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _velocity.y = 5;
        _sprite.setTextureRect({ 50*3, 50 * 8 , 50, 50 });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _velocity.y = -5;
        _sprite.setTextureRect({ 0, 50*8 , 50, 50 });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _velocity.x = -5;
        _frameMove += 0.2;
        if (_frameMove >= 8) {
            _frameMove = 0;
        }
        _sprite.setTextureRect({ 0 + int(_frameMove) * 50, 200 , 50, 50 });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _velocity.x = 5;
        _frameMove += 0.2;
        if (_frameMove >= 8) {
            _frameMove = 0;
        }
        _sprite.setTextureRect({ 0 + int(_frameMove) * 50, 200 , 50, 50 });
    }
    // el personaje se mueve a una velocidad especifica;
    if (_velocity.x != 0 || _velocity.y != 0) {
        _pasos++;
    }
    _sprite.move(_velocity);
    
    // setScale modifica la posición del sprite
    if (_velocity.x < 0) {
        _sprite.setScale(-1, 1);
    }
    else if (_velocity.x > 0) {
        _sprite.setScale(1, 1);
    }

    if (_sprite.getGlobalBounds().left < 0) {
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
        //_velocity.x = -_velocity.x; // cambia la velocidad cuando impacta contra el borde
    }
    if (_sprite.getGlobalBounds().top < 0) {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
        //_velocity.y = -_velocity.y;
    }
    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 800) {
        _sprite.setPosition(800 - _sprite.getGlobalBounds().width + _sprite.getOrigin().x, _sprite.getPosition().y);
        //_velocity.x = -_velocity.x;
    }
    if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 600) {
        _sprite.setPosition(_sprite.getPosition().x,600 - _sprite.getGlobalBounds().height + _sprite.getOrigin().y);
        //_velocity.y = -_velocity.y;
    }
    if (_pasos == 40) {
        _energy--;
        _pasos = 0;
    }
    
}

void Personaje::addEnergy(int energy)
{
    _energy += energy;
}

void Personaje::removeEnergy(int energy)
{
    _energy -= energy;
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}
