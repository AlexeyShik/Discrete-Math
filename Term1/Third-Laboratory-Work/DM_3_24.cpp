#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("nextperm.in", "r", stdin);
	freopen("nextperm.out", "w", stdout);
	int n;
	cin >> n;
	vector <int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	if (n == 1) {
		cout << 0 << endl << 0;
		return 0;
	}
	bool least = true;
	for (int i = 0; i < n; ++i)
		least &= (v[i] == i + 1);
	if (least) {
		for (int i = 0; i < n; ++i)
			cout << "0 ";
		cout << endl;
		swap(v[n - 1], v[n - 2]);
		for (int x : v)
			cout << x << ' ';
		return 0;
	}
	bool highest = true;
	for (int i = 0; i < n; ++i)
		highest &= (v[n - i - 1] == i + 1);
	if (highest) {
		swap(v[n - 1], v[n - 2]);
		for (int x : v)
			cout << x << ' ';
		cout << endl;
		for (int i = 0; i < n; ++i)
			cout << "0 ";
		return 0;
	}
	vector <int> tmp = v;
	int id;
	for (id = n - 2; id >= 0; --id) {
		if (v[id] > v[id + 1])
			break;
	}
	int mid = -1;
	for (int i = id + 1; i < n; ++i)
		if (v[i] < v[id] && (mid == -1 || v[mid] < v[i]))
			mid = i;
	if (mid == -1)
		mid = id + 1;
	swap(v[id], v[mid]);
	reverse(v.begin(), v.end());
	sort(v.begin(), v.end() - id - 1);
	reverse(v.begin(), v.end());
	for (int x : v)
		cout << x << ' ';
	cout << endl;
	v = tmp;
	for (id = n - 2; id >= 0; --id) {
		if (v[id] < v[id + 1])
			break;
	}
	mid = -1;
	for (int i = id + 1; i < n; ++i)
		if (v[i] > v[id] && (mid == -1 || v[mid] > v[i]))
			mid = i;
	if (mid == -1)
		mid = id + 1;
	swap(v[id], v[mid]);
	sort(v.begin() + id + 1, v.end());
	for (int x : v)
		cout << x << ' ';
	cout << endl;
	return 0;
}
