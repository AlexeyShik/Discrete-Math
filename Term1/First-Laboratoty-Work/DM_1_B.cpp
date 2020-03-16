#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector <vector <int> > v(k, vector <int> (n));
	vector <bool> ans(n, false);
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < n; ++j)
			cin >> v[i][j];
	vector <bool> changed(n, false);
	for (int t = 0; t <= 2000; ++t) {
		for (int i = 0; i < k; ++i) {
			bool one = false;
			int id = -1;
			for (int j = 0; j < n; ++j) 
				if (v[i][j] != -1){
					bool curr = (v[i][j] == 1 ? ans[j] : !ans[j]);
					one |= curr;
					if (!curr && !changed[j])
						id = j;
				}
			if (!one && id != -1) {
				changed[id] = true;
				ans[id] = !ans[id];
			}
		}
	}
	bool alright = true;
	for (int i = 0; i < k; ++i) {
		bool one = false;
		for (int j = 0; j < n; ++j) 
			if (v[i][j] != -1)
				one |= (v[i][j] == 1 ? ans[j] : !ans[j]);
		alright &= one;
	}
	if (alright)
		cout << "NO"; 
	else
		cout << "YES";
	return 0;
}
