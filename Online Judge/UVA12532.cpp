#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) { ft.assign(n + 1, 0); }
	int getSum(int b) {
		int ret = 0;
		while (b) {
			ret += ft[b]; //OPERADOR
			b -= (b & -b);
		}
		return ret;
	}
	void add(int pos, int val) {
		while (pos < ft.size()) {
			ft[pos] += val; //OPERADOR
			pos += (pos & -pos);
		}
	}
	int getSum(int a, int b) {
		return getSum(b) - getSum(a - 1);
	} //OPERADOR
	int getValue(int pos) {
		return getSum(pos) - getSum(pos - 1);
	} //OPERADOR
	void setValue(int pos, int val) {
		add(pos, val - getValue(pos));
	} //OPERADOR
};

int main() {
	int n, q;
	while (cin >> n >> q) {
		FenwickTree ceros(n), negativos(n);
		int num;
		for (int i = 1; i <= n; i++) {
			cin >> num;
			if (num == 0) {
				ceros.add(i, 1);
			}
			else if (num < 0) {
				negativos.add(i, 1);
			}
		}
		char c; int pos;
		while (q--){
			cin >> c;
			if (c == 'C') {
				cin >> pos >> num;
				negativos.setValue(pos, 0);
				ceros.setValue(pos, 0);
				if (num == 0) {
					ceros.setValue(pos, 1);
				}
				else if(num < 0) {
					negativos.setValue(pos, 1);
				}
			}
			else if (c == 'P') {
				cin >> pos >> num;
				if (ceros.getSum(pos, num) > 0)
					cout << '0';
				else if (negativos.getSum(pos, num) % 2 == 0)
					cout << '+';
				else cout << '-';
			}
		}
		cout << '\n';
	}

}