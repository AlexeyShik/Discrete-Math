#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n;
vector <int> ans;

void gen(int m) {
	if (m == n) {
		cout << ans[0];
		for (int i = 1; i < (int)ans.size(); ++i)
			cout << '+' << ans[i];
		cout << endl;
		return;
	}
	for (int x = (ans.empty() ? 1 : ans[ans.size() - 1]); x + m <= n; ++x) {
		ans.push_back(x);
		gen(m + x);
		ans.pop_back();
	}
}

int main() {
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
	cin >> n;
	gen(0);
	return 0;
}
