#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> map(10);
vector<int> X = { 1,0,-1,0,0 };
vector<int> Y = { 0,1,0,-1,0 };

bool inRange(int x, int y) {
	return 0 <= x && x < 10 && 0 <= y && y < 10;
}

void on_off(char&c) {
	c = (c == '#' ? 'O' : '#');
}

void press(int x, int y, vector<string> & m) {
	for (int k = 0; k < 5; k++) {
		if (inRange(x + X[k], y + Y[k]))
			on_off(m[x + X[k]][y + Y[k]]);
	}
}

int g() {
	int p = 0;
	vector<string> copia = map;
	for (int fila = 1; fila < 10; fila++) {
		for (int col = 0; col < 10; col++) {
			if (copia[fila - 1][col] == 'O') {
				press(fila, col, copia);
				p++;
			}

		}
	}
	bool ok = true;
	for (int col = 0; col < 10; col++) {
		if (copia[9][col] == 'O') ok = false;
	}
	return (ok ? p : 101);
}

int f(int i, int num) {
	if (i == 10) return g() + num;
	int a = f(i + 1,num);
	press(0, i,map);
	int b = f(i + 1,num + 1);
	press(0, i,map);
	return (a < b ? a : b);
}

int main() {
	string title;
	cin >> title;
	while (title != "end") {
		for (int i = 0; i < 10; i++) {
			cin >> map[i];
		}
		int sol = f(0, 0);
		if (sol == 101) {
			sol = -1;
		}
		cout << title << ' ' << f(0, 0) << '\n';


		cin >> title;
	}
}