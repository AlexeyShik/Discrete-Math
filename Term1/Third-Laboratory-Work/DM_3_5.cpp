#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, k, sz;
vector <vector <int> > ans;

void gray() {
	for (int i = 1; i <= k; ++i)
		ans[i][0] = i - 1;
	int r = k;
	for (int i = 1; i < n; ++i) {
		int l = r;
		int bound = r;
    	for (int j = 1; j < k; ++j) {
			for (int t = 1; t <= bound; ++t) {
    			++r;
    			ans[r] = ans[l];
    			ans[r][i] = j;
    			if (j & 1)
    				--l;
				else
					++l;
			}
			if (j & 1)
    				++l;
				else
					--l;
		}
    }
}

int main() {
	freopen("telemetry.in", "r", stdin);
	freopen("telemetry.out", "w", stdout);
	cin >> n >> k;
	sz = pow(k, n);
	ans.resize(sz + 1, vector <int> (n));
	gray();
	for (int i = 1; i <= sz; ++i) {
		for (auto x : ans[i])
			cout << x;
		cout << endl;
	}
	return 0;
}
