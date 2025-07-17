#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"

class enemy : public creature {
public:
	using creature::creature;
	virtual char type() { return '&'; }
};

#endif //ENEMY_H