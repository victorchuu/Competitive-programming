#include <iostream>
#include <vector>
#include <string>

#define INF 1e9

// Typedefs
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<long long>

// Common Methods
#define PB push_back
#define MP make_pair
#define ALL(x) (x).begin(), (x).end()

// Loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define REP(i,n) FOR(i,0,n)


using namespace std;
typedef long long int bigint;

vector<bigint> readInts(int n) {
    vector<bigint> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    return numbers;
}

vector<string> read(int n) {
    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }
    return strings;
}

void solve() {}
void solve(int n) {}

void numCases() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        solve();
}
    
void until(int ending) {
    int nextCase;
    cin >> nextCase;
    while (nextCase != ending) {
        solve(nextCase);
        cin >> nextCase;
    }
}

void untilEOF() {
    int nextCase;
    while (cin >> nextCase) {
        solve(nextCase);
    }
}

int main() {
    if (string(getenv("USER")) == "victor") {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}