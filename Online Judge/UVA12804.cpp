#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vector<int>>;

vvi grafo; vi estado; int V;
int const NO_VISTO = 0, TOCADO = 1, HUNDIDO = 2;
bool dfs(int u) {
	estado[u] = TOCADO;
	bool b = false;
	for (int i = 0; i < grafo[u].size(); ++i) {
		int v = grafo[u][i];
		if (estado[v] == TOCADO)
			b = true;
		else if ((estado[v] == NO_VISTO) && dfs(v))
			b = true;
	}
	estado[u] = HUNDIDO;
	return b;
}

int main() {

	int casos; char c; int N;
	cin >> casos;
	while (casos--) {
		cin >> V;
		grafo = vvi(V+1);
		estado = vi(V + 1,NO_VISTO);
		for (int i = 0; i < V; i++) {
			cin >> c;
			switch (c) {
			case 'A': grafo[i].push_back(i + 1); break;
			case 'J': cin >> N; grafo[i].push_back(N-1); break;
			default: cin >> N; grafo[i].push_back(N-1); grafo[i].push_back(i + 1);
			}
		}
		bool ciclos = dfs(0);
		if (ciclos) {
			if (estado[V] == NO_VISTO)
				cout << "NEVER\n";
			else
				cout << "SOMETIMES\n";
		}
		else
			cout << "ALWAYS\n";
	}
}