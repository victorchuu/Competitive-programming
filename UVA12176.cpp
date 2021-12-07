#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct UFDS {
	vector<int> p;
	int numSets;
	UFDS(int n) : p(n, 0), numSets(n) {
		for (int i = 0; i < n; ++i) p[i] = i;
	}
	int find(int x) {
		return (p[x] == x) ? x : p[x] = find(p[x]);
	}
	void merge(int x, int y) {
		int i = find(x), j = find(y);
		if (i == j) return;
		p[i] = j;
		--numSets;
	}
};

struct arista {
	int coste, origen, destino;
};

struct orden {
	bool operator()(arista a, arista b) {
		return a.coste < b.coste;
	}
};

void kruskal(vector<arista>& grafo, vector<arista> & arbol, int N) {
	
	orden ord;
	sort(grafo.begin(), grafo.end(), ord);

	UFDS UF(N);
	int i = 0;
	while (i < grafo.size() && UF.numSets > 1) {
		arista ar = grafo[i];
		if (UF.find(ar.destino) != UF.find(ar.origen)) {
			arbol.push_back(ar);
			UF.merge(ar.destino, ar.origen);
		}
		i++;
	}
}

void longest_edge(vector<arista> & arbol, int N, int src, int dest) {

	UFDS UF(N);
	for (int i = 0; i < arbol.size(); i++) {
		arista ar = arbol[i];
		if (UF.find(ar.destino) != UF.find(ar.origen)) {
			UF.merge(ar.destino, ar.origen);
		}
		if (UF.find(src) == UF.find(dest)) {
			cout << ar.coste << '\n'; break;
		}
	}

}

int main() {
	int casos;
	cin >> casos;
	for (int caso = 1; caso <= casos; caso++) {
		//Lectura
		int N, R, u, v ,d; cin >> N >> R;

		vector<arista> grafo, arbol;

		for (int i = 0; i < R; i++) {
			cin >> u >> v >> d;
			grafo.push_back({ d,u-1,v-1 });
		}

		kruskal(grafo, arbol, N);
		cout << "Case " << caso << '\n';

		int Q, k, t;
		cin >> Q;
		while (Q--) {
			cin >> k >> t;
			k--; t--;
			longest_edge(arbol, N, k, t);
		}
	}
}