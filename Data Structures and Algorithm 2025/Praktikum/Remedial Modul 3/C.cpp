/**
 *    author:  FrenH
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
    
    ll n, m, u, v, w, i, j, st, nd, tc;
    cin >> n;
    
    vector<vector<pll>> adj(n);
    vector<ll> dis(n), par(n);
    for(cin >> m; m--;) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    for(cin >> tc; tc--;) {
        cin >> st;
        if(st >= n) {
            cout << "Invalid starting point" << el;
            continue;
        }

        fp(i, 0, n) dis[i] = LLONG_MAX;
        fp(i, 0, n) par[i] = -1;
        priority_queue<pll, vector<pll>, greater<pll> > pq;
        pq.push({dis[st] = 0, st});
        while(!pq.empty()) {
            tie(w, u) = pq.top(), pq.pop();
            if(dis[u] < w) continue;
            for(pll &p : adj[u]) {
                if(dis[p.fr] > dis[u] + p.sc) {
                    pq.push({dis[p.fr] = dis[u] + p.sc, p.fr});
                    par[p.fr] = u;
                }
            }
        }
        for(i = 0; i < n; i++) {
            if(i == st) continue;
            cout << "---From " << st << " to " << i << "---" << el;
            stack<int> ans; u = i;
            while(u != -1) {
                ans.push(u), u = par[u];
            }
            while(!ans.empty()) {
                cout << ans.top(), ans.pop();
                if(!ans.empty()) cout << " - ";
            }
            cout << el;
        }
    }
}
// source – a – b – c – destination