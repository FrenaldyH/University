/**
 *    author:  FrenH
 *    created: 05.06.2025 16:03:35
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

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int n, m, st, nd, i, cur, u, v;
    cin >> n >> m >> st >> nd;

    vector<vector<int>> adj(n);
    while(m--) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dis(n, pinf);
    vector<bool> vis(n);
    queue<int> bfs;
    bfs.push(st);
    dis[st] = 0;
    vis[st] = 1;
    while(!bfs.empty()) {
        cur = bfs.front(), bfs.pop();
        for(int &ch : adj[cur]) {
            if(!vis[ch]) {
                dis[ch] = dis[cur] + (vis[ch] = 1); 
            }
        }
    }
    cout << (dis[nd] == pinf ? -1 : dis[nd]) << el;
    return 0;
}