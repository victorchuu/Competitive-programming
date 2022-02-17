#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <queue>
#include<cmath>
#include <bitset>
using namespace std;

using uint = unsigned int;
using lli = long long int;
using vi = vector<int>;
using vvi = vector<vi>;

uint const MAX_PRIME = 100000;

bitset<MAX_PRIME+1> bs; 
vector<uint> primes; 

void sieve() {
    bs.set(); 
    bs[0] = bs[1] = 0;
    for (uint i = 2; i <= MAX_PRIME; ++i) {
        if (bs[i]) {
            for (uint j = i*i; j <= MAX_PRIME; j += i)
                bs[j] = 0; 
            primes.push_back(i);
        } 
    } 
} 

bool isPrime(unsigned long long n) {
    if (n <= MAX_PRIME)
        return bs[n];
    for (unsigned int i = 0; primes[i]*primes[i] <= n; ++i) {
        if (!(n % primes[i]))
            return false;
    }
    return true;
}

void solve(int n){
    lli Z;
    cin >> Z;
    lli t = floor(sqrt(Z)), p = t, q = t+1;
    while(!isPrime(p))
        p--;
    while(!isPrime(q))
        q++;
    if(p*q <= Z)
        cout << p*q;
    else {
        q = p-1;
        while(!isPrime(q))
            q--;
        cout << p*q;
    }
}

int main() {
    int T, n = 0;

    cin >> T;
    sieve();
    while(n++ < T){
        cout << "Case #" << n << ": ";
        solve(n);
        cout << '\n';
    }
}