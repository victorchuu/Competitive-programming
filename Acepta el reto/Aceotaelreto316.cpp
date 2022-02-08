#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using lli = long long int;

vi v;

struct cosa {
    int a;
    int b;
    int maximo; // v[a] + ... + v[b] 
};

cosa f (int i, int j){
    if(i == j)
        return {i,i,v[i]};
    int mitad = (i + j - 1)/2;
    cosa cosa1 = f(i,mitad), cosa2 = f(mitad+1,j);
    int maximo = cosa1.maximo + cosa2.maximo;
    for(int z = cosa1.b + 1 ; z < cosa2.a ; z++)
        maximo += v[z];
    if(maximo > cosa1.maximo && maximo > cosa2.maximo)
        return {cosa1.a, cosa2.b, maximo};
    else if(cosa1.maximo > cosa2.maximo)
        return cosa1;
    else if(cosa1.maximo == cosa2.maximo && cosa1.b-cosa1.a <= cosa2.b-cosa1.a)
        return cosa1;
    return cosa2;
}

bool solve(){
    int n;
    cin >> n;
    v = vi(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    cosa c = f(0,n-1);
    cout << c.a + 1 << ' ' << c.b + 1 << '\n';
    return 1;
}

int main() {
    int casos;
    cin >>casos;
	while (casos--)solve();
}
