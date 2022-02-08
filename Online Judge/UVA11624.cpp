#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<int> X = { 0,1,0,-1 };
vector<int> Y = { 1,0,-1,0 };

struct pos {
	int fila, col, spread;
};

void mark(vector<vector<int>>& mapa, int f, int c, int spread) {
	if (f >= 0 && f < mapa[0].size() && c >= 0 && c < mapa.size() && mapa[f][c] == 0)
		mapa[f][c] = spread + 1;
}

int main() {
	int casos;
	cin >> casos;
	while (casos-- > 0) {
		int R, C;
		cin >> R >> C;
		vector<vector<int>> mapa(R, vector<int>(C, 2147483647));
		char casilla;
		queue<pos> cola;
		queue<pos> cola2;
		for (int r = 0; r < R ; r++) {
			for (int c = 0; c < C; c++) {
				cin >> casilla;
				switch (casilla)
				{
				case '#': mapa[r][c] = -1; break;
				case 'F': cola.push({ r,c,1 }); mapa[r][c] = 1; break;
				case 'J': cola2.push({ r,c,2 }); break;
				default: break;
				}
			}
		}
		while (!cola.empty()) {
			pos p = cola.front(); cola.pop();
			for (int i = 0; i < 4; i++) {
				int f = p.fila + X[i], c = p.col + Y[i];
				if (f >= 0 && f < R && c >= 0 && c < C && mapa[f][c] == 2147483647) {
					mapa[f][c] = p.spread + 1;
					cola.push({ f,c,p.spread + 1 });
				}
			}
		}
		/*for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				cout << mapa[r][c];
			}
			cout << '\n';
		}//*/
		bool alcanzado = false; int pasos = 0;
		while (!cola2.empty()) {
			pos p = cola2.front(); cola2.pop();
			if (p.col == 0 || p.fila == 0 || p.fila == R - 1 || p.col == C - 1) {
				alcanzado = true; pasos = p.spread - 1; break;
			}
			for (int i = 0; i < 4; i++) {
				int f = p.fila + X[i], c = p.col + Y[i];
				if (f >= 0 && f < R && c >= 0 && c < C && mapa[f][c] > p.spread) {
					mapa[f][c] = 0; //Marca de vertices visitados
					cola2.push({ f,c,p.spread + 1 });
				}
			}
		}
		if (alcanzado) {
			cout << pasos << '\n';
		}
		else {
			cout << "IMPOSSIBLE\n";
		}
	}
}