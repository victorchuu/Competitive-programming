#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dist(int a, int b) {
	return (a - b >= 0 ? a - b : b - a);
}

int main() {
	int N;
	cin >> N;
	while (N != 0) {
		vector<int> people(N);
		vector<int> skis(N);
		for (int i = 0; i < N; i++)
			cin >> people[i];
		for (int i = 0; i < N; i++)
			cin >> skis[i];
		sort(people.begin(), people.end());
		sort(skis.begin(), skis.end());
		int sum = 0;
		for (int i = 0; i < N; i++) {
			sum += dist(people[i], skis[i]);
		}
		cout << sum << '\n';
		cin >> N;
	}
}