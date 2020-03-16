#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, k = 0;
vector <int> v;
vector <ll> f;
vector <bool> used;

void gen(int m) {
	if (m == n) {
		cout << k;
		return;
	}
	for (int i = 1; i <= n; ++i)
		if (!used[i]) {
			if (v[m] > i) {
				k += f[n - m - 1];
			} else {
				used[i] = true;
				gen(m + 1);
				return;
			}
		}
}

int main() {
	freopen("perm2num.in", "r", stdin);
	freopen("perm2num.out", "w", stdout);
	cin >> n;
	f.resize(n + 1);
	v.resize(n);
	used.resize(n + 1, false);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	for (int i = 0; i < n + 1; ++i)
		f[i] = (i == 0 ? 1 : f[i - 1] * i);
	gen(0);
	return 0;
}
