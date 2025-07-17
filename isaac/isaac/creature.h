#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class creature : public object {
public:
	using object::object;

	void move_up() { pos_x--; }
	void move_down() { pos_x++; };
	void move_left() { pos_y--; };
	void move_right() { pos_y++; };
};

#endif //CREATURE_H