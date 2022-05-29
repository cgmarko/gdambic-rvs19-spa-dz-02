#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "image.h"

int main()
{
	srand(time(nullptr));
	game_of_life game;


	//music downloaded from: https://www.fesliyanstudios.com/royalty-free-music/download/8-bit-surf/568
	sf::Music music;
	if (!music.openFromFile("music.ogg"))
		return -1; // error
	music.play();
	music.setLoop(true);

	sf::RenderWindow window(sf::VideoMode(1600, 1000), "Hello, SFML world!");

	window.setFramerateLimit(60);
	image img(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		img.draw(game);
		window.display();
	}

	return 0;
}