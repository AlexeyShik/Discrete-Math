#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
 
int main() {
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
    int n;
    cin >> n;
    multiset <ll> p;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        p.insert(x);
    }
    ll ans = 0;
    if (p.size() == 1) {
        cout << *p.begin() << endl;
        return 0;
    }
    while (!p.empty()) {
        ll a = *p.begin();
        p.erase(p.begin());
        if (p.empty()) {
            break;
        }
        ll b = *p.begin();
        p.erase(p.begin());
        ans += a + b;
        p.insert(a + b);
    }
    cout << ans;
    return 0;
}
