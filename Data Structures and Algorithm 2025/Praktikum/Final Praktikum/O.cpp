/**
 *    author:  FrenH
 *    created: 10.06.2025 23:18:52
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
    
    int n, i, l, r, x, root = 0;
    bool ans = true;
    stack<int> stk;
    for(cin >> n; n--;) {
        cin >> x;
        if(x < root) ans = false;
        while(!stk.empty() && stk.top() < x) {
            root = stk.top();
            stk.pop();
        }
        stk.push(x);
    }
    cout << "ini " << (ans ? "" : "bukan ") << "pohon" << el;
    return 0;
}