#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy()
{
	_texture.loadFromFile("enemy.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	_sprite.setPosition(600, 400);
	_velocity = { 3, 3 };
	_speed = 5;
	_timeRespawn = 60 * 3;
	_flag = true;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Enemy::update()
{
	if (_flag) {
		_newPosition = { (std::rand() % 700) + _sprite.getGlobalBounds().width, (std::rand() % 500) + _sprite.getGlobalBounds().height };
		_flag = false;
	}
	if (_newPosition == _sprite.getPosition()) {
		_timeRespawn--;
		_velocity = { 0, 0 };
		if (_timeRespawn < 0) {
			_newPosition = { (std::rand() % 700) + _sprite.getGlobalBounds().width, (std::rand() % 500) + _sprite.getGlobalBounds().height };
			_timeRespawn = 60 * 2;
		}

	}
	/*_timeRespawn--;
	if (_timeRespawn < 0) {
		_newPosition = { (std::rand() % 700) + _sprite.getGlobalBounds().width, (std::rand() % 500) + _sprite.getGlobalBounds().height};
		_timeRespawn = 60 * 3;
	}*/
	// Mover en linea recta
	/*if (_sprite.getPosition().x < _newPosition.x) {
		_sprite.move( _velocity.x, 0 );
	}
	if (_sprite.getPosition().x > _newPosition.x) {
		_sprite.move(-_velocity.x, 0);
	}
	if (_sprite.getPosition().y < _newPosition.y) {
		_sprite.move(0, _velocity.y);
	}
	if (_sprite.getPosition().y > _newPosition.y) {
		_sprite.move(0, -_velocity.y);
	}*/
	if (_sprite.getPosition().x < _newPosition.x) {
		_velocity.x = _speed;
	}
	if (_sprite.getPosition().x > _newPosition.x) {
		_velocity.x = -_speed;
	}
	if (_sprite.getPosition().y < _newPosition.y) {
		_velocity.y = _speed;
	}
	if (_sprite.getPosition().y > _newPosition.y) {
		_velocity.y = -_speed;
	}

	_sprite.move(_velocity);

	//// no tocar los bordes
	//if (_sprite.getGlobalBounds().left < 0) {
	//	_sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
	//	_velocity.x = -_velocity.x; // cambia la velocidad cuando impacta contra el borde
	//}
	//if (_sprite.getGlobalBounds().top < 0) {
	//	//_sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
	//	_velocity.y = -_velocity.y;
	//}
	//if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 800) {
	//	//_sprite.setPosition(800 - _sprite.getGlobalBounds().width + _sprite.getOrigin().x, _sprite.getPosition().y);
	//	_velocity.x = -_velocity.x;
	//}
	//if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 600) {
	//	//_sprite.setPosition(_sprite.getPosition().x, 600 - _sprite.getGlobalBounds().height + _sprite.getOrigin().y);
	//	_velocity.y = -_velocity.y;
	//}
	

	// corrige la vibración del movimiento por la diferencia entre la distancia recorrida y la posición a la que hay que llegar
	if (std::abs(_sprite.getPosition().x - _newPosition.x) < _speed + 1) {
		_sprite.setPosition(_newPosition.x, _sprite.getPosition().y);
	}
	if (std::abs(_sprite.getPosition().y - _newPosition.y) < _speed + 1) {
		_sprite.setPosition(_sprite.getPosition().x, _newPosition.y);
	}
}



sf::FloatRect Enemy::getBounds() const
{
	return _sprite.getGlobalBounds();
}

