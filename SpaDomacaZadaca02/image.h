#pragma once
#include <SFML/Graphics.hpp>
#include "game_of_life.h"

using namespace std;
class image
{
private:
    sf::RenderWindow* window;
    sf::Clock clock;
    double r = rand() % 256;
    double g = rand() % 256;
    double b = rand() % 256;
    bool moving;
    bool game_started;
    int num;

public:
    image(sf::RenderWindow* window);
    void set_red();
    void set_green();
    void set_blue();
    bool get_game_started();
    void set_game_started(bool b);
    void menu(int num);
    void set_num(int n);
    int get_num();
    bool get_moving();
    void set_moving(bool b);
    void background();
    void to_live(game_of_life& game);
    void to_die(game_of_life& game);
    void birth(game_of_life& game);
    void draw(game_of_life& game);
};


