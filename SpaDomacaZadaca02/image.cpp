#include "image.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265

using namespace std;

sf::ConvexShape Star(double t, int outerRadius, int innerRadius, sf::Color color, int points, int xCenter, int yCenter) {
	sf::ConvexShape star;
	star.setPointCount(points*2);
	star.setFillColor(color);
	int distance;
	for (int i = 0; i < points*2; i++)
	{
		if (i%2 == 0)
		{
			distance = outerRadius;
		}
		else
		{
			distance = innerRadius;
		}

		star.setPoint(i, sf::Vector2f(xCenter + distance*cos(2*PI*i/points/2 + t * PI * 2) - distance*sin(2*PI*i/points/2 + t*2*PI) , yCenter + distance * cos(2 * PI * i / points / 2 + t*PI *2) + distance * sin(2 * PI * i / points / 2 + t * PI * 2) + 40 * sin(PI * t)));


	}

	return star;
}

sf::CircleShape Bubble(double t, int maxRadius, sf::Color color, int xPosition, int yPosition, double frequency, int xVelocity, int yVelocity, double phase)
{
	sf::CircleShape bubble;
	t = t + phase;
	maxRadius = maxRadius / 2;
	double t_ = 2 *  (t - (int)t) ;
		if (t_ <= 1)
		{
			bubble.setFillColor(sf::Color(color));
			bubble.setPosition(xPosition - maxRadius * t_ + t_ * xVelocity, yPosition - maxRadius * t_ + yVelocity);
			bubble.setRadius(maxRadius * t_);
			 

		}
		else
		{
			bubble.setPosition(xPosition - 2*maxRadius * (t_ - 1) + t_ * xVelocity, yPosition - 2*maxRadius * (t_ - 1) + t_ * yVelocity);
			bubble.setRadius(2*maxRadius * (t_ - 1));
			bubble.setFillColor(sf::Color::Transparent);
			bubble.setOutlineColor(sf::Color(color));
			bubble.setOutlineThickness(maxRadius - maxRadius * (t_ - 1));
		}
		
	
	return bubble;
}


image::image(sf::RenderWindow* window)
{
	this->window = window;
}

void image::set_red(double red)
{
	r = red;
}
void image::set_green(double green)
{
	g = green;
}
void image::set_blue(double blue)
{
	b = blue;
}

void image::random_color()
{
	switch (rand() % 12)
	{
	case 0:
		set_red(255);
		set_green(0);
		set_blue(0);
		break;
	case 1:
		set_red(255);
		set_green(128);
		set_blue(0);
		break;
	case 2:
		set_red(255);
		set_green(255);
		set_blue(0);
		break;
	case 3:
		set_red(128);
		set_green(255);
		set_blue(0);
		break;
	case 4:
		set_red(0);
		set_green(255);
		set_blue(0);
		break;
	case 5:
		set_red(0);
		set_green(255);
		set_blue(128);
		break;
	case 6:
		set_red(0);
		set_green(255);
		set_blue(255);
		break;
	case 7:
		set_red(0);
		set_green(128);
		set_blue(255);
		break;
	case 8:
		set_red(0);
		set_green(0);
		set_blue(255);
		break;
	case 9:
		set_red(127);
		set_green(0);
		set_blue(255);
		break;
	case 10:
		set_red(255);
		set_green(0);
		set_blue(255);
		break;
	case 11:
		set_red(255);
		set_green(0);
		set_blue(127);
		break;

	default:
		break;
	}
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
	sf::Color front;
	sf::Color background;
	if (game_started)
	{
		front = sf::Color::White;
		background = sf::Color::Black;
	}
	else
	{
		front = sf::Color::Black;
		background = sf::Color::White;
	}
	sf::RectangleShape menuBackground;
	menuBackground.setFillColor(background);
	menuBackground.setSize(sf::Vector2f(1600, 1000));
	window->draw(menuBackground);


	sf::Font font;
	if (!font.loadFromFile("OpenSans.ttf"))
	{
		// error...
	}
	sf::Text text;
	
	
	
	int c = 0;

	
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color(front));
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
				text.setString("Continue");
				window->draw(text);
			}
			text.setString("Continue");
			break;
		case 2:
			if (get_num()!=4)
			{
				text.setFillColor(sf::Color(front));
				text.setString("Options");
			}
			if (get_num() == 4)
			{
				text.setFillColor(sf::Color(front));
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
			text.setFillColor(sf::Color(front));
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
		text.setString("Continue");
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
	
	if (game_started)
	{
		sf::Color bubbleColor;
		for (int i = 0; i < 25; i++)
		{
			switch (i%3)
			{
			case 0:
				bubbleColor = sf::Color::Yellow;
				break;
			case 1:
				bubbleColor = sf::Color::Cyan;
				break;
			case 2:
				bubbleColor = sf::Color::Magenta;
				break;
			default:
				break;
			}
			window->draw(Bubble(t, 50, sf::Color(bubbleColor), 800, 500, 0.5, -350, 100 * sin(t + i), i / 10.0));
		}
	}
	else
	{
		for (int i = 0; i < 25; i++)
		{
			window->draw(Bubble(t, 50, sf::Color(front), 800, 500, 0.5, -350, 100 * sin(t + i), i / 10.0));
		}
	}
	if (game_started)
	{
		window->draw(Star(t, 100, 50, sf::Color(r + (255-r)*abs(sin(PI / 2 * t)), g + (255 - g) * abs(sin(PI / 2 * t)), b + (255 - b) * abs(sin(PI / 2 * t))), 5, 800, 500));
	}
	else
	{
		window->draw(Star(t, 100, 50, sf::Color(front), 5, 800, 500));
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

	sf::CircleShape outerCircle;
	outerCircle.setRadius(25);
	outerCircle.setFillColor(sf::Color(255, 255 * f2, 0));
	outerCircle.setOutlineThickness(5.f);
	outerCircle.setOutlineColor(sf::Color(255, 255 * f2, 0));
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_alive(c) && !game.get_just_born(c))
			{
				outerCircle.setPosition((50 + 200 * j) / 2 + f5, (50 + 200 * i) / 2 + f6);
				window->draw(outerCircle);
			}
			c++;
		}

	}

	int l;
	double f3;
	double f4;
	sf::ConvexShape Star;
	c = 0;
	int d = 0;
	Star.setPointCount(4);
	Star.setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
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
					
					Star.setPoint(0, sf::Vector2f((100 + 200 * j) / 2 + f5, (100 + 200 * i) / 2 + f6));
					Star.setPoint(1, sf::Vector2f((25 * f3 + (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (90 - 100 + l) * f3 + (100 + 200 * i)) / 2 + f6));
					Star.setPoint(2, sf::Vector2f(((50 - 2 * l) * f3 + (100 + 200 * j)) / 2 + f5, ((150 - 100 - 2 * l) * f4 + (100 + 200 * i)) / 2 + f6));
					Star.setPoint(3, sf::Vector2f((25 * f3 - (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (110 - 100 - l) * f3 + (100 + 200 * i)) / 2 + f6));

					window->draw(Star);

				}
				d++;
			}
			c++;
		}
	}

	sf::CircleShape innerCircle;
	innerCircle.setRadius(5);
	innerCircle.setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
	innerCircle.setOutlineThickness(2.5);
	innerCircle.setOutlineColor(sf::Color(255, 255 * f2, 0));
	c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (game.get_alive(c) && !game.get_just_born(c))
			{
	
				innerCircle.setPosition((90 + 200 * j) / 2 + f5, (90 + 200 * i) / 2 + f6);

				window->draw(innerCircle);
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
	sf::CircleShape outerCircle;
	outerCircle.setRadius(50 * f1 / 2);
	outerCircle.setFillColor(sf::Color(255 * f2, 0, 0));
	outerCircle.setOutlineThickness(2.5);
	outerCircle.setOutlineColor(sf::Color(255 * f2, 0, 0));
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_dying(c))
			{
				
				outerCircle.setPosition((100 - 50 * f1 + 200 * j) / 2 + f5, (100 - 50 * f1 + 200 * i) / 2 + f6);
				
				window->draw(outerCircle);
			}
			c++;
		}

	}
	c = 0;
	int d = 0;
	sf::ConvexShape Star;
	Star.setPointCount(4);
	Star.setFillColor(sf::Color(255 * f3, 255 * f3, 255 * f3));
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
					Star.setPoint(0, sf::Vector2f((100 + 200 * j) / 2 + f5, (100 + 200 * i) / 2 + f6));
					Star.setPoint(1, sf::Vector2f(((125 - 100 - f0 * 25) * cos(PI / 4 * k + PI * 4 * f0) - (90 - 100 + l) * sin(PI / 4 * k + PI * 4 * f0) + (100 + 200 * j)) / 2 + f5, ((125 - 100 - f0 * 25) * sin(PI / 4 * k + PI * 4 * f0) + (90 - 100 + l) * cos(PI / 4 * k + PI * 4 * f0) + (100 + 200 * i)) / 2 + f6));
					Star.setPoint(2, sf::Vector2f(((150 - 100 - 2 * l - f0 * 25) * cos(PI / 4 * k + PI * 4 * f0) + (100 + 200 * j)) / 2 + f5, ((150 - 100 - 2 * l - f0 * 25) * sin(PI / 4 * k + PI * 4 * f0) + (100 + 200 * i)) / 2 + f6));
					Star.setPoint(3, sf::Vector2f(((125 - 100 - f0 * 25) * cos(PI / 4 * k + PI * 4 * f0) - (110 - 100 - l) * sin(PI / 4 * k + PI * 4 * f0) + (100 + 200 * j)) / 2 + f5, ((125 - 100 - f0 * 25) * sin(PI / 4 * k + PI * 4 * f0) + (110 - 100 - l) * cos(PI / 4 * k + PI * 4 * f0) + (100 + 200 * i)) / 2 + f6));
					window->draw(Star);
				}
				d++;
			}
			c++;

		}
	}

	sf::CircleShape innerCircle;
	innerCircle.setFillColor(sf::Color(255 * f3, 255 * f3, 255 * f3));
	innerCircle.setOutlineThickness(2.5);
	innerCircle.setOutlineColor(sf::Color(255 * f3, 255 * f3, 0));
	innerCircle.setRadius(5);
	c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (game.get_dying(c))
			{
	
				innerCircle.setPosition((90 + 200 * j) / 2 + f5, (90 + 200 * i) / 2 + f6);

				window->draw(innerCircle);
			}
			c++;
		}

	}

}




void image::birth(game_of_life& game)
{

	double t = clock.getElapsedTime().asSeconds();
	double f1 = sin(PI * 0.03125 * pow(4, t)); //transition 0>1, accelerated
	double f2 = abs(sin(PI / 2 * t)); //transition 0>1
	double f5 = 80 * sin(PI * t) * get_moving(); //rotation around x-coordinate
	double f6 = 60 * sin(2 * PI * t) * get_moving(); //rotation around y-coordinate

	sf::CircleShape outerCircle;
	outerCircle.setRadius(25 * f1);
	outerCircle.setFillColor(sf::Color(255, 255 * f2, 0));
	outerCircle.setOutlineThickness(5.f);
	outerCircle.setOutlineColor(sf::Color(255, 255 * f2, 0));

	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_just_born(c))
			{

			
				outerCircle.setPosition((100 - 50 * f1 + 200 * j) / 2 + f5, (100 - 50 * f1 + 200 * i) / 2 + f6);
				
				window->draw(outerCircle);
			}
			c++;
		}

	}
	c = 0;
	int d = 0;
	int l;
	double f3;
	double f4;
	sf::ConvexShape Star;
	Star.setPointCount(4);
	Star.setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));

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

					Star.setPoint(0, sf::Vector2f((100 + 200 * j) / 2 + f5, (100 + 200 * i) / 2 + f6));
					Star.setPoint(1, sf::Vector2f((25 * f3 + (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (90 - 100 + l) * f3 + (100 + 200 * i)) / 2 + f6));
					Star.setPoint(2, sf::Vector2f(((50 - 2 * l) * f3 + (100 + 200 * j)) / 2 + f5, ((150 - 100 - 2 * l) * f4 + (100 + 200 * i)) / 2 + f6));
					Star.setPoint(3, sf::Vector2f((25 * f3 - (10 - l) * f4 + (100 + 200 * j)) / 2 + f5, ((125 - 100) * f4 + (110 - 100 - l) * f3 + (100 + 200 * i)) / 2 + f6));

					window->draw(Star);
				}
				d++;
			}
			c++;
		}
	}

	sf::CircleShape innerCircle;
	innerCircle.setFillColor(sf::Color(255 * f2, 255 * f2, 255 * f2));
	innerCircle.setOutlineThickness(2.5);
	innerCircle.setOutlineColor(sf::Color(255, 255 * f2, 0));
	innerCircle.setRadius(5);
	c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (game.get_just_born(c))
			{
				innerCircle.setPosition((90 + 200 * j) / 2 + f5, (90 + 200 * i) / 2 + f6);

				window->draw(innerCircle);
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
			random_color();
			game.next_generation();
			clock.restart();
		}
	}


}