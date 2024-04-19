#include <iostream>
#include <ctime>
#include <fstream>

int main() {
	std::cout << "Enter amount of numbers: ";
	int n;
	std::cin >> n;
	srand(time(0));

	std::cout << "Enter range of numbers: ";
	long long l, r;
	std::cin >> l >> r;

	std::ofstream fout("test10.txt");
	bool* used = new bool[r - l + 1];
	for (int i = 0; i < r - l + 1; i++) {
		used[i] = false;
	}
	for (int i = 0; i < n; i++) {
		int a = 0;
		do {
			a = rand() % (r - l + 1) + l;
		} while (used[a - l] == true);
		used[a - l] = true;

		fout << a << ' ';
	}
}