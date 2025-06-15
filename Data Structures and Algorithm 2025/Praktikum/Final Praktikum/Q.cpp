/**
 *    author:  FrenH
 *    created: 12.06.2025 20:32:07
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

struct { 
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
    
    unordered_map<string, int> mp;
    int n, m, E, p = 0;

    cin >> n;
    dsu.init(n);
    string a, b;
    for(cin >> m; m--;) {
        cin >> a >> b;
        if(!mp.count(a)) 
            mp[a] =++ p;
        if(!mp.count(b))
            mp[b] =++ p;
        dsu.unite(mp[a], mp[b]);
    }
    cin >> E;
    if (E > dsu.union_count) {
        cout << "You tied the loose ends and reached her.\n";
    }
    else if (E == dsu.union_count) {
        cout << "You tied the loose ends but couldn't reach her.\n";
    }
    else { 
        cout << "You didn't tie the loose ends. She remains out of reach.";
    }
    return 0;
}