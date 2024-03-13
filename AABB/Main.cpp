//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "Wall.h"



int main() {
	srand((unsigned)time(0)); // inicializar números aleatorios
	sf::RenderWindow window(sf::VideoMode(800, 600), "jueguito");
	window.setFramerateLimit(60);
	sf::Event event;
	Player player;
	Wall wall;
	sf::Clock d_clock;
	sf::Time d_time;
	while (window.isOpen()) {
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (player.getCollidable().CheckCollision(wall.getCollidable(), 0.0f)) {
			player.update(d_time.asSeconds());
		}
		
		//Clear
		window.clear();
		//Draw
		player.Draw(window);
		wall.Draw(window);
		//Display
		window.display();
		//clock.restart();
		d_time = d_clock.restart();
	}
	return 0;
}