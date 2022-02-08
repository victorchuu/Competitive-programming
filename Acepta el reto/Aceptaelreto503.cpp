#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

using lli = long long int;
using vi = vector<lli>;
using vvi = vector<vi>;


int main(){
    int casos,n,m;
    cin >> casos;
    while(casos--){
        cin >> n >> m;
        if(++m > ++n)swap(n,m);
        int i = m+1;
        cout << m;
        for(;i <= n; i++){
            cout << ' ' << i ;
        }
        cout << '\n';
    }
}