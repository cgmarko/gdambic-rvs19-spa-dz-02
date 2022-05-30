#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "image.h"


int main()
{
	game_of_life game;


	//music downloaded from: https://www.fesliyanstudios.com/royalty-free-music/download/8-bit-surf/568
	sf::Music music;
	if (!music.openFromFile("music.ogg"))
		return -1; // error
	

	sf::RenderWindow window(sf::VideoMode(1600, 1000), "Hello, SFML world!");

	window.setFramerateLimit(60);
	image img(&window);
	img.set_num(0);
	img.set_moving(true);
	img.set_game_started(false);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (img.get_num()<4)
					{
						if (img.get_num() == 0)
						{
							img.set_num(3);
						}
						else if (!img.get_game_started() && img.get_num() == 2)
						{
							img.set_num(0);
						}
						else
						{
							img.set_num(img.get_num() - 1);
						}
					}
					else if (img.get_num() == 4)
					{
						img.set_moving(!img.get_moving());
					}
					break;
				case sf::Keyboard::Down:
					if (img.get_num()<4)
					{
						if (img.get_num() == 3)
						{
							img.set_num(0);
						}
						else if (!img.get_game_started() && img.get_num() == 0)
						{
							img.set_num(2);
						}
						else
						{
							img.set_num(img.get_num() + 1);
						}
					}
					else if (img.get_num() == 4)
					{
						img.set_moving(!img.get_moving());
					}
					break;
				case sf::Keyboard::Enter:
					if (img.get_num() == 0)
					{
						music.play();
						music.setLoop(true);
						img.set_num(5);
						img.set_game_started(true);
					}
					else if (img.get_num() == 1)
					{
						img.set_num(6);
					}
					else if (img.get_num() == 2)
					{
						img.set_num(4);
					}
					else if (img.get_num() == 3)
					{
						return 0;
					}
					else if (img.get_num() == 4)
					{
						img.set_num(2);
					}
					break;
				case sf:: Keyboard::Escape:
					if (img.get_num()<4)
					{
						if (img.get_game_started())
						{
							img.set_num(6);
						}
					}
					else if (img.get_num() == 4)
					{
						img.set_num(2);
					}
					else if (img.get_num() == 5 || img.get_num() == 6)
					{
						img.set_num(1);
					}
					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		img.draw(game);
		window.display();
	}

	return 0;
}