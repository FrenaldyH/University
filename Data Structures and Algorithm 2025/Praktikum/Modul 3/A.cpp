/**
 *    author:  FrenH
 *    created: 31.05.2025 10:40:01
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

vector<vector<int>> adj;
vector<bool> dis;
vector<int> dist;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int n, m, l, s, a, b, i;
    cin >> n >> m >> l >> s;

    adj.resize(n);
    dis.resize(n);
    dist.resize(n);
    for(i = 0; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(i = 0; i < n; i++)
        dist[i] = -1;
    queue<int> bfs;
    bfs.push(s);
    dist[s] = 0;
    dis[s] = true;
    while(!bfs.empty()) {
        b = bfs.front(), bfs.pop();
        for(int &ch : adj[b]) {
            if(!dis[ch]) {
                bfs.push(ch);
                dist[ch] = dist[b] + 1;
                dis[ch] = true;
            }
        }
    }
    bool ok = false;
    for(i = 0; i < n; i++) {
        if(dist[i] == l) {
            cout << i << el;
            ok = true;
        }
    }
    if(!ok) cout << "Not Found" << el;
    return 0;
}

/*
    3 2 1 0
    0 1
    0 2
*/