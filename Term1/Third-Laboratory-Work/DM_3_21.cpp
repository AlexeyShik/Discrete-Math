#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, k;
vector <vector <ll> > f;
vector <int> ans;

void gen(int m) {
	if (m == n) {
		cout << ans[0];
		for (int i = 1; i < (int)ans.size(); ++i)
			cout << '+' << ans[i];
		return;
	}
	for (int i = (m == 0 ? 1 : ans[ans.size() - 1]); i <= n; ++i) {
		if (m + i <= n) {
			ll cnt = f[n - m - i][i];
			if (cnt > k) {
				ans.push_back(i);
				gen(m + i);
				return;
			}
			k -= cnt;
		}
	}
}

int main() {
	freopen("num2part.in", "r", stdin);
	freopen("num2part.out", "w", stdout);	
	cin >> n >> k;
	f.resize(n + 1, vector <ll> (n + 1, 0));
	for (int i = 0; i <= n; ++i)
		f[0][i] = f[i][i] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = n - 1; j > 0; --j) {
			f[i][j] = f[i][j + 1];
			if (j <= i)
				f[i][j] += f[i - j][j];
		}
	gen(0);
	return 0;
}
