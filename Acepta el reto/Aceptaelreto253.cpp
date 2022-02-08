#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int N, K, E, S;
	cin >> N >> K >> E >> S;
	while (N != 0) {
		vector<int> tabla(N*N + 1, 0);
		//0 : no visitado
		// x > 0 : escalera o serpiente hacia x
		//-1 : visitado
		int a, b;
		for (int i = 0; i < E + S;  i++) {
			cin >> a >> b;
			tabla[a] = b;
		}
		int pasos = -1, libre;
		queue<pair<int,int>> cola;
		cola.push({ 1,0 });
		while (!cola.empty()) {
			pair<int,int> u = cola.front(); cola.pop();
			
			libre = -1;
			for (int i = 1; i <= K; i++) {
				int v = u.first + i;
				if (v == N * N) {
					pasos = u.second+1;
					break;
				}
				if (tabla[v] == 0) {
					tabla[v] = -1;
					libre = v;
				}
				else if (tabla[v] > 0) {
					if (tabla[tabla[v]] == 0) {
						cola.push({ tabla[v],u.second + 1 });
						tabla[tabla[v]] = -1;
					}
				}
			}
			if (pasos >= 0) {
				cout << pasos << '\n';
				break;
			}
			if (libre > 0) cola.push({ libre,u.second + 1 });

		}
		cin >> N >> K >> E >> S;
	}
}