#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n;
vector <int> ans;
map <int, bool> used;

void gen(int m) {
	if (m == n) {
		for (int x : ans)
			cout << x << ' ';
		cout << endl;
		return;
	}
	for (int x = 1; x <= n; ++x)
		if (!used[x]) {
			ans[m] = x;
			used[x] = true;
			gen(m + 1);
			used[x] = false;
		}
}

int main() {
	freopen("permutations.in", "r", stdin);
	freopen("permutations.out", "w", stdout);
	cin >> n;
	ans.resize(n, 0);
	gen(0);
	return 0;
}
