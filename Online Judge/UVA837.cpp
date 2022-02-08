#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
#include <fstream>
using namespace std;


struct punto{
    double x;
    double y;
    bool fin;
    double refraccion;
};

struct orden {
    bool operator()(punto A, punto B) {
        return A.x < B.x;
    }
};

int main() {

#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	int casos;
	cin >> casos;
	while (casos-- > 0) {
        int NL;
        cin >> NL;
        double x1, y1, x2, y2, ref;
        vector<punto> lista;
        for (int q = 0; q < NL; q++) {
            cin >> x1 >> y1 >> x2 >> y2 >> ref;
            if (x1 <= x2) {
                lista.push_back({ x1,y1,false,ref });
                lista.push_back({ x2,y2,true,ref });
            }
            else {
                lista.push_back({ x2,y2, false,ref});
                lista.push_back({ x1,y1,true,ref });
            }
        }

        if (NL == 0) {
            cout << "1\n-inf +inf 1.000\n\n";
            continue;
        }

        orden ord;
        sort(lista.begin(), lista.end(), ord);
        
        cout << 2 * NL + 1 << '\n';
        int segments = 1;
        double luz = 1;
        cout << "-inf " << fixed << setprecision(3) << lista[0].x << ' ' << luz << '\n';
        luz *= lista[0].refraccion;
        for (int i = 1; i < lista.size(); i++) {
            cout << fixed << setprecision(3) << lista[i - 1].x << ' ' << lista[i].x << ' ' << luz << '\n';
            if (lista[i].fin) {
                luz = luz / lista[i].refraccion;
            }
            else {
                luz *= lista[i].refraccion;
            }
        }
        cout << lista[lista.size() - 1].x << " +inf 1.000\n\n";
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

	return 0;
}