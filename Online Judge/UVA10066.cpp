#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	
	int n, m;
	cin >> n >> m;
	int caso = 1;
	while (n != 0 || m != 0) {
		vector<int> A(n);
		vector<int> B(m);
		for (int i = 0; i < n ; i++)
			cin >> A[i];
		for (int i = 0; i < m; i++)
			cin >> B[i];

		vector<vector<int>> M(n+1, vector<int>(m+1,0));

		for (int i = n-1; i >= 0; i--) {
			for (int j = m-1; j >= 0; j--) {
				if (A[i] == B[j]) {
					M[i][j] = 1 + M[i + 1][j + 1];
				}
				else {
					M[i][j] = max(M[i+1][j], M[i][j+1]);
				}
			}
		}
		cout << "Twin Towers #" << caso++;
		cout << '\n' << "Number of Tiles : " << M[0][0] << '\n' << '\n';

		cin >> n >> m;

	}


	return 0;
}