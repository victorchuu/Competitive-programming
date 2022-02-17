#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
using namespace std;

using lli = long long int;
using vi = vector<int>;
using vvi = vector<vi>;

int log(int n){
    int sol = 0, p = 2;
    while(p < n){
        sol++;
        p *= 2;
    }
    return sol;
}

struct par{
    int weight;
    string diff;  
};
bool operator<(const par & one, const par & other){
        return one.weight > other.weight;
    }

string add (string & A, string & B){
    string sol = "";
    bool equal = true;
    for(int i = 0; i < A.size(); i++){
        if(A[i] != B[i])
            equal = false;
        if(A[i] == '1' || B[i] == '1')
            sol.push_back('1');
        else
            sol.push_back('0');
    }
    return (equal ? "" : sol);
}

int solve(){
    int N, M, P;
    char c;
    cin >> N >> M >> P;
    // The words have length P
    vi prefs(P,0); // This list saves the amount of people that would prefer option 1 rather than 0
    for(int i = 0; i < N ; i++){
        for(int j = 0; j < P; j++){
            cin >> c;
            if(c == '1')prefs[j]++;
        }
    }
    string best = ""; // The solution that satisfies the most people
    int complaints = 0;
    for(int i = 0; i < P ; i++){ 
        if(prefs[i] > N/2){
            complaints += N - prefs[i];
            prefs[i] = 2*prefs[i] - N;
            best.push_back('1');
        } else {
            complaints += prefs[i];
            prefs[i] = N - 2*prefs[i];
            best.push_back('0');
        }
    }
    // prefs[i] is now the amount of complaints that we get if we change the value of best[i]

    // We save in a hash map the number of differences between each forbidden word and best
    unordered_set<string> forbidden;
    string str;
    for(int i = 0; i < M ; i++){
        cin >> str;
        for(int j = 0; j < P ; j++){
            if(str[j] == best[j])str[j]='0';
            else str[j] = '1';
        }
        forbidden.insert(str);
    }

    //We are going to consider the best M+1 posibilities. The optimal solution must be among those
    //We use an ordered queue to always have the best solution at hand.
    priority_queue<par> q;
    unordered_map<string,int> repeated;
    string ssss(P,'0'), motherfucker;
    q.push({0,ssss});
    repeated[ssss] = 0;
    ssss[0] = '1';
    q.push({prefs[0], ssss});
    repeated[ssss] = prefs[0];
    for(int i = 1; i < P; i++){
        ssss[i-1] = '0';
        ssss[i] = '1';
        q.push({prefs[i], ssss});
        repeated[ssss] = prefs[i];
    }

    vector<string> extracted;
    bool not_found = true;
    while(not_found){
        par p = q.top(); q.pop();
        motherfucker = p.diff;
        if(!forbidden.count(motherfucker)){
            not_found = false;
            break;
        }
        extracted.push_back(motherfucker);
        for(auto guy : extracted){
            string sol = add(motherfucker,guy);
            if (sol.size() > 0){
                if(!repeated.count(sol)){
                    repeated[sol] = repeated[guy] + repeated[motherfucker];
                    q.push({repeated[sol] , sol});
                }
            }
        }
    }
    return complaints + repeated[motherfucker];
}

int main() {
    int T, n = 0;
    cin >> T;
    while(n++ < T){
        
        int AAAAAAA = solve();
        cout << "Case #" << n << ": " << AAAAAAA << '\n';
    }
}