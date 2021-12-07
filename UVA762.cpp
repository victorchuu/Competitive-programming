#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>

struct par {
	int origen, destino;
};

using namespace std;

int const INF = 2147483647;

int main() {

	int n;
	cin >> n;
	while (cin) {
		vector<string> traductor;
		vector<vector<int>> graph;
		unordered_map<string, int> mapa;
		string a, b;
		int turno = 0;
		while (n-- > 0) {
			cin >> a >> b;
			if (!mapa.count(a)) {
				traductor.push_back(a);
				graph.push_back(vector<int>());
				mapa[a] = turno++;
				for(int i = 0 ; i  )
			}
			if (!mapa.count(b)) {
				traductor.push_back(b);
				graph.push_back(vector<int>());
				mapa[b] = turno++;
			}
			graph[mapa[a]].push_back(mapa[b]);
			graph[mapa[b]].push_back(mapa[a]);
		}
		cin >> a >> b;

		if (!mapa.count(a) || !mapa.count(b)) {
			cout << "No route\n\n";
			cin >> n;
			continue;
		}
		vector<bool> visited(graph.size(), false);
		vector<int> camino(graph.size());

		queue<int> cola;
		cola.push(mapa[a]);
		int objetivo = mapa[b];
		bool found = false;
		while (!cola.empty()) {
			int v = cola.front(); cola.pop();
			if (v == objetivo) {
				found = true;
				break;
			}
			for (int u : graph[v]) {
				if (!visited[u]) {
					camino[u] = v;
					visited[u] = true;
					cola.push(u);
				}
			}
		}
		if (found) {
			stack<par> pila;
			while (objetivo != mapa[a]) {
				pila.push({ camino[objetivo], objetivo });
				objetivo = camino[objetivo];
			}
			while (!pila.empty()) {
				par p = pila.top(); pila.pop();
				cout << traductor[p.origen] << ' ' << traductor[p.destino] << '\n';
			}
			cout << '\n';
		}
		else {
			cout << "No route\n\n";
		}
		cin >> n;
	}
	return 0;
}