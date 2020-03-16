#include <bits/stdc++.h>

using namespace std;

bool major(int i, int j) {
	for (int k = (1 << 10); k > 0; k >>= 1)
		if ((i & k) < (j & k))
			return false;
	return true;
}

inline void bitPrint(int i, int n) {
	for (int k = (1 << (n - 1)); k > 0; k >>= 1)
		cout << ((i & k) == 0 ? 0 : 1);
}

int main() {
	int n;
	cin >> n;
	int sz = (1 << n);
	vector <bool> f(sz);
	for (int i = 0; i < sz; ++i) {
		string s;
		cin >> s;
		cin >> f[i];
	}
	for (int i = 0; i < sz; ++i) {
		int x = 0;
		for (int j = 0; j <= i; ++j)
			if (major(i, j))
				x ^= f[j];
		bitPrint(i, n);
		cout << ' ' << x << endl;
	}
	return 0;
}
