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
	int n, a, b, y;
	cin >> n;
	while (n != 0) {
		FenwickTree tree(100001);
		char c;
		while (n--) {
			cin >> c;
			if (c == 'B') {
				cin >> a >> b >> y;
				tree.add(a, y);
				tree.add(b+1, -y);
			}
			else {
				cin >> a;
				cout << tree.getSum(a) << '\n';
			}

		}

		cin >> n;
	}
}