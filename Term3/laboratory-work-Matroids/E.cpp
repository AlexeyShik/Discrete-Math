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
#define fileio freopen("cycles.in", "r", stdin), freopen("cycles.out", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

int main() {
    fileio;
    fastio;
    size_t n, m;
    cin >> n >> m;
    vector<bool> good(1u << n, false);
    vector<pair<ll, size_t>> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i].first;
        w[i].second = i;
    }
    sort(w.rbegin(), w.rend());
    vector<size_t> cycles(m);
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            size_t x;
            cin >> x;
            --x;
            cycles[i] |= 1u << x;
        }
    }
    ll ans = 0;
    size_t mask = 0;
    for (pair<ll, size_t> p : w) {
        bool ok = true;
        for (int i = 0; i < m; ++i) {
            ok &= (cycles[i] & (mask | (1u << p.second))) != cycles[i];
        }
        if (ok) {
            ans += p.first;
            mask |= (1u << p.second);
        }
    }
    cout << ans;
    return 0;
}
