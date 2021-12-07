#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int V; vvi grafo;
int hora; vi horaVertice, alcanzable;
vector<pair<int,int>> puentes;
void dfs(int u, int uParent) {
	horaVertice[u] = alcanzable[u] = hora; hora++;
	for (int i = 0; i < grafo[u].size(); ++i) {
		int v = grafo[u][i];
		if (v == uParent) continue; // BackEdge con el padre, que ignoramos
		if (horaVertice[v] == 0) { // No visitado
			dfs(v, u);
			if (alcanzable[v] >= horaVertice[u]) {
				puentes.push_back({ u,v });
			}
			alcanzable[u] = min(alcanzable[u], alcanzable[v]);
		}
		else
			alcanzable[u] = min(alcanzable[u], horaVertice[v]); // BackEdge
	}
}



int main() {

	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());

	int v, a, u; char basura;
	
	while (cin >> V) {
		grafo = vvi(V);
		for (int i = 0; i < V; i++){
			cin >> v >> basura >> a >> basura;
			for (int j = 0; j < a; j++) {
				cin >> u;
				grafo[v].push_back(u);
			}
		}
		puentes = vector<pair<int, int>>();
		hora = 1;
		horaVertice = vi(V, 0); alcanzable = vi(V, -1);
		for (int i = 0; i < V; ++i) {
			if (!horaVertice[i]) {
				dfs(i, 0);
			}
		}
		sort(puentes.begin(), puentes.end());
		cout << puentes.size() << " critical links\n";
		for (int i = 0; i < puentes.size(); i++) {
			cout << puentes[i].first << " - " << puentes[i].second << '\n';
		}
		cout << '\n';

	}
	cin.rdbuf(cinbuf);
}
