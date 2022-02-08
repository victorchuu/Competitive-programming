#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int dist(int a1, int b1, int a2, int b2){
    return abs(a1-a2)+abs(b1-b2);
}

void solve(){
    int n;
    cin >> n;
    vi A(n+1,0), B(n+1,0);
    for(int i = 1; i <= n; i++)
        cin >> A[i] >> B[i];
    int minimo;
    // Dinamic programming
    vi M = {dist(A[0],B[0],A[1],B[1])}; 
    int k = 2;
    for(; k <= n; k++){
        minimo = 1000000000;
        for(int i = 0; i < k-1; i++){
            minimo = min(minimo,M[i] + dist(A[i],B[i],A[k],B[k]));
            M[i] += dist(A[k-1],B[k-1],A[k],B[k]);
        }
        M.push_back(minimo);
    }
    minimo = 1000000000;
    for(int i = 0; i < k-1; i++){
         minimo = min(minimo,M[i]);
    }
    cout << minimo << '\n';
}

int main() {

	int casos;
	cin >> casos;
	while (casos-- > 0) {
        solve();
	}


}
