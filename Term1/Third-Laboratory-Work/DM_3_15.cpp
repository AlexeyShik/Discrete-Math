#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, m, k;
vector <int> ans;
vector <vector <ll> > c;
vector <bool> used;

void gen(int p) {
	if (p == m) {
		for (int x : ans)
			cout << x << ' ';
		return;
	}
	for (int t = (p == 0 ? 1 : ans[p - 1] + 1); t <= n; ++t) {
		ll cnt = c[n - t][m - p - 1];
		if (cnt <= k) {
			k -= cnt;
		} else {
			used[t] = true;
			ans.push_back(t);
			gen(p + 1);
			return;
		}
	}
}

int main() {
	freopen("num2choose.in", "r", stdin);
	freopen("num2choose.out", "w", stdout);
	cin >> n >> m >> k;
	c.resize(n + 1, vector <ll> (m + 1, 0));
	used.resize(n + 1, false);
	for (int i = 0; i <= n; ++i)
		c[i][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	gen(0);
	return 0;
}
