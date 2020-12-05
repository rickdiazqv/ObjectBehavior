#pragma once
#include "gamedata.h"

class Clan {
private:
	string _name;
	int _know;
	int _repute;
	int _force;
	int _stusNum;

	list<Person*> students;
};

