#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dist(int a, int b) {
	return (a - b >= 0 ? a - b : b - a);
}

int main() {
	string S;
	cin >> S;
	while (cin) {
		int max = 1, next, sum;
		for (int i = 0; i < S.size(); i++) {
			for (int j = S.size() - 1; j > i; j--) {
				if (S[i] == S[j]) {
					next = -1;
					int a = i, b = j;
					while (a < b && S[a++] == S[b--]) {
						if (next < 0 && S[b] == S[j]) next = b;
					}
					max = ( b <= a && j - i + 1 > max ? j - i + 1 : max);
					j = (next > b ? next : b);
				}
			}
		}
		cout << max << '\n';


		cin >> S;
	}
}