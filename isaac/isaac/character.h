#ifndef CHARACTER_H
#define CHARACTER_H

#include "creature.h"

class character : public creature {
public:
	using creature::creature;
	virtual char type() { return '@'; }
};

#endif //CHARACTER_H