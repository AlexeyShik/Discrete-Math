#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("bwt.in", "r", stdin);
	freopen("bwt.out", "w", stdout);
	string s;
	cin >> s;
	int n = s.size();
	s += s;
	multiset <string> v;
	for (int i = 0; i < n; ++i)
		v.insert(s.substr(i, n));
	string ans = "";
	for (auto x : v)
		ans += x[n - 1];
	cout << ans;
	return 0;
}
