#pragma once
#include <vector>
using namespace std;
class game_of_life
{
private:
	vector<bool> alive;
	vector<bool> dead;
	vector<bool> just_born;
	vector<bool> dying;
public:
	game_of_life();
	bool get_alive(int i);
	bool get_just_born(int i);
	bool get_dead(int i);
	bool get_dying(int i);
	void set_alive(int i, bool b);
	void set_just_born(int i, bool b);
	void set_dead(int i, bool b);
	void set_dying(int i, bool b);
	int count_neigbours(int i);
	void next_generation();
};

