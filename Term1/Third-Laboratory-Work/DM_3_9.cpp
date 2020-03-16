#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, k;
vector <bool> ans;

void gen(int m, int bal) {
	if (m == 2 * n) {
		for (int x : ans)
			cout << (x ? ')' : '(');
		cout << endl;
		return;
	}
	if (bal + 1 <= 2 * n - m) {
		ans[m] = false;
		gen(m + 1, bal + 1);
	}
	if (bal - 1 >= 0) {
		ans[m] = true;
		gen(m + 1, bal - 1);
	}
}

int main() {
	//freopen("brackets.in", "r", stdin);
	//freopen("brackets.out", "w", stdout);
	cin >> n;
	ans.resize(2 * n, false);
	gen(0, 0);
	return 0;
}
