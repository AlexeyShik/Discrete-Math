#include <iostream>
#include <vector>
#include <map>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

vector<ll> cnt;
vector<vector<bool>> mg;
vector<vector<int>> g;

void gen(int i, vector<vector<int>> &v) {
    if (i == g.size()) {
        ++cnt[v.size()];
        return;
    }
    for (int j = 0; j < v.size(); ++j) {
        bool can = true;
        for (int u : v[j]) {
            if (mg[i][u]) {
                can = false;
                break;
            }
        }
        if (can) {
            v[j].push_back(i);
            gen(i + 1, v);
            v[j].pop_back();
        }
    }
    v.emplace_back(1, i);
    gen(i + 1, v);
    v.pop_back();
}

vector<ll> &operator+=(vector<ll> &th, vector<ll> &oth) {
    for (int i = 0; i < th.size(); ++i) {
        th[i] += oth[i];
    }
    return th;
}

vector<ll> &operator*(vector<ll> &th, ll c) {
    for (ll &elem : th) {
        elem *= c;
    }
    return th;
}

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    g.resize(n);
    mg.resize(n, vector<bool>(n));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
        mg[u][v] = mg[v][u] = true;
    }
    cnt.resize(n + 1, 0);
    vector<vector<int>> v;
    gen(0, v);
    map<int, vector<ll>> mp = {
            {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
            {1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}},
            {2, {0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0}},
            {3, {0, 0, 0, 0, 0, 0, 0, 1, -3, 2, 0}},
            {4, {0, 0, 0, 0, 0, 0, 1, -6, 11, -6, 0}},
            {5, {0, 0, 0, 0, 0, 1, -10, 35, -50, 24, 0}},
            {6, {0, 0, 0, 0, 1, -15, 85, -225, 274, -120, 0}},
            {7, {0, 0, 0, 1, -21, 175, -735, 1624, -1764, 720, 0}},
            {8, {0, 0, 1, -28, 322, -1960, 6769, -13132, 13068, -5040, 0}},
            {9, {0, 1, -36, 546, -4536, 22449, -67284, 118124, -109584, 40320, 0}},
            {10, {1, -45, 870, -9450, 63273, -269325, 723680, -1172700, 1026576, -362880, 0}}
    };
    vector<ll> ans = mp[0];
    for (int i = 1; i <= n; ++i) {
        ans += mp[i] * cnt[i];
    }
    int d = -1;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] != 0) {
            d = ans.size() - i - 1;
            break;
        }
    }
    cout << d << endl;
    for (int i = ans.size() - d - 1; i < ans.size(); ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}
