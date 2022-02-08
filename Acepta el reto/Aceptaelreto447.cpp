#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include<queue>
using namespace std;

using lli = long long int;
using vi = vector<lli>;
using vvi = vector<vi>;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
    int l, r, n;
    cin >> l;
    while(l){
        cin >> r >> n;
        int d = n;
        while(r-- > 1){
            cin >> n;
            d = gcd(d,n);
        }

        if(l % d == 0)cout << "SI\n";
        else cout << "NO\n";
        cin >> l;
    }
}