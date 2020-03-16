#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, k;
vector <vector <ll> > f;
vector <char> ans;

void gen(int m, int b) {
	if (m == 2 * n) {
		for (char c : ans)
			cout << c;
		return;
	}
	if (f[2 * n - m - 1][b + 1] > k) {
		ans[m] = '(';
		gen(m + 1, b + 1);
		return;
	}
	ans[m] = ')';
	k -= f[2 * n - m - 1][b + 1];
	gen(m + 1, b - 1);
}

int main() {
	freopen("num2brackets.in", "r", stdin);
	freopen("num2brackets.out", "w", stdout);	
	cin >> n >> k;
	f.resize(2 * n + 1, vector <ll> (n + 2, 0));
	f[1][1] = 1;
	for (int i = 1; i <= 2 * n; ++i) {
		for (int b = 0; b <= n; ++b) {
			if (b > 0)
				f[i][b] += f[i - 1][b - 1];
			if (b < n)
				f[i][b] += f[i - 1][b + 1];
		}
	}
	ans.resize(2 * n);
	gen(0, 0);
	return 0;
}
