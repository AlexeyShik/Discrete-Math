#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("allvectors.in", "r", stdin);
	freopen("allvectors.out", "w", stdout);
	int n;
	cin >> n;
	vector <bool> ans(n);
	for (int i = 0; i < (1 << n); ++i) {
		for (auto x : ans)
			cout << x;
		cout << endl;
		for (int j = n - 1; j >= 0; --j)
			if (ans[j]) {
				ans[j] = false;
			} else {
				ans[j] = true;
				break;
			}
	}
	return 0;
}
