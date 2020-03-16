#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, k;
vector <vector <ll> > f;
vector <char> ans;
vector <ll> pows;
stack <char> last;

void gen(int m, int b) {
	if (m == 2 * n) {
		for (char c : ans)
			cout << c;
		return;
	}
	
	if (b + 1 <= n && f[2 * n - m - 1][b + 1] * pows[max(0ll, (2 * n - m - 1 - b - 1) / 2)] > k) {
		last.push('(');
		ans[m] = '(';
		gen(m + 1, b + 1);
		return;
	} else {
		if (b + 1 <= n)
			k -= f[2 * n - m - 1][b + 1] * pows[max(0ll, (2 * n - m - 1 - b - 1) / 2)];
	}
	if (b - 1 >= 0 && !last.empty() && last.top() == '(' && f[2 * n - m - 1][b - 1] * pows[max(0ll, (2 * n - m - 1 - b + 1) / 2)] > k) {
		ans[m] = ')';
		last.pop();
		gen(m + 1, b - 1);
		return;
	} else {
		if (b - 1 >= 0 && !last.empty() && last.top() == '(')
			k -= f[2 * n - m - 1][b - 1] * pows[max(0ll, (2 * n - m - 1 - b + 1) / 2)];
	}
	if (b + 1 <= n && f[2 * n - m - 1][b + 1] * pows[max(0ll, (2 * n - m - 1 - b - 1) / 2)] > k) {
		last.push('[');
		ans[m] = '[';
		gen(m + 1, b + 1);
		return;
	} else {
		if (b + 1 <= n)
			k -= f[2 * n - m - 1][b + 1] * pows[max(0ll, (2 * n - m - 1 - b - 1) / 2)];
	}
	if (b - 1 >= 0 && !last.empty() && last.top() == '[' && f[2 * n - m - 1][b - 1] * pows[max(0ll, (2 * n - m - 1 - b + 1) / 2)] > k) {
		ans[m] = ']';
		last.pop();
		gen(m + 1, b - 1);
		return;
	} else {
		if (b - 1 >= 0 && !last.empty() && last.top() == '[')
			k -= f[2 * n - m - 1][b - 1] * pows[max(0ll, (2 * n - m - 1 - b + 1) / 2)];
	}
	return;
}

int main() {
	freopen("num2brackets2.in", "r", stdin);
	freopen("num2brackets2.out", "w", stdout);	
	cin >> n >> k;
	pows.resize(2 * n + 1);
	pows[0] = 1;
	for (int i = 1; i <= 2 * n; ++i)
		pows[i] = pows[i - 1] << 1;
	f.resize(2 * n + 1, vector <ll> (n + 2, 0));
	f[0][0] = 1;
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
