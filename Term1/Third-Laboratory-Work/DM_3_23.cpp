#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("nextvector.in", "r", stdin);
	freopen("nextvector.out", "w", stdout);
	string s;
	cin >> s;
	int n = s.size();
	if (n == 1 && s[0] == '0') {
		cout << '-' << endl << 1;
		return 0;
	}
	bool zeros = true;
	for (auto c : s)
		zeros &= (c == '0');
	if (zeros) {
		cout << '-' << endl;
		s[s.size() - 1] = '1';
		cout << s;
		return 0;
	}
	bool ones = true;
	for (auto c : s)
		ones &= (c == '1');
	if (ones) {
		s[n - 1] = '0';
		cout << s << endl;
		/*cout << '1';
		for (int i = 0; i < n; ++i)
			cout << '0';*/
		cout << '-';
		return 0;
	}
	int id;
	for (id = n - 1; id >= 0; --id)
		if (s[id] == '1')
			break;
	if (id < 0) {
		cout << "Strange test";
		return 0;
	}
	s[id] = '0';
	for (int i = id + 1; i < n; ++i)
		s[i] = '1';
	cout << s << endl;
	s[id] = '1';
	for (int i = id + 1; i < n; ++i)
		s[i] = '0';
	for (id = n - 1; id >= 0; --id)
		if (s[id] == '0')
			break;
	if (id < 0) {
		cout << "Strange test";
		return 0;
	}
	s[id] = '1';
	for (int i = id + 1; i < n; ++i)
		s[i] = '0';
	cout << s;
	return 0;
}
