#include <iostream>
#include <vector> 
#include<algorithm>
#include<set>
#include<iomanip>
#include <cmath>
#include<random>
#include<tuple>
#include<cassert>
#include <fstream>
using namespace std;
const double EPS = 1e-9;
const double PI = acos(-1);
using T = double;
struct pt {
	T x, y; int altura;
	pt operator+(pt p) const { return { x + p.x, y + p.y }; }
	pt operator-(pt p) const { return { x - p.x, y - p.y }; }
	pt operator*(T d) const { return { x * d, y * d }; }
	pt operator/(T d) const { return { x / d, y / d }; }
	bool operator==(pt o) const { return x == o.x && y == o.y; }
	bool operator!=(pt o) const { return !(*this == o); }
	bool operator<(pt o) const {
		if (x == o.x) return y < o.y;
		return x < o.x;
	}
};
T distsq(pt v) { return v.x * v.x + v.y * v.y; }
double modulo(pt v) { return sqrt(distsq(v)); }

T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
bool isPerp(pt v, pt w) { return dot(v, w) == 0; }
double angle(pt v, pt w) {
	double cosTheta = dot(v, w) / modulo(v) / modulo(w);
	return acos(max(-1.0, min(1.0, cosTheta)));
}
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
// positivo/cero/negativo: c a la izquieda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
bool inAngle(pt a, pt b, pt c, pt p) {
	assert(orient(a, b, c) != 0);
	if (orient(a, b, c) < 0) swap(b, c);
	return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
	if (orient(a, b, c) >= 0)
		return angle(b - a, c - a);
	else
		return 2 * PI - angle(b - a, c - a);
}

// ORDENACI�N POLAR
bool half(pt p) { // true if in blue half
	assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
	return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pt>& v) {
	sort(v.begin(), v.end(), [](pt v, pt w) {
		return make_tuple(half(v), 0, distsq(v)) < make_tuple(half(w), cross(v, w), distsq(w));
		});
}

pt translate(pt v, pt p) { return p + v; }
pt scale(pt c, double factor, pt p) {
	return c + (p - c) * factor;
}
// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a) {
	return { p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a) };
}
// rotate 90� counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }

struct line {
	pt v; T c;
	// v:vector director, c: punto
	line(pt v, T c) : v(v), c(c) {}
	// from equation ax + by = c
	line(T a, T b, T c) : v({ b,-a }), c(c) {}
	// from points p and q
	line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
	T side(pt p) { return cross(v, p) - c; }
	double dist(pt p) { return abs(side(p)) / modulo(v); }
	line translate(pt t) { return { v, c + cross(v,t) }; }
	pt proj(pt p) { return p - perp(v) * side(p) / distsq(v); }
};

bool inter(line l1, line l2, pt& out) {
	T d = cross(l1.v, l2.v);
	if (d == 0) return false;
	out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
	return true;
}
// POLIGONOS, el primer y �ltimo puntos coinciden
double areaTriangle(pt a, pt b, pt c) {
	return abs(cross(b - a, c - a)) / 2.0;
}
double areaPolygon(vector<pt> const& p) {
	double area = 0.0;
	for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
		area += cross(p[i], p[i + 1]);
	}
	return abs(area) / 2.0;
}
// if strict, returns false when A is on the boundary
/*bool inPolygon(vector<pt> const& p, pt a, bool strict = true) {
	int numCrossings = 0;
	for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
		if (onSegment(p[i], p[i + 1], a))
			return !strict;
		numCrossings += crossesRay(a, p[i], p[i + 1]);
	}
	return numCrossings & 1; // inside if odd number of crossings
}*/
bool isConvex(vector<pt> const& p) {
	bool hasPos = false, hasNeg = false;
	for (int i = 0, n = (int)p.size(); i < n; ++i) {
		int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
		if (o > 0) hasPos = true;
		if (o < 0) hasNeg = true;
	}
	return !(hasPos && hasNeg);
}

// ENVOLVENTE CONVEXA
// para aceptar puntos colineales cambia a >=
// returns true if point r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
	return orient(p, q, r) > 0;
}
vector<pt> convexHull(vector<pt>& P) {
	int n = int(P.size()), k = 0;
	vector<pt> H(2 * n);
	sort(P.begin(), P.end());
	// build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && !ccw(H[k - 2], H[k - 1], P[i])) --k;
		H[k++] = P[i];
	}
	// build upper hull
	for (int i = n - 2, t = k + 1; i >= 0; --i) {
		while (k >= t && !ccw(H[k - 2], H[k - 1], P[i])) --k;
		H[k++] = P[i];
	}
	H.resize(k);
	return H;
}
// DIVISI�N DE UN POL�GONO
vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
	vector<pt> R; pt c;
	for (int i = 0; i < int(P.size()) - 1; i++) {
		double left1 = cross(b - a, P[i] - a),
			left2 = cross(b - a, P[i + 1] - a);
		if (left1 >= 0) R.push_back(P[i]);  // P[i] is on the left of ab
		if (left1 * left2 < 0) {  // edge (P[i], P[i+1]) crosses line ab
			inter({ P[i], P[i + 1] }, { a,b }, c);
			R.push_back(c);
		}
	}
	if (!R.empty())
		R.push_back(R[0]); // make R's first point = R's last point
	return R;
}

int main() {
	int n, set = 1;
	cin >> n;
	while (n != 0) {
		vector<pt> puntos(n), tapados;
		for (int i = 0; i < n; i++) {
			cin >> puntos[i].x >> puntos[i].y >> puntos[i].altura;
		}
		polarSort(puntos);
		double angulo = 0;
		int maximo = 0;
		for (int i = 0; i < n; i++) {
			pt p = puntos[i];
			if (abs(angle(p, { 1,0 }) - angulo) < EPS) {
				if (maximo >= p.altura) {
					tapados.push_back(p);
				}
				maximo = max(maximo, p.altura);
			}
			else {
				maximo = p.altura;
				angulo = angle(p, { 1,0 });
			}
		}
		sort(tapados.begin(), tapados.end());
		cout << "Data set " << set++ << ":\n";
		if (tapados.size() == 0) {
			cout << "All the lights are visible.\n";
		}
		else {
			cout << "Some lights are not visible:\n";
			for (int i = 0; i < tapados.size() - 1; i++) {
				pt p = tapados[i];
				cout << "x = " << (int)p.x << ", y = " << (int)p.y << ";\n";
			}
			pt p = tapados[tapados.size() - 1];
			cout << "x = " << (int)p.x << ", y = " << (int)p.y << ".\n";
		}
		
		cin >> n;
	}
}