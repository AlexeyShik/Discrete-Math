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
#define fileio freopen("schedule.in", "r", stdin), freopen("schedule.out", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

bool cmp(pll a, pll b) {
    return a.first < b.first || (a.first == b.first && a.second > b.second);
}

int main() {
    fileio;
    fastio;
    int n;
    cin >> n;
    vector<pll> tasks(n);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].first >> tasks[i].second;
        ans += tasks[i].second;
    }
    sort(tasks.begin(), tasks.end(), cmp);
    multiset<ll> base;
    for (pll task : tasks) {
        if (base.size() < task.first) {
            base.insert(task.second);
        } else if (*base.begin() < task.second) {
            base.erase(*base.begin());
            base.insert(task.second);
        }
    }
    for (ll x : base) {
        ans -= x;
    }
    cout << ans;
    return 0;
}
