#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
vi cuenta;
int V; vvi grafo;
int hora; vi horaVertice, alcanzable;
void dfs(int u, int uParent) {
	horaVertice[u] = alcanzable[u] = hora; hora++;
	for (int i = 0; i < grafo[u].size(); ++i) {
		int v = grafo[u][i];
		if (v == uParent) continue; // BackEdge con el padre, que ignoramos
		if (horaVertice[v] == 0) { // No visitado
			dfs(v, u);
			if (alcanzable[v] >= horaVertice[u]) {
				cuenta[u]++;
			}				//<algorithm>
			alcanzable[u] = min(alcanzable[u], alcanzable[v]);
		}
		else
			alcanzable[u] = min(alcanzable[u], horaVertice[v]); // BackEdge
	}
}

int main() {
	cin >> V; string s; 
	while (V != 0) {	
		grafo = vvi(V);
		int v;
		cin >> v;
		while (v != 0) {
			v--;
			getline(cin, s);
			stringstream ss(s);
			int num;
			while (ss >> num) {
				grafo[v].push_back(num - 1);
				grafo[num - 1].push_back(v);
			}
			cin >> v;
		}
		hora = 1;
		cuenta = vi(V, 0);
		horaVertice = vi(V, 0); alcanzable = vi(V, -1);
		for (int i = 0; i < V; ++i) {
			if (!horaVertice[i]) {
				cuenta[i] = -1;
				dfs(i, 0);
			}
		}
		int total = 0;
		for (int c : cuenta)
			if (c > 0) total++;
		cout << total << '\n';
		cin >> V;
	}
}





// BUSCA PUNTOS ARTICULACION

// Igual que puentes, con un >=, y PUEDEN REPETIRSE 
// al encontrarlo hacer cuenta[u]++
// El primer nodo siempre aparece una vez, aunque no sea de articulacion
// Antes de la llamada a dfs, hacerle cuenta[u] = -1