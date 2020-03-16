#include <bits/stdc++.h>

using namespace std;

inline int get(int mask, int i) {
	return mask & (1 << i);
}

int main() {
	int n, m;
	cin >> n >> m;
	map <pair <int, int>, bool> inCNF; // size <= 2 * n * 2 * n
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		inCNF[{a, b}] = true;
	}
	bool zero = true;
	for (int mask = 0; mask < (1 << n); ++mask) {
		bool curr = true;
		for (auto kloz : inCNF) {
			bool b;
			if (kloz.first.first > 0)
				b = get(mask, kloz.first.first - 1);
			else
				b = !get(mask, -kloz.first.first - 1);
			if (kloz.first.second > 0)
				b |= get(mask, kloz.first.second - 1);
			else
				b |= !get(mask, -kloz.first.second - 1);
			curr &= b;
		}
		zero &= !curr;
	}
	cout << (zero ? "YES" : "NO");
	return 0;
}
