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

struct p {
    int ini,fin;
};

struct orden {
    bool operator()(p a, p b){
        return a.ini < b.ini;
    }
};

int main(){
    int n;
    while(cin >> n){
        vector<p> v(n);
        for(int i = 0; i < n ; i++){
            cin >> v[i].ini >> v[i].fin;
        }
        sort(v.begin(),v.end(),orden());

        priority_queue<int,vector<int>,greater<int>> cola;

        int count = 0;
        for(p elem : v){
            if(count == 0 || cola.top() > elem.ini)
                count++;
            else
                cola.pop();
            cola.push(elem.fin);    
        }

        cout << count-1 << '\n';
    }
}