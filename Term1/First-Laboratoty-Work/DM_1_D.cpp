#include <bits/stdc++.h>

using namespace std;
typedef uint64_t uint;
typedef long long ll;
const uint MAX = ULLONG_MAX;

inline uint get(uint mask, int i) {
	return mask & (1 << i);
}

int main() {
	int n;
	cin >> n;
	vector <uint> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	uint s;
	cin >> s;
	if (s == 0) {
		cout << "1&~1";
		return 0;
	}
	string str = "";
	uint ans = 0;
	for (int i = 0; i < 32; ++i) {
		if (!get(s, i))
			continue;
		uint cur = MAX;
		for (int j = 0; j < n; ++j) {
			if (get(v[j], i))
				cur &= v[j];
			else {
				str.push_back('~');
				cur &= ~v[j];
			}
			str.push_back(char('1' + j));
			if (j != n - 1)
				str.push_back('&');
		}
		str.push_back('|');
		ans |= cur;
	}
	while (str.size() >= 1 && str[str.size() - 1] == '|')
		str.pop_back();
	if (ans != s) {
		cout << "Impossible";
	} else {
		cout << str;
	}
	return 0;
}
