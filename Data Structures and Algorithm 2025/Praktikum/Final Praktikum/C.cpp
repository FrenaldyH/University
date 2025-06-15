/**
 *    author:  FrenH
 *    created: 10.06.2025 20:18:55
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
    
    int n, i, j, l, r;
    ll ans = 0;

    cin >> n;
    vector<int> v(n);
    fp(i, 0, n) cin >> v[i];

    l = v[i = 0], r = v[j = n - 1];
    while(i < j) {
        if(l <= r) {
            if(v[++i] < l) 
                ans += l - v[i];
            else l = v[i];
        } else {
            if(v[--j] < r) 
                ans += r - v[j];
            else r = v[j];
        }
    }
    cout << ans << el;
    return 0;
}

/*
tc 1
7
3 0 1 0 4 0 2

tc 2
5
1 0 3 4 2
*/