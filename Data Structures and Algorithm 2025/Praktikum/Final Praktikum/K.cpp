/**
 *    author:  FrenH
 *    created: 11.06.2025 13:09:55
**/

#include <bits/stdc++.h>
using namespace std;

//Shortcut
#define fp(i, l, r)     for(i = l; i < r; i++)
#define ms(x, y)        memset(x, y, sizeof(x))
#define all(x)          x.begin(), x.end()
#define sc              second
#define fr              first
#define el              '\n'

using dd                = double;
using ll                = long long;
using ull               = unsigned long long;
using pii               = pair<int, int>;
using pll               = pair<ll, ll>;

// Global variabel
const int S = 1e5,
minf = INT_MIN, 
pinf = INT_MAX,
mod = 1e9 + 7;

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

struct { // 1'idxd
    int union_count;
    vector<int> parent, size;
    void init(int input_size) {
        parent.resize(input_size + 1);
        size.resize(input_size + 1);
        union_count = input_size;
        for(int i = 1; i <= input_size; i++) 
            parent[i] = i;
    }
    int find(int root) {
        if(root == parent[root]) 
            return root;
        return parent[root] = find(parent[root]);
    }
    bool unite(int ra, int rb) {
        ra = find(ra);
        rb = find(rb);  
        if(ra == rb) return false;

        if(size[ra] < size[rb]) swap(ra, rb);

        size[ra] += size[rb];
        parent[rb] = ra;
        union_count--;
        return true;
    }
} dsu;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int n, i, j, k;
    string s[3];
    cin >> n;
    
    k = 0;
    unordered_map<string, int> hash;
    vector<vector<int>> v(n, vector<int> (3));
    fp(i, 0, n) {
        fp(j, 0, 3) {
            cin >> s[j];
            if(j) {
                if(!hash.count(s[j])) 
                    hash[s[j]] = ++k;
                v[i][j] = hash[s[j]];
            } 
            else if(s[0] == "RECRUIT") 
                v[i][j] = 0;
            else if(s[0] == "CHECK") 
                v[i][j] = 1;
            else v[i][j] = 2;
        }
    }

    dsu.init(k);
    fp(i, 0, n) {
        if(v[i][0] & 1) {
            cout << (dsu.find(v[i][1]) == dsu.find(v[i][2]) ? "YES" : "NO") << el;
        } else{
            dsu.unite(v[i][1], v[i][2]);
        }
    }
    return 0;
}