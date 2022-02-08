#include <iostream>
#include <string>

using namespace std;

char f(char a, char b, char c) {
	if (a == b || a == c)return a;
	if (b == c) return b;
	return 'x';
}

int main() {
	string a, b, c;
	cin >> a;
	while (cin) {
		cin >> b >> c;
		int tam = (a.size() > b.size() ? a.size() : b.size());
		tam = (tam > c.size() ? tam : c.size());
		while (a.size() < tam) {
			a = "0" + a;
		}
		while (b.size() < tam) {
			b = "0" + b;
		}
		while (c.size() < tam) {
			c = "0" + c;
		}
		for (int i = 0; i < tam; i++) {
			char p = f(a[i], b[i], c[i]);
			if (p == 'x') {
				a = "RUIDO COSMICO"; break;
			}
			a[i] = p;
		}
		cout << a << '\n';

		cin >> a;
	}

	return 0;
}