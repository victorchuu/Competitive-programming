#include <iostream>
#include <vector>

using namespace std;

int inf = 1147483647;

int min(int a, int b, int c) {
	if (a < b && a < c)
		return a;
	if (b < a && b < c)
		return b;
	return c;
}

int main() {
	int ncasos;
	cin >> ncasos;
	int n;
	while (ncasos--) {
		cin >> n;
		n = n / 100;
		vector<vector<int>> m(10,vector<int>(n));
		for (int i = 9; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				cin >> m[i][j];
			}
		}
		vector<vector<int>> M(10, vector<int>(n+1,inf));
		M[0][n] = 0;



		for (int j = n - 1; j >= 0; j--) {
			for (int i = 0; i < 10; i++) {

				int op1 = inf, op2 = inf, op3 = inf;
				if (i < 9)
					op1 = M[i + 1][j + 1] + 60 - m[i][j];
				if (i > 0)
					op3 = M[i - 1][j + 1] + 20 - m[i][j];
				op2 = M[i][j + 1] + 30 - m[i][j];

				M[i][j] = min(op1, op2, op3);


			}
		}
		cout << M[0][0] << '\n' << '\n';
		
	}

	return 0;
}