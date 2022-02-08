#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
#include <queue>

bool solve(){
    int n,k,i,num;
    pair<int,int> tope;
    cin >> n >> k;
    if(n == 0)return 0;
    priority_queue<pair<int,int>> pq;
    i = 0;
    while(i < k){
        cin >> num;
        pq.push({num,i});
        i++;
    }
    cout << pq.top().first;
    while(i < n){
        cin >> num;
        pq.push({num,i});
        tope = pq.top();
        while(tope.second < i - k + 1){
            pq.pop();
            tope = pq.top();
        }
        cout << ' ' << tope.first;
        i++;
    }
    cout << '\n';
    return 1;
}

int main() {

	
	while (solve());


}
