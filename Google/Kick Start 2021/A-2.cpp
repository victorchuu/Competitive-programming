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

int Lshapes(int a, int b){
    // Given the 2 lengths of the sides of an L shape, 
    // this function determines the number of L-shapes
    // that match the problem description
    if(a < 2 || b < 2)return 0;
    int sol = 0;
    if(a >= 2*b) sol += b-1;
    else if(a > 3) sol += (a-2)/2;
    if(b >= 2*a) sol += a-1;
    else if(b > 3) sol += (b-2)/2;
    return sol;
}

void solve(int n){
    int R,C;
    cin >> R >> C;
    vvi mat(R,vi(C,0));
    vvi up = mat,down = mat,left = mat,right = mat;
    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            cin >> mat[i][j];

    int k;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            k = 1;
            while(j < C && mat[i][j]){
                left[i][j++] = k++;
            }
        }
        for(int j = C-1; j >= 0; j--){
            k = 1;
            while(j >= 0 && mat[i][j]){
                right[i][j--] = k++;
            }
        }
    }

    for(int j = 0; j < C; j++){
        for(int i = 0; i < R; i++){
            k = 1;
            while(i < R && mat[i][j]){
                up[i++][j] = k++;
            }
        }
        for(int i = R-1; i >= 0; i--){
            k = 1;
            while(i >= 0 && mat[i][j]){
                down[i--][j] = k++;
            }
        }
    }

    long long int cnt = 0;
    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++){
            cnt += Lshapes(up[i][j],left[i][j])
            + Lshapes(up[i][j],right[i][j])
            + Lshapes(down[i][j],left[i][j])
            + Lshapes(down[i][j],right[i][j]);
        }
    cout << "Case #" << n << ": " << cnt << '\n';
}

int main() {
    int T, n = 0;
    cin >> T;
    while(n++ < T){
        solve(n);
    }
}