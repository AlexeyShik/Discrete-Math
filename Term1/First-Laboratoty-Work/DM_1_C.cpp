#include <bits/stdc++.h>

using namespace std;

bool major(int i, int j, int n) {
	for (int k = (1 << n); k > 0; k >>= 1)
		if ((i & k) < (j & k))
			return false;
	return true;
}

bool lineal(int i) {
	int cnt = 0;
	while (i > 0) {
		cnt += i % 2;
		i /= 2;
	}
	return cnt <= 1;
}

bool checkl(vector <bool> &b, int n) {
	for (int i = 0; i < (1 << n); ++i) {
		bool x = 0;
		for (int j = 0; j <= i; ++j)
			if (major(i, j, n))
				x ^= b[j];
		if (x && !lineal(i))
			return false;
	}
	return true;
}

int no(int i, int n) {
	return (1 << n) - i - 1;
}

bool checks(vector <bool> &b, int n) {
	if (n == 0)
		return false;
	for (int i = 0; i < (1 << (n - 1)); ++i)
		if (b[i] == b[no(i, n)])
			return false;
	return true;
}

bool checkm(vector <bool> &b, int n) {
	for (int i = 0; i < (1 << n); ++i)
		for (int j = 0; j <= i; ++j)
			if (major(i, j, n) && b[i] < b[j])
				return false;
	return true;
}

int main() {
	int n;
	cin >> n;
	bool f0 = false, f1 = false, fl = false, fs = false, fm = false;
	for (int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		vector <bool> b(1 << k);
		string s;
		cin >> s;
		for (int i = 0; i < (1 << k); ++i)
			b[i] = (s[i] == '1');
		f0 |= b[0];
		f1 |= !b[(1 << k) - 1];
		fl |= !checkl(b, k);
		fs |= !checks(b, k);
		fm |= !checkm(b, k);
	}
	if (f0 && f1 && fl && fs && fm)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
