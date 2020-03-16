#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;
vector <vector <bool> > ans;

void gray() {
	ans[1][n - 1] = false;
	ans[2][n - 1] = true;
	int r = 2;
	for (int i = 1; i < n; ++i) {
		int l = r;
    	r *= 2;
    	for (int k = r / 2 + 1; k <= r; ++k) {
    		ans[k] = ans[l];
    		ans[l][n - i - 1] = false;
    		ans[k][n - i - 1] = true; 
    		l--;
    	}
    }
}

int main() {
	freopen("gray.in", "r", stdin);
	freopen("gray.out", "w", stdout);
	cin >> n;
	ans.resize(((1 << n) + 1), vector <bool> (n));
	gray();
	for (int i = 1; i <= (1 << n); ++i) {
		for (auto x : ans[i])
			cout << x;
		cout << endl;
	}
	return 0;
}
