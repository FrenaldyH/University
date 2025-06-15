/**
 *    author:  FrenH
 *    created: 11.06.2025 11:06:15
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

int n, m, st, nd, i, u, v; ll w, ans;
vector<vector<ll>> dis (2);
vector<vector<int>> con (2);
vector<vector<vector<pair<int, ll>>>> adj (2);

void djk(int st, int op) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({dis[op][st] = 0, st});
    con[op][st] = 1;
    while(!pq.empty()) {
        tie(w, u) = pq.top(), pq.pop();
        if(dis[op][u] < w) continue;
        for(pair<int, ll> &p : adj[op][u]) {
            if(dis[op][p.fr] > dis[op][u] + p.sc) {
                pq.push({dis[op][p.fr] = dis[op][u] + p.sc, p.fr});
                con[op][p.fr] = con[op][u] + 1;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    cin >> n >> m >> st >> nd;
    for(i = 0; i < 2; i++) {
        con[i].resize(n + 1);
        adj[i].resize(n + 1);
        dis[i].resize(n + 1, LLONG_MAX);
    }
    for(i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[0][u].push_back({v, w});
        adj[1][v].push_back({u, w});
    }

    djk(st, 0);
    djk(nd, 1);

    ans = LLONG_MAX;
    for(i = 1; i <= n; i++) {
        for(auto [p, q] : adj[0][i]) {
            if(con[0][i] + con[1][p] >= (n >> 1)) {
                ans = min(ans, dis[0][i] + (q >> 1LL) + dis[1][p]);
            }
        }
    }
    cout << ans << el;
    return 0;
}

/*
tc 1
4 5 1 3 
1 2 3  
2 3 1  
1 3 7  
2 4 4  
4 3 2   

tc 2
3 3 1 3 
1 2 3
2 3 4
1 3 8 

tc 3
4 4 1 4 
1 2 1
2 3 1
3 4 1
1 4 10 

*/