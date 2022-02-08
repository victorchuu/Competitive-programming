#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

using lli = long long int;
using vi = vector<lli>;
using vvi = vector<vi>;

const int modulo = 1000000007;

const int MAXN = 10;
class Trie
{
    int prefixes;
    int words;
    vector<Trie *> child;

public:
    Trie() : prefixes(0), words(0), child(MAXN, nullptr) {}
    ~Trie()
    {
        for (int i = 0; i < MAXN; ++i)
            delete child[i];
    }
    void add(string &s, int i)
    {
        if (s[i] == '\0')
            ++words;
        else
        {
            Trie *t;
            if (child[s[i] - '0'] == nullptr)
            {
                t = child[s[i] - '0'] = new Trie();
                t->prefixes = 1;
            }
            else
            {
                t = child[s[i] - '0'];
                t->prefixes++;
            }
            t->add(s, i + 1);
        }
    }

    void search(vi &v, string &s, int i, lli combinaciones)
    {
        if (i > (int)s.size())
            return;
        v[i] += combinaciones * words % modulo;
        if (child[s[i] - '0'] != nullptr){
            child[s[i] - '0']->search(v, s, i + 1, combinaciones);
        }
    }
};

int main()
{
    int words;
    cin >> words;
    while (words)
    {
        Trie trie;
        string s;
        while (words--)
        {
            cin >> s;
            s.push_back('\0');
            trie.add(s, 0);
        }
        s = "0";
        trie.add(s,0);
        cin >> s;
        vi v(s.size() + 1, 0); // v[i] = num combinaciones para hacer s[0...i-1]
        v[0] = 1;
        for (int i = 0; i < s.size(); i++)
        {
            trie.search(v, s, i, v[i]);
        }
        cout << v[v.size() - 1] << '\n';
        cin >> words;
    }
    return 0;
}