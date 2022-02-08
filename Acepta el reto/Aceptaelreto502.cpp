#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

using lli = long long int;
using vi = vector<lli>;
using vvi = vector<vi>;

//[i, j]
int binsearch(vi & v,int elem, int i, int j){
    if(i == j)return i;
    int mitad = (i+j)/2;
    if(elem >= v[mitad])
        return binsearch(v,elem,mitad+1,j);
    else
        return binsearch(v,elem,i,mitad);
}

int main(){
    int n,a;
    while(cin >> n){
        vi v;
        while(n--){
            cin >> a;
            if(v.empty() || a >= v[v.size()-1])
                v.push_back(a);
            else
                v[binsearch(v,a,0,v.size())] = a;
        }
        cout << v.size() << '\n';
    }
}