#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0) 
#define fileio freopen("input.txt","r",stdin),freopen("output.txt","w",stdout)
#define pb push_back
#define pll pair<ll,ll>
#define pii pair<int,int>
#pragma GCC optimize ("O3")

using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 7;

vector <vector <int> > s;
int n, k;

void fill_start() {
	for (int i = 1; i <= n; ++i) {
		vector <int> cur(1, i);
		s.push_back(cur);
	}
}

bool not_start() {
	return (int)s.size() < n;
}

void print() {
	for (auto st : s) {
		for (auto t : st) {
			cout << t << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void get_next() {
	set <int> deleted;
	int tmp = -1;
	for (int i = s.size() - 1; i >= 0; --i) {
		if (!deleted.empty() && deleted.upper_bound(s[i].back()) != deleted.end()) {
			auto it = deleted.upper_bound(s[i].back());
			int x = *it;
			deleted.erase(it);
			s[i].push_back(x);
			for (int t = i + 1; !deleted.empty(); ++t) {
				if (t == (int)s.size())
					s.resize(s.size() + 1);
				s[t].push_back(*deleted.begin());
				deleted.erase(deleted.begin());
			}
			break;	
		}
		if (s[i].size() == 1) {
			deleted.insert(s[i].back());
			s.pop_back();
			continue;
		}
		deleted.insert(s[i].back());
		s[i].pop_back();
		vector <bool> used(s[i].size(), true);
		for (int j = s[i].size() - 1; j > 0; --j) {
			if (!deleted.empty() && deleted.upper_bound(s[i][j]) != deleted.end()) {
				auto it = deleted.upper_bound(s[i][j]);
				int x = *it;
				deleted.erase(it);
				tmp = s[i][j];
				s[i][j] = x;
				deleted.insert(tmp);		
				for (int t = i + 1; !deleted.empty(); ++t) {
					if (t == (int)s.size())
						s.resize(s.size() + 1);
					s[t].push_back(*deleted.begin());
					deleted.erase(deleted.begin());
				}	
				break;
			}
			deleted.insert(s[i][j]);
			s[i].pop_back();
		}
		if (tmp != -1) {
			break;
		}
		deleted.insert(s[i][0]);
		s.pop_back();
	}
	for (int t = s.size(); !deleted.empty(); ++t) {
		s.resize(s.size() + 1);
		s[t].push_back(*deleted.begin());
		deleted.erase(deleted.begin());
	}
}


int main() {
	freopen("part2sets.in", "r", stdin);
	freopen("part2sets.out", "w", stdout);
	cin >> n >> k;
	fill_start();
	do {
		if ((int)s.size() == k)
			print();
		get_next();
	} while (not_start());
	return 0;
}
