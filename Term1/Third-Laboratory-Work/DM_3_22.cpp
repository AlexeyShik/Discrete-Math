#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n = 0, k = 0;
vector <vector <ll> > f;
string s;
vector <int> v;

void gen(int m, int sum) {
	if (sum == n) {
		cout << k;
		return;
	}
	for (int i = m == 0 ? 1 : v[m - 1]; i < v[m]; ++i)
		k += f[n - sum - i][i];	
	gen(m + 1, sum + v[m]);
}

int main() {
	freopen("part2num.in", "r", stdin);
	freopen("part2num.out", "w", stdout);	
	cin >> s;
	s = s + '+';
	int cur = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		if (s[i] == '+') {
			v.push_back(cur);
			cur = 0;
		} else {
			cur = 10 * cur + (int)(s[i] - '0');
		}
	}
	for (int i = 0; i < (int)v.size(); ++i)
		n += v[i];
	f.resize(n + 1, vector <ll> (n + 1, 0));
	for (int i = 0; i <= n; ++i)
		f[0][i] = f[i][i] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = n - 1; j > 0; --j) {
			f[i][j] = f[i][j + 1];
			if (j <= i)
				f[i][j] += f[i - j][j];
		}
	gen(0, 0);
	return 0;
}
