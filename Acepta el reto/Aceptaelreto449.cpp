#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include<queue>
using namespace std;

using lli = long long int;
using vi = vector<int>;
using vvi = vector<vi>;
const int INF = 1000000000;

string s;
vvi tabla;

void trim(int & i, int & j, char c){
    while(s[i] == c)
        i++;
    while(s[j] == c)
        j--;
}

int f(int i, int j){
    if(i > j) return 0;
    if(tabla[i][j] >= 0) return tabla[i][j];
    if(i == j) return 1;
    int x = i, y = j;
    trim(x,y,s[i]);
    int sol = f(x,y);
    x = i; y = j;
    trim(x,y,s[j]);
    sol = 1 + min(sol,f(x,y));
    tabla[i][j] = sol;
    return sol;
}

int main(){
    int n;
    while(cin >> s){
        n = s.size();
        tabla = vvi(n,vi(n,-1));
        cout << f(0,n-1) << '\n';
    }
}