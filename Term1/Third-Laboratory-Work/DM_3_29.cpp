#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("nextpartition.in", "r", stdin);
	freopen("nextpartition.out", "w", stdout);
	string s;
	cin >> s;
	int n = 0, t;
	for (t = 0; t < (int)s.size() && s[t] != '='; ++t)
		n = 10 * n + (s[t] - '0');
	vector <int> v(1, 0);
	++t;
	for (; t < (int)s.size(); ++t) {
		if (s[t] == '+') {
			v.push_back(0);
		} else {
			v[v.size() - 1] = v[v.size() - 1] * 10 + (s[t] - '0');
		}
	}
	int m = (int)v.size();
	if (m == 1) {
		cout << "No solution";
		return 0;
	}
	v[m - 1]--;
	v[m - 2]++;
	if (v[m - 1] < v[m - 2]) {
		v[m - 2] += v[m - 1];
		v.pop_back();
		m--;
	} else {
		while (v[m - 1] >= 2 * v[m - 2]) {
			v.push_back(v[m - 1] - v[m - 2]);
			++m;
			v[m - 2] = v[m - 3];
		}
	}
	cout << n << '=' << v[0];
	for (int i = 1; i < m; ++i)
		cout << '+' << v[i];
	return 0;
}
