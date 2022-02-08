#include <iostream>

using namespace std;

int sqrt(unsigned long int a, unsigned long int b, unsigned long int n) {
	if (a + 1 >= b) return a;
	int mitad = (a + b) / 2;
	if (mitad * mitad > n) {
		return sqrt(a, mitad, n);
	}
	else return sqrt(mitad, b, n);
}

int sqrt(unsigned long int n) {
	int i = 1;
	while (i*i < n) {
		i *= 2;
	}
	return sqrt(i/2, i, n);
}

int main() {
	unsigned long int n;
	cin >> n;
	while (n != 0) {
		int r = sqrt(n);
		while (n % r != 0)
			r--;
		cout << n/r << '\n';
		cin >> n;
	}
	return 0;
}