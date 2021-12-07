#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int V; vvi adjMat, memo; // tabla de DP
int tsp(int pos, int visitados) {
	if (visitados == (1 << V) - 1) // hemos visitado ya todos los vértices
		return adjMat[pos][0]; // volvemos al origen
	if (memo[pos][visitados] != -1)
		return memo[pos][visitados];
	int res = 1000000000; // INF
	for (int i = 1; i < V; ++i)
		if (!(visitados & (1 << i))) // no hemos visitado vértice i
			res = min(res, adjMat[pos][i] + tsp(i, visitados | (1 << i)));
	return memo[pos][visitados] = res;
}

int abs(int x) {
	return (x > 0 ? x : -x);
}

int main() {

	int casos, a, b;
	cin >> casos;
	while (casos--) {
		vector<int> x, y;
		cin >> a >> a >> a >> b >> V;
		x.push_back(a); y.push_back(b);
		for (int i = 0; i < V; i++) {
			cin >> a >> b;
			x.push_back(a); y.push_back(b);
		}
		V++;
		adjMat = vvi(V, vi(V));
		for(int i = 0; i < V; i++)
			for (int j = i; j < V; j++) {
				int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
				adjMat[i][j] = dist;
				adjMat[j][i] = dist;
			}
		memo = vvi(V, vi(1 << V, -1));
		cout << "The shortest path has length " << tsp(0, 1) << '\n';
	}
}

