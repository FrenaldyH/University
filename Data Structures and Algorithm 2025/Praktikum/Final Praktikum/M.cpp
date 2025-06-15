/**
 *    author:  FrenH
 *    created: 10.06.2025 23:07:56
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
    
    int n, num;
    string a, b;
    map<string, int> mp;
    for(cin >> n; n--;) {
        cin >> a >> b >> num;
        if(a == "ADD") 
            mp[b] += num;
        else {
            if(!mp.count(b)) {
                cout << "item not found" << el;
            } else 
            if(mp[b] < num) {
                cout << "not enough stock" << el;
            } else {
                cout << "SUCCESS" << el;
                mp[b] -= num;
            }
        }
    }
    return 0;
}

/*
tc 1
9
ADD mango 20
ADD rambutan 15
SELL mango 5
SELL durian 1
ADD mango 10
SELL rambutan 20
SELL mango 25
ADD salak 30
SELL mango 1
*/