#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, k = 0;
vector <vector <ll> > f;
string s;

void gen(int m, int b) {
	if (m == 2 * n) {
		cout << k;
		return;
	}
	if (s[m] == '(') {
		gen(m + 1, b + 1);
		return;
	}
	k += f[2 * n - m - 1][b + 1];
	gen(m + 1, b - 1);
}

int main() {
	//freopen("brackets2num.in", "r", stdin);
	//freopen("brackets2num.out", "w", stdout);	
	cin >> s;
	n = (int)s.size() / 2;
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
	gen(0, 0);
	return 0;
}
