#include <iostream>
#include<vector>
#include<unordered_set>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;

void solve(string& a, string& b) {
	int llevada = 0, contador = 0;
	a = "0" + a; b = "0" + b;
	int A = a.size()-1, B = b.size()-1;
	int i = 0; 
	while (i <= A && i <= B) {
		if (a[A-i] + b[B-i] - '0' - '0' + llevada >= 10) {
			llevada = 1;
			contador++;
		}
		else
			llevada = 0;
		i++;
	}
	cout << contador << '\n';
}

int main() {

	/*ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());//*/

	string a, b;
	cin >> a >> b;
	while (a != "0" || b != "0") {
		solve(a, b);
		cin >> a >> b;
	}

	//cin.rdbuf(cinbuf);
}