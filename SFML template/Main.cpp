#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>



int main() {
	srand((unsigned)time(0)); // inicializar números aleatorios
	sf::RenderWindow window(sf::VideoMode(800, 600), "jueguito");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock d_clock;
	sf::Time d_time;
	while (window.isOpen()) {
		d_time = d_clock.restart();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Clear
		window.clear();
		//Draw

		//Display
		window.display();
	}
	return 0;
}