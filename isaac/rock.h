#ifndef ROCK_H
#define ROCK_H

#include "object.h"

class rock : public object {
public:
	using object::object;
	virtual char type() { return '#'; }
};

#endif //ROCK_H