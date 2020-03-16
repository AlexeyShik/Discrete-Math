#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("vectors.in", "r", stdin);
	freopen("vectors.out", "w", stdout);
	int n;
	cin >> n;
	vector <bool> ans(n);
	vector <vector <bool> > print;
	for (int i = 0; i < (1 << n); ++i) {
		bool check = true;
		for (int i = 1; i < n; ++i)
			check &= !(ans[i] == true && ans[i - 1] == true);
		if (check)
			print.push_back(ans);
		for (int j = n - 1; j >= 0; --j)
			if (ans[j]) {
				ans[j] = false;
			} else {
				ans[j] = true;
				break;
			}
	}
	cout << print.size() << endl;
	for (auto st : print) {
		for (auto e : st)
			cout << e;
		cout << endl;
	}
	return 0;
}
