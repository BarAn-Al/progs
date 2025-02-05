#ifndef OBJECT_H
#define OBJECT_H

class object {
private:
	int x;
	int y;

public:
	object(const int& a, const int& b) : x(a), y(b) {}
	object(const object& other) : x(other.x), y(other.y) {}

	int& get_x() {
		return x;
	}

	int& get_y() {
		return y;
	}

};

#endif //OBJECT_H