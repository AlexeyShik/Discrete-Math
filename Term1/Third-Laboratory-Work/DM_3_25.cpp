#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("nextchoose.in", "r", stdin);
	freopen("nextchoose.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	vector <int> v(k);
	for (int i = 0; i < k; ++i)
		cin >> v[i];
	sort(v.begin(), v.end());
	if (k == 1) {
		if (v[0] == n)
			cout << -1;
		else
			cout << v[0] + 1;
		return 0;
	}
	bool highest = true;
	for (int i = 0; i < k; ++i)
		highest &= (v[k - i - 1] == n - i);
	if (highest) {
		cout << -1;
		return 0;
	}
	v.push_back(n + 1);
	int id;
	for (id = k - 1; id >= 0; --id) {
		if (v[id + 1] - v[id] >= 2)
			break;
	}
	v[id]++;
	for (int i = id + 1; i < k; ++i)
		v[i] = v[i - 1] + 1;
	v.pop_back();
	for (int x : v)
		cout << x << ' ';
	cout << endl;
	return 0;
}
