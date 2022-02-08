#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int V;
vvi adjMat, camino;
void floyd() {
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j]) {
					adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
					camino[i][j] = k;
				}
}

void reconstruct(int src, int dst) {
	if (src == dst) return;
	int k = camino[src][dst];
	if (k == dst) {
		cout << ' ' << dst+1; return;
	}
	reconstruct(src, k);
	reconstruct(k, dst);
}

int INF = 1000000000;

int main() {
	cin >> V;
	int caso = 1, src, dst;
	while (V != 0) {
		string s;
		adjMat = vvi(V, vi(V,INF));
		camino = vvi(V, vi(V));
		getline(cin, s);
		for (int i = 0; i < V; i++) {
			adjMat[i][i] = 0;
			getline(cin, s); 
			stringstream ss(s);
			int n, v, d;
			ss >> n;
			for (int j = 0; j < n; j++) {
				ss >> v >> d;
				v--;
				adjMat[i][v] = d;
				camino[i][v] = v;
			}
		}
		cin >> src >> dst;
		floyd();
		cout << "Case " << caso++ << ": Path = " << src;
		reconstruct(--src, --dst);
		cout << "; " << adjMat[src][dst] << " second delay\n";
		cin >> V;
	}
}