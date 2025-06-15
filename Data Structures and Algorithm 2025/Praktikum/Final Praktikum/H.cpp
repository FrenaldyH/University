/**
 *    author:  FrenH
 *    created: 10.06.2025 21:39:43
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
    
    vector<int> a(26, 0);
    string s; cin >> s;

    for(int i = 0; i < s.length(); i++)
        a[s[i] - 97]++;
    for(int i = 0; i < s.length(); i++) {
        if(a[s[i] - 97] == 1) {
            cout << i << el;
            return 0;
        }
    }
    cout << -1 << el;
    return 0;
}