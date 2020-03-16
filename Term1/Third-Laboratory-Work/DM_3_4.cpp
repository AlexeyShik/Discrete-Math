#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("chaincode.in", "r", stdin);
	freopen("chaincode.out", "w", stdout);
	int n;
	cin >> n;
	map <string, bool> used;
	vector <string> ans;
	string cur = "";
	for (int i = 0; i < n; ++i)
		cur += '0';
	while (!used[cur]) {
		ans.push_back(cur);
		used[cur] = true;
		string prefix;
		for (int i = 1; i < n; ++i)
			prefix += cur[i];
		prefix += '1';
		if (!used[prefix])
			cur = prefix;
		else {
			prefix[n - 1] = '0';
			cur = prefix;
		}
	}
	for (auto x : ans)
		cout << x << endl;
	return 0;
}
