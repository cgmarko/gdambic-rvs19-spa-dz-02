#include "game_of_life.h"
#include <ctime>

game_of_life::game_of_life()
{
	srand(time(nullptr));
	for (int i = 0; i < 160; i++)
	{
		switch (rand() % 4)
		{
		case 0:
			alive.push_back(true);
			just_born.push_back(true);
			dead.push_back(false);
			dying.push_back(false);
			break;
		case 1:
			alive.push_back(false);
			just_born.push_back(false);
			dead.push_back(true);
			dying.push_back(false);
			break;
		case 2:
			alive.push_back(false);
			just_born.push_back(false);
			dead.push_back(true);
			dying.push_back(false);
			break;
		case 3:
			alive.push_back(false);
			just_born.push_back(false);
			dead.push_back(true);
			dying.push_back(false);
			break;
		default:
			break;
		}
	}
}

void game_of_life::new_game()
{
	srand(time(nullptr));
	game_of_life new_game;
	alive = new_game.alive;
	dead = new_game.dead;
	just_born = new_game.just_born;
	dying = new_game.dying;

}

bool game_of_life::get_alive(int i)
{
	return alive[i];
}

bool game_of_life::get_just_born(int i)
{
	return just_born[i];
}

bool game_of_life::get_dead(int i)
{
	return dead[i];
}

bool game_of_life::get_dying(int i)
{
	return dying[i];
}

void game_of_life::set_alive(int i, bool b)
{
	alive[i] = b;
}

void game_of_life::set_just_born(int i, bool b)
{
	just_born[i] = b;
}

void game_of_life::set_dead(int i, bool b)
{
	dead[i] = b;
}

void game_of_life::set_dying(int i, bool b)
{
	dying[i] = b;
}

int game_of_life::count_neigbours(int i)
{
	int counter = 0;
	if (i % 16 != 0)
	{
		if (get_alive(i - 1))
		{
			counter++;
		}
	}

	if ((i + 1)% 16)
	{
		if (get_alive(i + 1))
		{
			counter++;
		}
	}
	if (i > 15)
	{
		if (get_alive(i - 16))
		{
			counter++;
		}
	}
	if (i < 144)
	{
		if (get_alive(i + 16))
		{
			counter++;
		}
	}
	if (i > 16 && i % 16 != 0)
	{
		if (get_alive(i - 17))
		{
			counter++;
		}
	}
	if (i > 15 && (i + 1) % 16 != 0)
	{
		if (get_alive(i - 15))
		{
			counter++;
		}
	}
	if (i < 144 && i  % 16 != 0)
	{
		if (get_alive(i + 15))
		{
			counter++;
		}
	}
	if (i < 143 && (i + 1) % 16 != 0)
	{
		if (get_alive(i + 17))
		{
			counter++;
		}
	}
	return counter;
}

void game_of_life::next_generation()
{
	game_of_life next_gen;
	for (int i = 0; i < 160; i++)
	{
		switch (count_neigbours(i))
		{
		case 0:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		case 1:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		case 2:
			next_gen.set_alive(i, get_alive(i));
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, get_dead(i));
			next_gen.set_dying(i, false);
			break;
		case 3:
			if (get_dead(i))
			{
				next_gen.set_alive(i, true);
				next_gen.set_just_born(i, true);
				next_gen.set_dead(i, false);
				next_gen.set_dying(i, false);
			}
			else
			{
				next_gen.set_alive(i, true);
				next_gen.set_just_born(i, false);
				next_gen.set_dead(i, false);
				next_gen.set_dying(i, false);
			}
			break;
		case 4:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		case 5:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		case 6:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		case 7:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		case 8:
			next_gen.set_alive(i, false);
			next_gen.set_just_born(i, false);
			next_gen.set_dead(i, true);
			if (get_alive(i))
			{
				next_gen.set_dying(i, true);
			}
			else
			{
				next_gen.set_dying(i, false);
			}
			break;
		default:
			break;
		}

	}
	alive = next_gen.alive;
	dead = next_gen.dead;
	just_born = next_gen.just_born;
	dying = next_gen.dying;
}
