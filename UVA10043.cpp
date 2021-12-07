#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct par {
	int x, y;
};

struct ordenx {
	bool operator()(par a, par b) {
		return a.x < b.x;
	}
};

struct ordeny {
	bool operator()(par a, par b) {
		return a.y < b.y;
	}
};

void max(int& m, int otro) {
	if (otro > m) m = otro;
}

void f(int& m, vector<par>& arboles, int indice, int sup, int inf, int l) {
	if (indice >= arboles.size()) {
		max(m, l * (inf - sup));
		return;
	}
	if (inf > arboles[indice].y && arboles[indice].y > sup) {
		max(m, (inf - sup) * arboles[indice].x);
		f(m, arboles, indice + 1, sup, arboles[indice].y, l);
		f(m, arboles, indice + 1, arboles[indice].y, inf, l);
	}
	else {
		f(m, arboles, indice + 1, sup, inf, l);
	}
}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	int casos;
	cin >> casos;
	int l, w, n, x, y, dx, dy;
	while (casos--) {
		cin >> l >> w;
		cin >> n;
		vector<par> arboles;
		while (n != 0) {
			if (n == 1) {
				cin >> x >> y;
				arboles.push_back({ x,y });
			}
			else {
				cin >> x >> y >> dx >> dy;
				for (int i = 0; i < n; i++) {
					arboles.push_back({ x,y });
					x += dx; y += dy;
				}
			}
			cin >> n;


		}
		vector<par> copia = arboles;
		
		sort(arboles.begin(), arboles.end(), ordenx());
		sort(copia.begin(), copia.end(), ordeny());

		int m = 0;
		for (int i = 0; i < arboles.size(); i++) {
			par arbol = arboles[i];
			int inferior = w, superior = 0;
			for (int j = i+1; j < arboles.size(); j++) {
				if (arboles[j].x > arbol.x && inferior > arboles[j].y && arboles[j].y > superior) {
					max(m, (inferior - superior) * (arboles[j].x - arbol.x));
					if (arbol.y <= arboles[j].y) inferior = arboles[j].y;
					if (arbol.y >= arboles[j].y) superior = arboles[j].y;
				}
			}
			max(m, (inferior - superior) * (l - arbol.x));
		}

		f(m, arboles, 0, 0, w, l);
		cout << m << '\n';
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}