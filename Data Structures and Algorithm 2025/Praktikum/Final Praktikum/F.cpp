/**
 *    author:  FrenH
 *    created: 11.06.2025 10:35:26
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

int stringtoint(string s) {
    int num = 0, min = (s.front() == '-' ? 1 : 0), i;
    for(i = min; i < s.length(); i++) {
        num = num * 10 + (s[i] - 48);
    }
    return num * (min ? -1 : 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    string s, t;
    vector<ll> v;
    getline(cin, s);

    s += ' ', t = "";
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == ' ') {
            if(t.length() > 1) 
                v.push_back(stringtoint(t));
            else {
                switch (t[0]) {
                case '+':
                    v.push_back(v[v.size() - 1] + v[v.size() - 2]);
                    break;
                case 'D':
                    v.push_back(v.back() * 2LL);
                    break;
                case 'C':
                    v.pop_back();
                    break;
                default:
                    v.push_back(t[0] - 48);
                    break;
                }
            }
            t.clear();
        } 
        else t.push_back(s[i]);
    }
    ll sum = 0;
    for(ll &i : v)
        sum += i;
    cout << sum << el;
    return 0;   
}