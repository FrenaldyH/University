/**
 *    author:  FrenH
 *    created: 10.06.2025 21:22:52
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
    
    deque<int> dq;
    int n, num;
    string s;
    for(cin >> n; n--;) {
        cin >> s;
        if(s == "tambahDepan") {
            cin >> num;
            dq.push_front(num);
        } else 
        if(s == "tambahBelakang") {
            cin >> num;
            dq.push_back(num);
        } else
        if(s == "depan") {
            if(!dq.empty()) {
                cout << dq.front();
                dq.pop_front();
            }
            cout << el;
        } else 
        if(s == "belakang") {
            if(!dq.empty()) {
                cout << dq.back();
                dq.pop_back();
            }
            cout << el;
        } else {
            if(!dq.empty())
                swap(dq.front(), dq.back());
        }
    }
    return 0;
}

/*
tc 1
14
tambahDepan 101
tambahBelakang 3
balik
depan
tambahBelakang 99
tambahDepan 23
balik
belakang
balik
depan
belakang
depan
tambahDepan 10
belakang
*/