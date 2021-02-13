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
#define fileio freopen("check.in", "r", stdin), freopen("check.out", "w", stdout)
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
    vector<bool> used(1u << n);
    bool subsets = true;
    bool add_bit = true;
    for (int i = 0; i < m; ++i) {
        int k = 0;
        cin >> k;
        size_t mask = 0;
        for (int j = 0; j < k; ++j) {
            size_t x;
            cin >> x;
            --x;
            mask |= (1u << x);
        }
        used[mask] = true;
    }
    for (size_t mask = 0; mask < 1u << n; ++mask) {
        if (used[mask]) {
            for (size_t submask = mask; submask > 0; submask = (submask - 1) & mask) {
                if (!used[submask]) {
                    subsets = false;
                }
            }
        }
    }
    for (size_t m1 = 0; m1 < 1u << n; ++m1) {
        if (used[m1]) {
            for (size_t m2 = 0; m2 < 1u << n; ++m2) {
                if (used[m2] && __builtin_popcount(m1) > __builtin_popcount(m2)) {
                    bool ok = false;
                    for (size_t i = 0; i < n; ++i) {
                        if ((m1 & (1u << i)) != 0 && (m2 & (1u << i)) == 0) {
                            if (used[m2 | (1u << i)]) {
                                ok = true;
                            }
                        }
                    }
                    add_bit &= ok;
                }
            }
        }
    }
    cout << (used[0] && subsets && add_bit ? "YES" : "NO");
    return 0;
}
