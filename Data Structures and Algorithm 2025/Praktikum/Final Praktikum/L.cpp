/**
 *    author:  FrenH
 *    created: 13.06.2025 16:57:02
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
    
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_rev(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj_rev[v].push_back(u);
    }

    int num_masks = 1 << n;
    vector<vector<long long>> dp(num_masks, vector<long long>(n + 1, 0));

    dp[1][1] = 1;

    for (int mask = 2; mask < num_masks; ++mask) {
        for (int u = 1; u <= n; ++u) {
            if (mask & (1 << (u - 1))) {
                int prev_mask = mask ^ (1 << (u - 1));
                for (int v : adj_rev[u]) {
                    if (prev_mask & (1 << (v - 1))) {
                        dp[mask][u] = (dp[mask][u] + dp[prev_mask][v]) % mod;
                    }
                }
            }
        }
    }

    int final_mask = (1 << n) - 1;
    cout << dp[final_mask][n] << el;
    
    return 0;
}