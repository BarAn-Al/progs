#include <iostream>
#include <utility>
#include <ctime>
#include <set>
#include <queue>
#include <utility>
#include <cmath>
#include <conio.h>
#include "field.h"
#include "character.h"
#include "enemy.h"
#include "rock.h"

const int length = 11;
const int width = 11;
long long score = 0;
bool game_over = false;
std::set <enemy> enemies;
std::vector <rock> rocks;

void make_map(const field& f, std::vector <std::vector <bool>>& used) {
	std::queue <std::pair <int, int>> bfs;
	bfs.push({ length / 2, 1 });
	used[length / 2][1] = true;
	while (bfs.size()) {
		int x = bfs.front().first;
		int y = bfs.front().second;
		bfs.pop();

		if (f.is_free(x - 1, y) && !used[x - 1][y]) {
			bfs.push({ x - 1, y });
			used[x - 1][y] = true;
		}
		if (f.is_free(x + 1, y) && !used[x + 1][y]) {
			bfs.push({ x + 1, y });
			used[x + 1][y] = true;
		}
		if (f.is_free(x, y - 1) && !used[x][y - 1]) {
			bfs.push({ x, y - 1 });
			used[x][y - 1] = true;
		}
		if (f.is_free(x, y + 1) && !used[x][y + 1]) {
			bfs.push({ x, y + 1 });
			used[x][y + 1] = true;
		}
	}
}

bool check_connectivity(const field& f) {
	std::vector <std::vector <bool>> used(length, std::vector <bool>(width));
	make_map(f, used);
	return used[length / 2][width - 2];
}

void level_init(field& f, character& isaac) {
	f.clear();
	f.create_level();
	f.change(new character(&isaac));

	int rocks_amount = rand() % ((length - 2) * (width - 2) / 5);
	rocks.reserve(rocks_amount);

	int cnt = 0;
	while (cnt < rocks_amount) {
		int x = rand() % (length - 2) + 1;
		int y = rand() % (width - 2) + 1;

		if (f.is_free(x, y)) {
			f.change(new rock(x, y));
			if (!check_connectivity(f)) {
				f.del(x, y);
			}
			else {
				cnt++;
				rocks.push_back(new rock(x, y));
			}
		}
	}

	std::vector <std::vector <bool>> used(length, std::vector <bool>(width));
	make_map(f, used);
	int max_enemy_amount = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (abs(i - length / 2) + abs(j - 1) < 4) {
				used[i][j] = false;
			}
			max_enemy_amount += used[i][j];
		}
	}

	int enemies_amount = rand() % (max_enemy_amount / 4);
	for (int i = 0; i < enemies_amount; i++) {
		int x = rand() % (length - 2) + 1;
		int y = rand() % (width - 2) + 1;

		if (used[x][y]) {
			enemies.insert(enemy(x, y));
			f.change(new enemy(x, y));
			used[x][y] = false;
		}
	}
}

void character_move(character& isaac, field& f) {
	char c = _getch();
	character copy(isaac);

	switch (c) {
	case 'w':
		copy.move_up();
		break;

	case 'a':
		copy.move_left();
		break;

	case 's':
		copy.move_down();
		break;

	case 'd':
		copy.move_right();
		break;
	}

	if (f.is_free(copy.pos_x, copy.pos_y)) {
		isaac = copy;
	}
	else {
		auto it = enemies.find(enemy(copy.pos_x, copy.pos_y));
		if (it != enemies.end()) {
			enemies.erase(it);
			score += 1000;
		}
	}

}

enum {UP, DOWN, LEFT, RIGHT};

void enemies_move(character& isaac, field& f) {
	std::queue <std::pair <int, int>> bfs;
	std::vector <std::vector <bool>> used(length, std::vector <bool>(width));
	bfs.push({ isaac.pos_x, isaac.pos_y });
	used[isaac.pos_x][isaac.pos_y] = true;

	while (bfs.size()) {
		int x = bfs.front().first;
		int y = bfs.front().second;
		bfs.pop();

		bool cnt[4]{};
		int direct = 0;
		for (int i = 0; i < 4; i++) {
			direct = rand() % 4;
			while (cnt[direct]) {
				direct = (direct + 1) % 4;
			}
			cnt[direct] = true;

			switch (direct) {
			case UP:
				if (!used[x - 1][y] && f.get_object(x - 1, y) != '#') {
					bfs.push({ x - 1, y });

					auto it = enemies.find(enemy(x - 1, y));
					if (it != enemies.end() && enemies.find(enemy(x, y)) == enemies.end()) {
						enemies.erase(it);
						enemies.insert(enemy(x, y));
					}
				}

				used[x - 1][y] = true;
				break;
			case DOWN:
				if (!used[x + 1][y] && f.get_object(x + 1, y) != '#') {
					bfs.push({ x + 1, y });

					auto it = enemies.find(enemy(x + 1, y));
					if (it != enemies.end() && enemies.find(enemy(x, y)) == enemies.end()) {
						enemies.erase(it);
						enemies.insert(enemy(x, y));
					}
				}

				used[x + 1][y] = true;
				break;
			case LEFT:
				if (!used[x][y - 1] && f.get_object(x, y - 1) != '#') {
					bfs.push({ x, y - 1 });

					auto it = enemies.find(enemy(x, y - 1));
					if (it != enemies.end() && enemies.find(enemy(x, y)) == enemies.end()) {
						enemies.erase(it);
						enemies.insert(enemy(x, y));
					}
				}

				used[x][y - 1] = true;
				break;
			case RIGHT:
				if (!used[x][y + 1] && f.get_object(x, y + 1) != '#') {
					bfs.push({ x, y + 1 });

					auto it = enemies.find(enemy(x, y + 1));
					if (it != enemies.end() && enemies.find(enemy(x, y)) == enemies.end()) {
						enemies.erase(it);
						enemies.insert(enemy(x, y));
					}
				}

				used[x][y + 1] = true;
				break;
			}
		}
	}
}

int main() {
	srand(time(0));
	
	while (!game_over) {
		field f(length, width);
		character isaac(length / 2, 1);
		enemies.clear();
		rocks.clear();
		level_init(f, isaac);
		f.draw();

		while (!game_over && isaac != character(length / 2, width - 1)) {
			character_move(isaac, f);
			if (enemies.size()) {
				enemies_move(isaac, f);
			}

			if (enemies.find(enemy(isaac.pos_x, isaac.pos_y)) != enemies.end()) {
				game_over = true;
			}
			else {
				f.clear();
				f.create_level();
				f.change(new character(isaac));
				for (auto i : rocks) {
					f.change(new rock(i));
				}
				for (auto i : enemies) {
					f.change(new enemy(i));
				}
				if (enemies.empty()) {
					f.create_door();
				}
				system("cls");
				f.draw();
			}
		}
		if (!game_over) {
			score += 2500;
		}
		system("cls");
	}
	std::cout << "your score is " << score;

	return 0;
}