#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("nextbrackets.in", "r", stdin);
	freopen("nextbrackets.out", "w", stdout);
	string s;
	cin >> s;
	int n = (int)s.size();
	int bal = 0;
	for (int i = n - 1; i >= 0; --i) {
		s[i] == ')' ? bal++ : bal--;
		if (s[i] == '(' && bal > 0) {
			s[i] = ')';
			int k = n - i;
			int j;
			for (j = i + 1; bal < k; ++j, k--, bal++)
				s[j] = '(';
			for (; j < n; ++j)
				s[j] = ')';
			cout << s;
			return 0;
		}
	}
	cout << "-";
	return 0;
}
