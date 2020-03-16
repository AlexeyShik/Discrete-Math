#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, k;
vector <int> ans;
vector <ll> f;
vector <bool> used;

void gen(int m) {
	if (m == n) {
		for (auto x : ans)
			cout << x << ' ';
		return;
	}
	for (int i = 1; i <= n; ++i)
		if (!used[i]) {
			if (f[n - m - 1] <= k) {
				k -= f[n - m - 1];
			} else {
				used[i] = true;
				ans.push_back(i);
				gen(m + 1);
				return;
			}
		}
}

int main() {
	freopen("num2perm.in", "r", stdin);
	freopen("num2perm.out", "w", stdout);
	cin >> n >> k;
	f.resize(n + 1);
	used.resize(n + 1, false);
	for (int i = 0; i < n + 1; ++i)
		f[i] = (i == 0 ? 1 : f[i - 1] * i);
	gen(0);
	return 0;
}
