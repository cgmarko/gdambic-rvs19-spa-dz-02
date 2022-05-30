#include "image.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

using namespace std;


image::image(sf::RenderWindow* window)
{
	this->window = window;
}

void image::set_red()
{
	r = rand() % 256;
}
void image::set_green()
{
	g = rand() % 256;
}
void image::set_blue()
{
	b = rand() % 256;
}

bool image::get_game_started()
{
	return game_started;
}

void image::set_game_started(bool b)
{
	game_started = b;
}

void image::menu(int num)
{
	double t = clock.getElapsedTime().asSeconds();
	double f1 = abs(sin(PI / 2 * t))/2 + 0.5;
	double f2 = abs(sin(PI / 2 * t));
	double f3; 
	double f4;
	double f5;

	sf::Font font;
	if (!font.loadFromFile("OpenSans.ttf"))
	{
		// error...
	}
	sf::Text text;
	
	
	sf::RectangleShape menuBackground;
	menuBackground.setSize(sf::Vector2f(1600, 1000));
	menuBackground.setPosition(0, 0);
	menuBackground.setFillColor(sf::Color(255, 87, 51));
	window->draw(menuBackground);
	int c = 0;

	
	menuBackground.setSize(sf::Vector2f(1600, 1000));
	menuBackground.setPosition(0, 0);
	menuBackground.setFillColor(sf::Color(255, 87, 51));
	window->draw(menuBackground);
	

	vector<sf::ConvexShape> Sunshine;
	Sunshine.resize(16);
	for (int i = 0; i < 16; i++)
	{
		f3 = cos(PI /  8* i + 2*t*game_started); //rotation around x-coordinate
		f4 = sin(PI / 8 * i + 2*t*game_started); //rotation around y-coordinate
		
		Sunshine[i].setPointCount(4);
		Sunshine[i].setFillColor(sf::Color(r * f1 * game_started, g * f1 * game_started, b * f1 * game_started));
		Sunshine[i].setPoint(0, sf::Vector2f( 800, 500));
		Sunshine[i].setPoint(1, sf::Vector2f((900 - 800) * f3 - (450 - 500) * f4 + 800, (900 - 800) * f4 + (450 - 500) * f3 + 500));
		Sunshine[i].setPoint(2, sf::Vector2f((1000-800)*f3 + 800, (1000-800) * f4 + 500));
		Sunshine[i].setPoint(3, sf::Vector2f((900 - 800) * f3 - (550 - 500) * f4 + 800, (900 - 800) * f4 + (550 - 500) * f3 + 500));
		window->draw(Sunshine[i]);

	}
	
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color(0, 0, 0));
	for (int i = 0; i < 4; i++)
	{
		text.setPosition(120, 700 + 55 * i);
		if (i == get_num())
		{
			continue;
		}
		switch (i)
		{
		case 0:
			text.setString("New Game");
			break;
		case 1:
			if (!get_game_started())
			{
				text.setFillColor(sf::Color(100, 100, 100));
				text.setString("Continue Game");
				window->draw(text);
			}
			text.setString("Continue Game");
			break;
		case 2:
			if (get_num()!=4)
			{
				text.setFillColor(sf::Color(0, 0, 0));
				text.setString("Options");
			}
			if (get_num() == 4)
			{
				text.setFillColor(sf::Color(0, 0, 0));
				if (get_moving())
				{
					text.setString("Dynamic");
					text.setPosition(120 + 20, 700 + 55 * i);
				}
				else if (!get_moving())
				{
					text.setString("Static");
					text.setPosition(120 + 20, 700 + 55 * i);
				}
			}
			break;
		case 3:
			text.setFillColor(sf::Color(0, 0, 0));
			text.setString("Quit");
			break;
		default:
			break;
		}
		
		window->draw(text);
	}
	c = 0;
	switch (get_num())
	{
	case 0:
		text.setString("New Game");
		text.setPosition(120 - 20, 700 + 55 * get_num());
		window->draw(text);
		break;
	case 1:
		text.setString("Continue Game");
		text.setPosition(120 - 20, 700 + 55 * get_num());
		window->draw(text);
		break;
	case 2:
		
		text.setString("Options");
		text.setPosition(120 - 20, 700 + 55 * get_num());
		window->draw(text);
		break;
	case 3:

		text.setString("Quit");
		text.setPosition(120-20, 700 + 55 * get_num());
		window->draw(text);
		break;
	case 4:
		
		break;
	default:
		break;
	}
}

void image::set_num(int n)
{
	num = n;
}

int image::get_num()
{
	return num;
}

bool image::get_moving()
{
	return moving;
}

void image::set_moving(bool b)
{
	moving = b;
}

void image::background()
{
	double t = clock.getElapsedTime().asSeconds();
	double f1 = abs(sin(PI / 2 * t)); //transition 0>1>0
	sf::RectangleShape background(sf::Vector2f(1600, 1000));
	background.setFillColor(sf::Color(r * f1, g * f1, b * f1));
	background.setPosition(0, 0);
	window->draw(background);
}

void image::to_live(game_of_life& game)
{
	double t = clock.getElapsedTime().asSeconds();
	double f1 = sin(PI * 0.03125 * pow(4, t)); //transition 0>1, accelerated
	double f2 = abs(sin(PI / 2 * t)); //transition 0>1>0
	double f5 = 80 * sin(PI * t) * get_moving(); //moving elements on x-axis
	double f6 = 60 * sin(2 * PI * t) * get_moving(); //moving elements on y-axis

	vector<sf::CircleShape> outerCircles;
	outerCircles.resize(160);

	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_alive(c) && !game.get_just_born(c))
			{
				outerCircles[c].setRadius(25);
				outerCircles[c].setPosition((50 + 200 * j) / 2 + f5, (50 + 200 * i) / 2 + f6);
				outerCircles[c].setFillColor(sf::Color(255, 255 * f2, 0));
				outerCircles[c].setOutlineThickness(5.f);
				outerCircles[c].setOutlineColor(sf::Color(255, 255 * f2, 0));
				window->draw(outerCircles[c]);
			}
			c++;
		}

	}

	int l;
	double f3;
	double f4;
	vector<sf::ConvexShape> Stars;
	Stars.resize(160 * 8);
	c = 0;
	int d = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (game.get_alive(c) && !game.get_just_born(c))
				{
					l = 0;
					f3 = cos(PI / 4 * k + PI * 4 * sin(PI / 4 * t)); //rotation around x-coordinate
					f4 = sin(PI / 4 * k + PI * 4 * sin(PI / 4 * t)); //rotation around y-coordinate
					if (k % 2 != 0)
					{
						l = 5;
					}
					Stars[d].setPointCount(4);
					Stars[d].setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
					Stars[d].setPoint(0, sf::Vector2f((100 + 200 * j) / 2 + f5, (100 + 200 * i) / 2 + f6));
					Stars[d].setPoint(1, sf::Vector2f((25 * f3 + (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (90 - 100 + l) * f3 + (100 + 200 * i)) / 2 + f6));
					Stars[d].setPoint(2, sf::Vector2f(((50 - 2 * l) * f3 + (100 + 200 * j)) / 2 + f5, ((150 - 100 - 2 * l) * f4 + (100 + 200 * i)) / 2 + f6));
					Stars[d].setPoint(3, sf::Vector2f((25 * f3 - (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (110 - 100 - l) * f3 + (100 + 200 * i)) / 2 + f6));

					window->draw(Stars[d]);

				}
				d++;
			}
			c++;
		}
	}

	vector<sf::CircleShape> innerCircles;
	innerCircles.resize(160);
	c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (game.get_alive(c) && !game.get_just_born(c))
			{
				innerCircles[c].setRadius(5);
				innerCircles[c].setPosition((90 + 200 * j) / 2 + f5, (90 + 200 * i) / 2 + f6);
				innerCircles[c].setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
				innerCircles[c].setOutlineThickness(2.5);
				innerCircles[c].setOutlineColor(sf::Color(255, 255 * f2, 0));
				window->draw(innerCircles[c]);
			}
			c++;
		}

	}

}

void image::to_die(game_of_life& game)
{
	
	double t = clock.getElapsedTime().asSeconds();
	double f0 = sin(PI / 4 * t); //0 > 1, used for shrinking star
	double f1 = cos(PI / 4 * 0.125 * pow(4, t)); //transition 1>0, accelerated
	double f2 = 1 - f0 / 2; //transition 1 > 0.5
	double f3 = abs(sin(PI / 2 * t)); //transition 0>1>0
	double f5 = 80 * sin(PI * t) * get_moving(); //rotation around x-coordinate
	double f6 = 60 * sin(2 * PI * t) * get_moving(); //rotation around y-coordinate
	vector<sf::CircleShape> outerCircles;
	outerCircles.resize(160);
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_dying(c))
			{
				outerCircles[c].setRadius(50 * f1 / 2);
				outerCircles[c].setPosition((100 - 50 * f1 + 200 * j) / 2 + f5, (100 - 50 * f1 + 200 * i) / 2 + f6);
				outerCircles[c].setFillColor(sf::Color(255 * f2, 0, 0));
				outerCircles[c].setOutlineThickness(2.5);
				outerCircles[c].setOutlineColor(sf::Color(255 * f2, 0, 0));
				window->draw(outerCircles[c]);
			}
			c++;
		}

	}
	c = 0;
	int d = 0;
	vector<sf::ConvexShape> Stars;
	Stars.resize(160 * 8);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				int l = 0;
				if (game.get_dying(c))
				{
					if (k % 2 != 0)
					{
						l = 5;
					}
					Stars[d].setPointCount(4);
					Stars[d].setFillColor(sf::Color(255 * f3, 255 * f3, 255 * f3));
					Stars[d].setPoint(0, sf::Vector2f((100 + 200 * j) / 2 + f5, (100 + 200 * i) / 2 + f6));
					Stars[d].setPoint(1, sf::Vector2f(((125 - 100 - f0 * 25) * cos(PI / 4 * k + PI * 4 * f0) - (90 - 100 + l) * sin(PI / 4 * k + PI * 4 * f0) + (100 + 200 * j)) / 2 + f5, ((125 - 100 - f0 * 25) * sin(PI / 4 * k + PI * 4 * f0) + (90 - 100 + l) * cos(PI / 4 * k + PI * 4 * f0) + (100 + 200 * i)) / 2 + f6));
					Stars[d].setPoint(2, sf::Vector2f(((150 - 100 - 2 * l - f0 * 25) * cos(PI / 4 * k + PI * 4 * f0) + (100 + 200 * j)) / 2 + f5, ((150 - 100 - 2 * l - f0 * 25) * sin(PI / 4 * k + PI * 4 * f0) + (100 + 200 * i)) / 2 + f6));
					Stars[d].setPoint(3, sf::Vector2f(((125 - 100 - f0 * 25) * cos(PI / 4 * k + PI * 4 * f0) - (110 - 100 - l) * sin(PI / 4 * k + PI * 4 * f0) + (100 + 200 * j)) / 2 + f5, ((125 - 100 - f0 * 25) * sin(PI / 4 * k + PI * 4 * f0) + (110 - 100 - l) * cos(PI / 4 * k + PI * 4 * f0) + (100 + 200 * i)) / 2 + f6));
					window->draw(Stars[d]);
				}
				d++;
			}
			c++;

		}
	}

	vector<sf::CircleShape> innerCircles;
	innerCircles.resize(160);

	c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (game.get_dying(c))
			{
				innerCircles[c].setRadius(5);
				innerCircles[c].setPosition((90 + 200 * j) / 2 + f5, (90 + 200 * i) / 2 + f6);
				innerCircles[c].setFillColor(sf::Color(255 * f3, 255 * f3, 255 * f3));
				innerCircles[c].setOutlineThickness(2.5);
				innerCircles[c].setOutlineColor(sf::Color(255 * f3, 255 * f3, 0));
				window->draw(innerCircles[c]);
			}
			c++;
		}

	}

}




void image::birth(game_of_life& game)
{

	double t = clock.getElapsedTime().asSeconds();
	vector<sf::CircleShape> outerCircles;
	outerCircles.resize(160);

	double f1 = sin(PI * 0.03125 * pow(4, t)); //transition 0>1, accelerated
	double f2 = abs(sin(PI / 2 * t)); //transition 0>1
	double f5 = 80 * sin(PI * t)*get_moving(); //rotation around x-coordinate
	double f6 = 60 * sin(2 * PI * t) * get_moving(); //rotation around y-coordinate
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_just_born(c))
			{

				outerCircles[c].setRadius(25 * f1);
				outerCircles[c].setPosition((100 - 50 * f1 + 200 * j) / 2 + f5, (100 - 50 * f1 + 200 * i) / 2 + f6);
				outerCircles[c].setFillColor(sf::Color(255, 255 * f2, 0));
				outerCircles[c].setOutlineThickness(5.f);
				outerCircles[c].setOutlineColor(sf::Color(255, 255 * f2, 0));
				window->draw(outerCircles[c]);
			}
			c++;
		}

	}
	c = 0;
	int d = 0;
	int l;
	double f3;
	double f4;
	vector<sf::ConvexShape> Stars;
	Stars.resize(160 * 8);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (game.get_just_born(c))
				{
					l = 0;
					f3 = cos(PI / 4 * k + PI * 4 * sin(PI / 4 * t)); //rotation around x-coordinate
					f4 = sin(PI / 4 * k + PI * 4 * sin(PI / 4 * t)); //rotation around y-coordinate
					if (k % 2 != 0)
					{
						l = 5;
					}
					Stars[d].setPointCount(4);
					Stars[d].setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
					Stars[d].setPoint(0, sf::Vector2f((100 + 200 * j) / 2 + f5, (100 + 200 * i) / 2 + f6));
					Stars[d].setPoint(1, sf::Vector2f((25 * f3 + (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (90 - 100 + l) * f3 + (100 + 200 * i)) / 2 + f6));
					Stars[d].setPoint(2, sf::Vector2f(((50 - 2 * l) * f3 + (100 + 200 * j)) / 2 + f5, ((150 - 100 - 2 * l) * f4 + (100 + 200 * i)) / 2 + f6));
					Stars[d].setPoint(3, sf::Vector2f((25 * f3 - (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (110 - 100 - l) * f3 + (100 + 200 * i)) / 2 + f6));

					window->draw(Stars[d]);
				}
				d++;
			}
			c++;
		}
	}

	vector<sf::CircleShape> innerCircles;
	innerCircles.resize(160);
	c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_just_born(c))
			{
				innerCircles[c].setRadius(5);
				innerCircles[c].setPosition((90 + 200 * j) / 2 + f5, (90 + 200 * i) / 2 + f6);
				innerCircles[c].setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
				innerCircles[c].setOutlineThickness(2.5);
				innerCircles[c].setOutlineColor(sf::Color(255, 255 * f2, 0));
				window->draw(innerCircles[c]);
			}
			c++;

		}

	}
}

void image::draw(game_of_life& game)
{
	if (num <5)
	{
		menu(5);
	}
	else
	{
		if (get_num() == 5)
		{
			set_num(6);
			clock.restart();
			for (int i = 0; i < 160; i++)
			{
				switch (rand() % 4)
				{
				case 0:
					game.set_alive(i, true);
					game.set_just_born(i, true);
					game.set_dead(i, false);
					game.set_dying(i, false);
					break;
				case 1:
					game.set_alive(i, false);
					game.set_just_born(i, false);
					game.set_dead(i, true);
					game.set_dying(i, false);
					break;
				case 2:
					game.set_alive(i, false);
					game.set_just_born(i, false);
					game.set_dead(i, true);
					game.set_dying(i, false);
					break;
				case 3:
					game.set_alive(i, false);
					game.set_just_born(i, false);
					game.set_dead(i, true);
					game.set_dying(i, false);
					break;
				default:
					break;
				}
			}
		}
		background();
		birth(game);
		to_live(game);
		to_die(game);

		if (clock.getElapsedTime().asSeconds() >= 2)
		{
			set_red();
			set_blue();
			set_green();
			game.next_generation();
			clock.restart();
		}
	}


}