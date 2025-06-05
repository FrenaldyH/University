/**
 *    author:  FrenH
 *    created: 05.06.2025 15:52:18
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

struct { // 1'idxd
    int union_count;
    vector<int> parent, size;
    void init(int input_size) {
        parent.resize(input_size + 1);
        size.resize(input_size + 1);
        union_count = input_size;
        for(int i = 1; i <= input_size; i++) 
            parent[i] = i;
    }
    int find(int root) {
        if(root == parent[root]) 
            return root;
        return parent[root] = find(parent[root]);
    }
    bool unite(int ra, int rb) {
        ra = find(ra);
        rb = find(rb);  
        if(ra == rb) return false;

        if(size[ra] < size[rb]) swap(ra, rb);
        
        size[ra] += size[rb];
        parent[rb] = ra;
        union_count--;
        return true;
    }
} dsu;

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

bool comp(vector<int> &a, vector<int> &b) {
    return a[2] < b[2];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int n, m, j, i, sum;
    cin >> n >> m;
    dsu.init(n);
    vector<vector<int>> edge(m, vector<int> (3));
    for(i = 0; i < m; i++) {
        for(j = 0; j < 3; j++) {
            cin >> edge[i][j];
        }
    }
    sort(all(edge), comp);
    /* fp(i, 0, m) {
        fp(j, 0, 3) 
            cout << edge[i][j] << ' ';
        cout << el;
    } */
    sum = 0;
    for(i = 0; i < m; i++) {
        if(dsu.unite(edge[i][0], edge[i][1])) {
            sum += edge[i][2];
        }
    }
    cin >> n;
    if(n < sum) {
        cout << "Waduh budgetnya kurang bos\n";
    } else {
        cout << "Budgetnya cukup Bos! Ada sisa " << n - sum << el;
    }
    return 0;
}