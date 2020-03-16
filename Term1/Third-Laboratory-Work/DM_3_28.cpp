#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("nextmultiperm.in", "r", stdin);
	freopen("nextmultiperm.out", "w", stdout);
	int n;
	cin >> n;
	vector <int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	int id = -1;
	for (int i = n - 1; i > 0; --i)
		if (v[i - 1] < v[i]) {
			id = i - 1;
			break;
		}
	if (id == -1) {
		for (int i = 0; i < n; ++i)
			cout << "0 ";
		return 0;
	}
	int min_x = v[id + 1], min_i = id + 1;
	for (int i = id + 1; i < n; ++i)
		if (v[i] > v[id] && min_x > v[i]) {
			min_x = v[i];
			min_i = i;
		}
	swap(v[min_i], v[id]);
	sort(v.begin() + id + 1, v.end());
	for (int x : v)
		cout << x << ' ';
	return 0;
}
