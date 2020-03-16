#include <bits/stdc++.h>

using namespace std;

int maxh = 0;

void dfs(int u, int h, vector <vector <int> > &g) {
	maxh = max(maxh, h);
	for (int v : g[u])
		dfs(v, h + 1, g);
}

inline int get(int mask, int k) {
	return mask & (1 << k);
}

int main() {
	int n;
	cin >> n;
	vector <vector <int> > g(n), tg(n);
	vector <vector <bool> > table(n);
	vector <int> p(n, 0);
	int k = 0;
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
		if (p[i] == 0) {
			k++;
			continue;
		}
		for (int j = 0; j < p[i]; ++j) {
			int x;
			cin >> x;
			x--;
			tg[i].push_back(x);
			g[x].push_back(i);
		}
		reverse(tg[i].begin(), tg[i].end());
		for (int j = 0; j < (1 << p[i]); ++j) {
			int x;
			cin >> x;
			table[i].push_back(x);
		}
	}
	for (int i = 0; i < n; ++i)
		if (p[i] == 0)
			dfs(i, 0, g);
	cout << maxh << endl;
	for (int mask = 0; mask < (1 << k); ++mask) {
		int j = k - 1;
		vector <bool> values(n);
		for (int i = 0; i < n; ++i) {
			if (p[i] == 0) {
				values[i] = get(mask, j);
				--j;
			} else {
				int id = 0;
				int nj = 0;
				for (int v : tg[i]) {
					id |= (values[v] << nj);
					++nj;
				}
				values[i] = table[i][id];
			}
		}
		cout << values[n - 1];
	}
	return 0;
}
