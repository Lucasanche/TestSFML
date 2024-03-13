#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personaje.h"
#include "Item.h"
#include "Power.h"
#include "Enemy.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>

int main()
{
	// Inicialización de la ventana
	srand((unsigned)time(0)); // inicializar números aleatorios

	sf::RenderWindow window(sf::VideoMode(800, 600), "jueguito");
	window.setFramerateLimit(60);

	Personaje megaman;

	Enemy jetstringray;
	Item vida;
	vida.respawn();
	bool coso = false;
	Power power;
	int timer = 0;
	power.respawn();
	int puntos = 0;
	bool colision = true;
	sf::Font font;
	sf::Text puntaje;
	sf::Text gameover;
	sf::Text text_energy;

	sf::Texture background;
	background.loadFromFile("fondo.png");
	sf::Sprite backgroundsprite;
	backgroundsprite.setTexture(background);

	sf::SoundBuffer bufferVida;
	bufferVida.loadFromFile("ItemSounds/vida.wav");
	sf::Sound sonidoVida;
	sonidoVida.setBuffer(bufferVida);

	sf::SoundBuffer bufferEnergy;
	bufferEnergy.loadFromFile("ItemSounds/energy.wav");
	sf::Sound sonidoEnergy;
	sonidoEnergy.setBuffer(bufferEnergy);

	sf::SoundBuffer bufferGO;
	bufferGO.loadFromFile("ItemSounds/gameover.wav");
	sf::Sound sonidoGO;
	sonidoGO.setBuffer(bufferGO);
	int bGameover = 1;

	font.loadFromFile("Fonts/Nostalgia.ttf");
	text_energy.setFont(font);
	gameover.setFont(font);
	puntaje.setFont(font);
	gameover.setString("GAME OVER");
	gameover.setPosition(400, 300);
	gameover.setOrigin(gameover.getGlobalBounds().width / 2, gameover.getGlobalBounds().height / 2);

	// Game Loop (update del juego)
	while (window.isOpen())
	{
		/* readinput: actualizar los estados de los periféricos de entrada.*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// CMD


		// Update - Actualiza los estados del juego

		if (megaman.getEnergy() > 0) {
			megaman.update();
			jetstringray.update();
			if (megaman.isCollision(vida)) {
				if (timer < 2) {
					timer++;
				}
				sonidoVida.play();
				vida.respawn();
				puntos++;
			}
			if (megaman.isCollision(jetstringray)) {
				if (colision) {
					megaman.removeEnergy(5);
					sonidoGO.play();
					colision = false;

				}
			}
			else {
				colision = true;
			}


			if (timer == 2 && megaman.isCollision(power)) {
				megaman.addEnergy(2);
				power.respawn();
				sonidoEnergy.play();
				timer = 0;
			}
			text_energy.setString(" Energia: " + std::to_string(megaman.getEnergy()));
			text_energy.setPosition(0, 50);
			puntaje.setString(" Puntaje: " + std::to_string(puntos));



			// Draw

			window.clear();
			window.draw(backgroundsprite);

			window.draw(jetstringray);
			window.draw(megaman);
			window.draw(vida);
			window.draw(puntaje);
			window.draw(text_energy);

			if (timer == 2) {
				window.draw(power);
			}
		}
		else {
			window.clear();
			if (bGameover == 1) {
				sonidoGO.play();
				bGameover = 0;
			}
			window.draw(gameover);
		}


		// Display - Flip


		window.display();
	}

	// Liberación del Juego

	return 0;
}
