#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <list>
#include "object.h"
#include "rock.h"

class field {
	int length = 0;
	int width = 0;
	std::vector <std::vector <object*>> things;

public:
	field(int, int);
	~field();
	void change(object*);
	void del(int, int);
	bool is_free(int, int) const;
	char get_object(int, int) const;
	void clear();
	void create_level();
	void create_door();
	void draw() const;
};

#endif //FIELD_H