#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n;
vector <int> ans;

void gen() {
	cout << endl;
	for (int x : ans)
		cout << x << ' ';
	for (int x = ans[ans.size() - 1] + 1; x <= n; ++x) {
		ans.push_back(x);
		gen();
		ans.pop_back();
	}
}

int main() {
	freopen("subsets.in", "r", stdin);
	freopen("subsets.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		ans.push_back(i);
		gen();
		ans.pop_back();
	}
	return 0;
}
