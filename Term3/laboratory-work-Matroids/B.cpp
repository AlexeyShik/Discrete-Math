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
#define fileio freopen("destroy.in", "r", stdin), freopen("destroy.out", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

struct edge {
    int u;
    int v;
    ll w;
    int id;
};

bool cmp(edge a, edge b) {
    return a.w > b.w;
}

vector<int> dsu;

int get(int u) {
    return dsu[u] = dsu[u] == u ? u : get(dsu[u]);
}

void join(int u, int v) {
    u = get(u);
    v = get(v);
    if (rand() % 2) {
        swap(u, v);
    }
    dsu[u] = v;
}

int main() {
    fileio;
    fastio;
    int n, m;
    ll s, sum;
    cin >> n >> m >> s;
    sum = -s;
    vector<edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        sum += w;
        --u, --v;
        edges.push_back({u, v, w, i});
    }
    sort(edges.begin(), edges.end(), cmp);
    vector<bool> chosen(m, false);
    dsu.resize(n);
    for (int i = 0; i < n; ++i) {
        dsu[i] = i;
    }
    for (edge &e : edges) {
        if (get(e.u) != get(e.v)) {
            join(e.u, e.v);
            sum -= e.w;
            chosen[e.id] = true;
        }
    }
    for (edge &e : edges) {
        if (sum > 0 && !chosen[e.id]) {
            sum -= e.w;
            chosen[e.id] = true;
        }
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (!chosen[i]) {
            ++cnt;
        }
    }
    cout << cnt << endl;
    for (int i = 0; i < m; ++i) {
        if (!chosen[i]) {
            cout << i + 1 << ' ';
        }
    }
    return 0;
}
