#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, k;
vector <int> ans;
map <int, bool> used;

void gen(int m) {
	if (m == k) {
		for (int x : ans)
			cout << x << ' ';
		cout << endl;
		return;
	}
	for (int x = (m == 0 ? 1 : ans[m - 1] + 1); x <= n; ++x)
		if (!used[x] && n - x >= k - m - 1) {
			ans[m] = x;
			used[x] = true;
			gen(m + 1);
			used[x] = false;
		}
}

int main() {
	freopen("choose.in", "r", stdin);
	freopen("choose.out", "w", stdout);
	cin >> n >> k;
	ans.resize(k, 0);
	gen(0);
	return 0;
}
