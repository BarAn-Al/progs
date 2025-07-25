#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <ctime>
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	vector <string> words;
	vector <vector <string>> correctAnswers;

	ifstream fin("verbs.txt");

	string word;
	while (fin >> word) {
		words.push_back(word);

		string firstF, secondF, thirdF;
		fin >> firstF >> secondF >> thirdF;
		correctAnswers.push_back({ firstF, secondF, thirdF });
	}

	bool wantToContinue = true;
	bool firstTime = true;
	while (wantToContinue) {
		int sumOfCA = 0;
		vector <bool> used(words.size());

		while (sumOfCA < used.size()) {
			int a = rand() % used.size();
			while (used[a]) {
				a = rand() % used.size();
			}

			if (firstTime) {
				cout << "������ ������, ������ � ������ ����� ������� �������������� ����� ������ ��� Enter\n";
				firstTime = false;
			}
			cout << words[a] << '\n';

			string ans[3];
			for (int i = 0; i < 3; i++) {
				cin >> ans[i];
			}

			for (int i = 0; i < 3; i++) {
				if (ans[i] != correctAnswers[a][i]) {
					cout << "� ��������� �����:\n";
					for (int i = 0; i < 3; i++) {
						cout << correctAnswers[a][i] << ' ';
					}
					goto INCORRECT;
				}
			}

			cout << "�����";
			used[a] = true;
			sumOfCA++;

		INCORRECT:
			cout << '\n';
		}
		cout << "������!\n � ������ ������ ����� �����, ����� ������ ��-����� ��� ������ 0, ����� ���������\n";

		int a;
		cin >> a;
		if (!a) {
			wantToContinue = false;
			cout << "�� �����\n";
		}
	}




	return 0;
}