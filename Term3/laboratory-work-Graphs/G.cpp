#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

inline void dfs(int u, vector<int> &order, vector<bool> &used, vector<vector<int>> &g) {
    used[u] = true;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs(v, order, used, g);
        }
    }
    order.push_back(u);
}

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    int k = 0;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        k = max(k, (int) g[i].size());
    }
    if (k % 2 == 0) {
        ++k;
    }
    int s = -1;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() < k) {
            s = i;
            break;
        }
    }
    vector<int> order;
    vector<bool> used(n, false);
    dfs(s, order, used, g);
    vector<int> color(n, -1);
    for (int u : order) {
        unordered_set<int> forbidden;
        for (int v : g[u]) {
            if (color[v] != -1) {
                forbidden.insert(color[v]);
            }
        }
        for (int i = 0; i < k; ++i) {
            if (forbidden.find(i) == forbidden.end()) {
                color[u] = i;
                break;
            }
        }
    }
    cout << k << endl;
    for (int x : color) {
        cout << x + 1 << endl;
    }
    return 0;
}
