/**
 *    author:  FrenH
 *    created: 05.06.2025 17:05:38
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
    
    int n, st, u, v, w, ans, i;
    cin >> n >> st;
    vector<vector<pii>> adj(n + 1);
    vector<int> dis(n + 1, pinf);

    while(cin >> u >> v >> w) {
        if(!u && !v && !w) break;
        adj[u].push_back({v, w});
    }

    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push({dis[st] = 0, st});
    while(!pq.empty()) {
        tie(w, u) = pq.top(), pq.pop();
        if(dis[u] < w) continue;
        for(pii &p : adj[u]) {
            if(dis[p.fr] > dis[u] + p.sc) {
                pq.push({dis[p.fr] = dis[u] + p.sc, p.fr});
            }
        }
    }
    
    ans = 0;
    for(i = 1; i <= n; i++) 
        ans = max(ans, dis[i]);
    cout << (ans == pinf ? -1 : ans) << el;
    
    return 0;
}

/*

*/