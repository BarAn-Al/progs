#include <iostream>
#include <conio.h>
#include <ctime>
#include <utility>
#include <string>
#include <cmath>
#include "functions.h"
#include <queue>
#include <vector>

using namespace std;

const int width = 11;        //  |
const int length = 11;		 // ---
const int start_y = width / 2;
const int start_x = 1;
const int end_y = width / 2;
const int end_x = length - 1;
const enum moves { UP = 'w', RIGHT = 'd', DOWN = 's', LEFT = 'a' };
const enum hits { HIT_UP = 'i', HIT_DOWN = 'k', HIT_LEFT = 'j', HIT_RIGHT = 'l' };

vector <pair <int, int>> enemies;
vector <pair <int, int>> rocks;
pair <int, int> isaac = { start_y, start_x }; //координаты в формате (y, x)
pair <int, int> end_of_level = { end_y, end_x };
int score = 0;
string field;

bool game_is_over = false;

bool Field_conect(int y, int x) {
	bool used[length][width];
	used[isaac.first][isaac.second] == true;
	queue <pair <int, int>> bfs;
	bfs.push({ isaac.first, isaac.second });

	while (bfs.size()) {
		pair <int, int> f = bfs.front();

		if (f.first == y && f.second == x) {
			bfs.pop();
			continue;
		}

		if (!used[f.first - 1][f.second] && !Is_rock(f.first - 1, f.second)) {
			used[f.first - 1][f.second] = true;
			bfs.push({ f.first - 1, f.second });
		}
		if (!used[f.first + 1][f.second] && !Is_rock(f.first + 1, f.second)) {
			used[f.first + 1][f.second] = true;
			bfs.push({ f.first + 1, f.second });
		}
		if (!used[f.first][f.second - 1] && !Is_rock(f.first, f.second - 1)) {
			used[f.first][f.second - 1] = true;
			bfs.push({ f.first, f.second - 1 });
		}
		if (!used[f.first][f.second + 1] && !Is_rock(f.first, f.second + 1)) {
			used[f.first][f.second + 1] = true;
			bfs.push({ f.first, f.second + 1 });
		}

		bfs.pop();
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (!used[enemies[i].first][enemies[i].second]) {
			return false;
		}
	}

	if (used[end_of_level.first][end_of_level.second - 1]) {
		return true;
	}
	else {
		return false;
	}
}

bool Is_rock(int i, int j) {
	for (int k = 0; k < rocks.size(); k++) {
		if (i == rocks[k].first && j == rocks[k].second) {
			return true;
		}
	}
	return false;
}

pair <bool, int> Is_enemy(int i, int j) {
	for (int k = 0; k < enemies.size(); k++) {
		if (enemies[k].first == i && enemies[k].second == j) {
			return { true, k };
		}
	}
	return { false, false };
}

void Generate_enemy() {

	int x = 2;
	int y = width / 2;

	while (Is_rock(y, x) || abs(x - isaac.second) + abs(y - isaac.first) < 3) {
		x = rand() % (length - 2) + 1;
		y = rand() % (width - 2) + 1;
	}

	enemies.push_back({ y, x });
}

void Generate_walls() {
	rocks.push_back({ end_of_level.first, end_of_level.second });

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			if (i == end_of_level.first && j == end_of_level.second) {
				continue;
			}

			if (i == 0 || j == 0 || j == length - 1 || i == width - 1) {
				rocks.push_back({ i, j });
			}
		}
	}
}

void Generate_rock() {
	int y = 0;
	int x = 0;

	while (Is_rock(y, x) || Is_enemy(y, x).first || !Field_conect(y, x) || (y == isaac.first && x == isaac.second)) {
		y = rand() % (width - 2) + 1;
		x = rand() % (length - 2) + 1;
	}

	rocks.push_back({ y, x });
}

void Generate_field() {
	isaac = { start_y, start_x };
	enemies = {};
	rocks = {};

	Generate_walls();
	for (int i = 0; i < rand() % 10; i++) {
		Generate_enemy();
	}

	for (int i = 0; i < rand() % 41; i++) {
		Generate_rock();
	}
}

void Draw_field() {
	string s;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			if (Is_rock(i, j)) {
				s += '#';
			}
			else if (i == isaac.first && j == isaac.second) {
				s += 'A';
			}
			else if (Is_enemy(i, j).first) {
				s += 'E';
			}
			else {
				s += '.';
			}

		}
		s += '\n';
	}

	if (!enemies.size()) {
		if (rocks[0].first == end_of_level.first && rocks[0].second == end_of_level.second) {
			rocks.erase(rocks.begin());
			s[end_of_level.first * (width + 1) + end_of_level.second] = '.';
		}
	}
	field = s;
	cout << field << "You score: " << score;
}

void Enemy_move(int num) {
	int i = enemies[num].first;
	int j = enemies[num].second;
	while (i == enemies[num].first && j == enemies[num].second) {
		switch (rand() % 4) {
		case 0:
			if (!Is_rock(i + 1, j)) {
				enemies[num].first++;
			}
			break;

		case 1:
			if (!Is_rock(i, j - 1)) {
				enemies[num].second--;
			}
			break;

		case 2:
			if (!Is_rock(i - 1, j)) {
				enemies[num].first--;
			}
			break;

		case 3:
			if (!Is_rock(i, j + 1)) {
				enemies[num].second++;
			}
			break;

		}
	}
}

void step() {
	pair <bool, int> k;
	switch (_getch()) {
	case UP:
		if (!Is_rock(isaac.first - 1, isaac.second)) {
			isaac.first--;
		}
		break;

	case DOWN:
		if (!Is_rock(isaac.first + 1, isaac.second)) {
			isaac.first++;
		}
		break;

	case LEFT:
		if (!Is_rock(isaac.first, isaac.second - 1)) {
			isaac.second--;
		}
		break;

	case RIGHT:
		if (!Is_rock(isaac.first, isaac.second + 1)) {
			isaac.second++;
		}
		break;

	case HIT_UP:
		k = Is_enemy(isaac.first - 1, isaac.second);
		if (k.first) {
			enemies.erase(enemies.begin() + k.second);
			score += 50;
		}
		break;

	case HIT_DOWN:
		k = Is_enemy(isaac.first + 1, isaac.second);
		if (k.first) {
			enemies.erase(enemies.begin() + k.second);
			score += 50;
		}
		break;

	case HIT_LEFT:
		k = Is_enemy(isaac.first, isaac.second - 1);
		if (k.first) {
			enemies.erase(enemies.begin() + k.second);
			score += 50;
		}
		break;

	case HIT_RIGHT:
		k = Is_enemy(isaac.first, isaac.second + 1);
		if (k.first) {
			score += 50;
			enemies.erase(enemies.begin() + k.second);
		}
		break;
	}

	for (int i = 0; i < enemies.size(); i++) {
		Enemy_move(i);
	}


	system("cls");
	Draw_field();

}

int main() {
	srand(time(NULL));
start:
	game_is_over = false;
	score = 0;
	Generate_field();
	Draw_field();
	while (!game_is_over) {
		step();

		if (isaac.first == end_of_level.first && isaac.second == end_of_level.second) {
			score += 100;
			Generate_field();
			system("cls");
			Draw_field();
		}

		if (Is_enemy(isaac.first, isaac.second).first) {
			game_is_over = true;
			system("cls");
		}

	}

	cout << "You lose!\nYour score: " << score;
	cout << "\nPress \"r\" for restart or \"e\" to end the game";
restart:
	char c = _getch();
	if (c == 'r') {
		system("cls");
		goto start;
	}
	else if (c == 'e') {
		return 0;
	}
	else {
		cout << "Ya tvoyu mamu...\n";
		goto restart;
	}
}