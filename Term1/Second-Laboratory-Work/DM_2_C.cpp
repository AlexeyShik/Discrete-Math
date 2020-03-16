#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("mtf.in", "r", stdin);
	freopen("mtf.out", "w", stdout);
	string s;
	cin >> s;
	vector <char> order;
	for (char c = 'a'; c <= 'z'; ++c)
		order.push_back(c);
	map <char, bool> used;
	for (auto c : s) {
		int id = 0;
		for (id = 0; id < (int)order.size(); ++id)
			if (order[id] == c)
				break;
		cout << id + 1 << ' ';
		while (id > 0) {
			swap(order[id], order[id - 1]);
			id--;
		}
	}
	return 0;
}
