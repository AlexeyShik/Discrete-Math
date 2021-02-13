#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <cassert>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("matching.in", "r", stdin), freopen("matching.out", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

bool cmp(pll &a, pll &b) {
    return a.first > b.first;
}

inline bool dfs(int u, int t, vector<int> &used, vector<vector<int>> &g, vector<int> &mt) {
    used[u] = t;
    bool b = false;
    for (int v : g[u]) {
        if (mt[v] == -1) {
            mt[u] = v;
            mt[v] = u;
            return true;
        }
        if (used[mt[v]] != t) {
            b |= dfs(mt[v], t, used, g, mt);
            if (b) {
                mt[u] = v;
                mt[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    fileio;
    fastio;
    int n;
    cin >> n;
    vector<pll> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i].first;
        w[i].first *= w[i].first;
        w[i].second = i;
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int u;
            cin >> u;
            --u;
            g[i].push_back(u + n);
        }
    }
    sort(w.begin(), w.end(), cmp);
    vector<int> mt(2 * n, -1);
    vector<int> used(n, -1);
    for (int i = 0; i < n; ++i) {
        dfs(w[i].second, i, used, g, mt);
    }
    for (int i = 0; i < n; ++i) {
        cout << (mt[i] == -1 ? 0 : mt[i] + 1 - n) << ' ';
    }
    return 0;
}
