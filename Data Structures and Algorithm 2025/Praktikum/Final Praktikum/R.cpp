/**
 *    author:  FrenH
 *    created: 10.06.2025 23:51:46
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
mod = 1000;

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

vector<vector<bool>> vis;
vector<vector<char>> mat;
vector<pii> step {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

int n, m, tp, a, b, c;
int floodFill(int y, int x) {
    int count = 1;
    vis[y][x] = true;
    for(int i = 0; i < 4; i++) {
        int ty = y + step[i].fr, 
            tx = x + step[i].sc;
        if(ty < 0 || tx < 0 || ty >= n || tx >= m || vis[ty][tx] || mat[ty][tx] == '#') 
            continue;
        count += floodFill(ty, tx);
    }
    return count;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int i, j;
    cin >> n >> m;
    mat.resize(n, vector<char> (m));
    vis.resize(n, vector<bool> (m));
    fp(i, 0, n) 
        fp(j, 0, m) 
            cin >> mat[i][j];

    a = b = c = 0;
    fp(i, 0, n) {
        fp(j, 0, m) {
            if(!vis[i][j] && mat[i][j] == '+') {
                tp = floodFill(i, j);
                a++, c += !(tp & 1);
                b = max(b, tp);
            }
        }
    }
    cout << a << ' ' << b << ' ' << c << el;
    return 0;
}

/*
tc 1
5 5
+####
#++##
##+##
###++
###++

tc 2
4 4
#++#
####
##+#
#++#
*/