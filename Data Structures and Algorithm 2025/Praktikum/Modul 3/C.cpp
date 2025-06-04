/**
 *    author:  FrenH
 *    created: 05.06.2025 01:24:41
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

map<ll, vector<pll>> adj;
set<pll> visEdge;
bool found;
ll target;

void dfs(ll node, ll curW = 0) {
    if(curW > target || found) return;
    if(curW == target) {
        found = true;
        return;
    }
    for(auto &h : adj[node]) {
        if(visEdge.count({min(node, h.fr), max(node, h.fr)})) 
            continue;
        visEdge.insert({min(node, h.fr), max(node, h.fr)});
        dfs(h.fr, curW + h.sc);
        visEdge.erase({min(node, h.fr), max(node, h.fr)});
        if(found) return;
    }
}

void solve() {
    adj.clear();
    found = false;
    ll u, v, w;
    while(cin >> u >> v >> w) {
        if(!u && !v && !w) break;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    cin >> target;
    for(auto &h : adj) {
        dfs(h.fr);
        if(found) break;
    }
    cout << (found ? "YES" : "NO") << el;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int tc;
    for(cin >> tc; tc--;) {
        solve();
    }
    
    return 0;
}