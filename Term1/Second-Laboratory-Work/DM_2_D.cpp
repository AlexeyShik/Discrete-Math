#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("lzw.in", "r", stdin);
	freopen("lzw.out", "w", stdout);
	string s;
	cin >> s;
	map <string, int> order;
	int k = 1;
	for (char c = 'a'; c <= 'z'; ++c) {
		string cs = "";
		cs += c;
		order[cs] = k++;
	}
	order[""] = 1e9;
	int n = s.size();
	int i = 0;
	while (i < n) {
		string curr = "";
		curr += s[i];
		int last = -1;
		while (i < n && order[curr] > 0) {
			last = order[curr];
			++i;
			if (i < n)
				curr += s[i];
		}
		order[curr] = k++;
		cout << last - 1 << ' ';
	}	
	return 0;
}
