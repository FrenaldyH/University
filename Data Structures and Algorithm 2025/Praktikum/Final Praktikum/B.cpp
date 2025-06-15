/**
 *    author:  FrenH
 *    created: 11.06.2025 00:34:52
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
    
    int n, i;
    cin >> n;

    vector<ll> h(n + 1), w(n + 1);
    fp(i, 1, n + 1) cin >> h[i];
    fp(i, 1, n + 1) {
        cin >> w[i], w[i] += w[i - 1];
    }

    ll ans = 0, tp;
    stack<pll> stk;
    h.push_back(0);
    stk.push({-1, 0});
    for(i = 1; i <= n + 1; i++) {
        while(!stk.empty() && stk.top().fr > h[i]) {
            tp = stk.top().fr; stk.pop();
            ans = max(ans, tp * (w[i - 1] - w[stk.top().sc]));
        }
        stk.push({h[i], i});
    }
    cout << ans << el;
    return 0;
}

/*
tc 1
3
24 58 16
1 1 1
*/