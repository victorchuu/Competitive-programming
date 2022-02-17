#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;

using lli = long long int;
using vi = vector<int>;
using vvi = vector<vi>;

void solve(int n){
    char a, b;
    int N, cnt = 1;
    cin >> N;
    cin >> a;
    cout << "Case #" << n << ": 1";
    for(int i = 1; i < N; i++){
        cin >> b;
        if(b > a) cnt++;
        else cnt = 1;
        cout << ' ' << cnt;
        a = b;
    }
    cout << '\n';
}

int main() {
    int T, n = 0;

    cin >> T;
    while(n++ < T){
        solve(n);
    }
}