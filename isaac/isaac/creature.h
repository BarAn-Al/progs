#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class creature : public object {
private:
	int health;

public:
	creature(const int& a, const int& b, const int& h) : object(a, b), health(h) {}
	creature(const creature& other) : object(other), health(other.health) {}


	void go_up() {
		get_x()++;
	}

	void go_down() {
		get_x()--;
	}

	void go_left() {
		get_y()--;
	}

	void go_right() {
		get_y()++;
	}
};


#endif //CREATURE_H