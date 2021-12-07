#include <iostream>
#include<vector>
#include<unordered_set>
#include <queue>
#include <fstream>

using namespace std;


int INF = 1000000000;

vector<int> parent;
vector<vector<int>> adj;
vector<vector<int>> cap;
vector<bool> visited;

void bfs(int s, int t) {
	queue<int> q;
	visited = vector<bool>(parent.size(), 0);
	q.push(s);
	parent[s] = -1; visited[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			if (!visited[v] && (cap[u][v] > 0)) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int sendFlow(int s, int t) {
	// Intentamos llegar de s a t
	bfs(s, t);
	if (!visited[t])
		return 0; // No pudimos
		// Buscamos capacidad m´as peque˜na en el camino
	int flow = INF, v = t;
	while (v != s) {
		flow = min(cap[parent[v]][v], flow);
		v = parent[v];
	}
	// Mandamos flujo
	v = t;
	while (v != s) {
		cap[parent[v]][v] -= flow;
		cap[v][parent[v]] += flow; // INVERSA
		v = parent[v];
	}
	return flow;
}

int edmondsKarp(int s, int t) {
	int ret = 0;
	int flow = 0;
	do {
		flow = sendFlow(s, t);
		ret += flow;
	} while (flow > 0);
	return ret;
}

void mibfs(int s) {
	queue<int> q;
	visited = vector<bool>(parent.size(), 0);
	q.push(s);
	visited[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			if (!visited[v] && (cap[u][v] > 0)) {
				visited[v] = true;
				q.push(v);
			}
		}
	}
	for (int u = 0; u < visited.size(); u++) {
		if (visited[u]) {
			for (int v : adj[u]) {
				if (!visited[v]) {
					cout << u+1 << ' ' << v+1 << '\n';
				}
			}
		}
	}
}

int main() {

	/*ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());//*/

	int v, edges;
	cin >> v >> edges;
	while (v != 0 && edges != 0) {
		adj = vector<vector<int>>(v,vector<int>());
		cap = vector<vector<int>>(v, vector<int> (v,0));
		int a, b, c;
		for (int p = 0; p < edges; p++){
			cin >> a >> b >> c;
			adj[--a].push_back(--b);
			adj[b].push_back(a);
			cap[a][b] = c;
			cap[b][a] = c;
		}
		parent = vector<int>(v+2);
		/*adj[0].push_back(1);
		adj[1].push_back(0);
		adj[v + 1].push_back(2);
		adj[2].push_back(v + 1);
		cap[0][1] = INF;
		cap[2][v + 1] = INF;*/
		edmondsKarp(0, 1);

		mibfs(0);
		cout << '\n';
		cin >> v >> edges;
	}

	//cin.rdbuf(cinbuf);
}