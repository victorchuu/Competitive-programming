#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
#include <queue>
using lli = long long int;

lli gcd(lli a, lli b) {
	return b == 0 ? a : gcd(b, a % b);
}

bool solve(){
   lli mesas = 1, tam, n, nuevotam;
   cin >> tam;
   if(!tam)return 0;
   cin >> n;
   while(n){
       nuevotam = gcd(tam,n);
       if (nuevotam != tam){
           mesas *= (tam/nuevotam);
           tam = nuevotam;
        } 
        mesas += n/tam;
        cin >> n;
   }
   cout << mesas << '\n';
   return 1;
}

int main() {
	while (solve());
}
