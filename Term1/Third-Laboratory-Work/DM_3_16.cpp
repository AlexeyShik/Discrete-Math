#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, m, k = 0;
vector <int> v;
vector <vector <ll> > c;

void gen(int p) {
	if (p == m) {
		cout << k;
		return;
	}
	for (int t = (p == 0 ? 1 : v[p - 1] + 1); t <= n; ++t) {
		ll cnt = c[n - t][m - p - 1];
		if (t < v[p]) {
			k += cnt;
		} else {
			gen(p + 1);
			return;
		}
	}
}

int main() {
	freopen("choose2num.in", "r", stdin);
	freopen("choose2num.out", "w", stdout);
	cin >> n >> m;
	c.resize(n + 1, vector <ll> (m + 1, 0));
	v.resize(m);
	for (int i = 0; i <= n; ++i)
		c[i][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	for (int i = 0; i < m; ++i)
		cin >> v[i];
	gen(0);
	return 0;
}
