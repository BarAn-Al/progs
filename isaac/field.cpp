#include "field.h"
#include "rock.h"
#include <algorithm>
#include <iostream>

field::field(int l, int w) : length(l), width(w) {
	things.resize(l, std::vector <object*>(w));
	clear();
}

field::~field() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			delete things[i][j];
		}
	}
}

void field::change(object* a) {
	delete things[a->pos_x][a->pos_y];
	things[a->pos_x][a->pos_y] = a;
}

void field::del(int x, int y) {
	delete things[x][y];
	things[x][y] = new object(x, y);
}

void field::clear() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			delete things[i][j];
			things[i][j] = new object(i, j);
		}
	}
}

void field::create_level() {
	for (int i = 0; i < length; i++) {
		delete things[i][0];
		things[i][0] = new rock(i, 0);
		delete things[i][width - 1];
		things[i][width - 1] = new rock(i, width - 1);
	}

	for (int j = 0; j < width; j++) {
		delete things[0][j];
		things[0][j] = new rock(0, j);
		delete things[length - 1][j];
		things[length - 1][j] = new rock(length - 1, j);
	}
}

void field::create_door() {
	del(length / 2, width - 1);
}

void field::draw() const {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << things[i][j]->type();
		}
		std::cout << '\n';
	}
}

bool field::is_free(int x, int y) const {
	return get_object(x, y) == '.';
}

char field::get_object(int x, int y) const {
	return things[x][y]->type();
}