#include<iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int M, N; vvi grafo; //Solo los primeros M vertices 
vi match, vis;
int aug(int l) {
	if (vis[l]) return 0;
	vis[l] = 1;
	for (auto r : grafo[l])
		if (match[r] == -1 || aug(match[r])) {
			match[r] = l;
			return 1;
		}
	return 0;
}
int berge_mcbm() {
	int mcbm = 0;
	match.assign(N + M, -1);
	for (int l = 0; l < M; l++) {
		vis.assign(M, 0);
		mcbm += aug(l);
	}
	return mcbm;
}

using ii = pair<double, double>;
using vii = vector<ii>;

int main() {
	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());


	int s, v;
	while (cin >> M >> N) {
		cin >> s >> v;
		vii gophers(M), holes(N);
		for (int i = 0; i < M; i++)
			cin >> gophers[i].first >> gophers[i].second;
		for (int i = 0; i < N; i++)
			cin >> holes[i].first >> holes[i].second;
		grafo = vvi(M);
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				int x = gophers[i].first - holes[j].first;
				int y = gophers[i].second - holes[j].second;
				if (x * x + y * y < s * s * v * v)
					grafo[i].push_back(j);
			}
		}
		cout << M-berge_mcbm() << '\n';
	}
	cin.rdbuf(cinbuf);
}