#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <clocale>


int main() {
	srand((unsigned)time(0)); // inicializar números aleatorios
	sf::RenderWindow window(sf::VideoMode(800, 600), "jueguito");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock d_clock;
	sf::Time d_time;
	sf::Font font;
	sf::Text text;
	font.loadFromFile("./Fonts/Nostalgia.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	//setlocale(LC_ALL, "Spanish");
	sf::String string;
	string = "hola como va? ñ\ntodo bien?";
	text.setPosition(100, 100);
	float i = 0;
	int j = 0;
	while (window.isOpen()) {
		d_time = d_clock.restart();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Clear
		window.clear();
		//Draw
		if (i > 1) {
			if (j < string.getSize()) {
				text.setString(text.getString() + string.substring(j, 1));
				j++;
			}
			i = 0;
		}
		window.draw(text);
		//Display
		window.display();
		i+=d_time.asSeconds()*50;
	}
	return 0;
}