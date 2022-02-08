#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
int const INF = 1000000000;

int V, sumidero;
vector<bool> visited; vvi grafo, adjMat;
int dfs(int u, int flow) {
	visited[u] = true;
	if (u == sumidero) return flow;
	for (int v : grafo[u]) {
		if (!visited[v] && adjMat[u][v] > 0) {
			int sol = dfs(v, min(flow, adjMat[u][v]));
			if (sol > 0) {
				adjMat[u][v] -= sol;
				adjMat[v][u] += sol;
				return sol;
			}
		}
	}
	return 0;
}
int maxFlow(int s, int t) {
	int ret = 0; sumidero = t;
	int flow = 0;
	do { visited = vector<bool>(V, false);
		flow = dfs(s,INF);
		ret += flow;
	} while (flow > 0);
	return ret;
}

int main() {
	
	int foco, aristas, u, v, f, caso = 1;
	cin >> V; 
	while (V != 0) {
		cin >> foco >> sumidero >> aristas;
		grafo = vvi(V);
		adjMat = vvi(V, vi(V,0));
		while (aristas--) {
			cin >> u >> v >> f;
			grafo[--u].push_back(--v);
			grafo[v].push_back(u);
			adjMat[u][v] += f;
			adjMat[v][u] += f;
		}
		cout << "Network " << caso++ << "\nThe bandwidth is " << maxFlow(--foco, --sumidero) << ".\n";
		cin >> V;
	}

}