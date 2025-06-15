/**
 *    author:  FrenH
 *    created: 12.06.2025 21:00:01
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
    
    char c;
    ll n, m, i, j, k;
    vector<pair<int, char>> siv(26);
    for(cin >> n >> m; n--;) {
        cin >> c;
        siv[(siv[c - 65].sc = c) - 65].fr++;
    }
    sort(all(siv), greater());

    /* for(i = 0; i < 26; i++) {
        cout << siv[i].fr << ' ' << siv[i].sc << el;
    } */
    
    vector<int> cd(26);
    for(i = 1; siv[0].fr; i++) {
        for(j = 0; j < 26; j++) {
            if(siv[j].fr && i > cd[siv[j].sc - 65]) {
                cd[siv[j].sc - 65] = m + i;
                siv[j].fr--;
                while(j < 25 && siv[j].fr < siv[j + 1].fr) 
                    swap(siv[j], siv[j + 1]), j++;
                break;
            }
        }
    }
    cout << i - 1 << el;
    return 0;
}

// A B C A B C A B C D . . D . . D