#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

vector<vector<int>> g;

bool cmp(int u, int v) {
    if (g[u - 1][v - 1] == -1)  {
        cout << 1 << ' ' << u << ' ' << v << endl;
        string res;
        cin >> res;
        g[u - 1][v - 1] = res == "YES";
        g[v - 1][u - 1] = res == "NO";
    }
    return g[u - 1][v - 1];
}

int main() {
    fastio;
    int n;
    cin >> n;
    g.resize(n, vector<int> (n, -1));
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = i + 1;
    }
    stable_sort(ans.begin(), ans.end(), cmp);
    cout << 0 << ' ';
    for (int x : ans) {
        cout << x << ' ';
    }
    return 0;
}
