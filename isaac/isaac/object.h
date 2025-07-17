#ifndef OBJECT_H
#define OBJECT_H

class object {
public:
	int pos_x = 0;
	int pos_y = 0;

	object() = default;
	object(int a, int b) : pos_x(a), pos_y(b) {};
	object(object* other) : pos_x(other->pos_x), pos_y(other->pos_y) {};
	virtual char type() { return '.'; }

	bool operator <(object other) const {
		if (pos_x < other.pos_x) {
			return true;
		}
		else if (pos_x == other.pos_x && pos_y < other.pos_y) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator >=(object other) const {
		return !(*this < other);
	}

	bool operator ==(object other) const {
		return pos_x == other.pos_x && pos_y == other.pos_y;
	}

	bool operator !=(object other) const {
		return !(*this == other);
	}

	bool operator >(object other) const {
		return (*this >= other) && (*this != other);
	}

	bool operator <=(object other) const {
		return !(*this > other);
	}
};

#endif //OBJECT_H