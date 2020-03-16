#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("antigray.in", "r", stdin);
	freopen("antigray.out", "w", stdout);
	int n;
	cin >> n;
	vector <int> v(n, 0);
	int m = pow(3, n - 1);
	for (int i = 0; i < m; ++i) {
		for (auto x : v)
			cout << x;
		cout << endl;
		for (auto x : v)
			cout << (x + 1) % 3;
		cout << endl;
		for (auto x : v)
			cout << (x + 2) % 3;
		cout << endl;
		for (int j = n - 1; j >= 0; --j)
			if (v[j] != 2) {
				v[j]++;
				break;
			} else {
				v[j] = 0;
			}
	}
	return 0;
}
