//
// Created by Alexey Shik on 11.04.2021.
//
#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

int main() {
    int k;
    cin >> k;
    vector<ll> a(k), c(k + 1);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> c[i + 1];
    }
    vector<ll> p(k), q(k + 1);
    for (int i = 0; i < k; ++i) {
        p[i] = a[i];
        for (int j = 1; j <= i; ++j) {
            p[i] -= c[j] * a[i - j];
        }
    }
    q[0] = 1;
    for (int i = 1; i <= k; ++i) {
        q[i] = -c[i];
    }
    while (p.size() > 1 && p.back() == 0) {
        p.pop_back();
    }
    cout << p.size() - 1 << endl;
    for (ll x : p) {
        cout << x << ' ';
    }
    cout << endl;
    while (q.size() > 1 && q.back() == 0) {
        q.pop_back();
    }
    cout << q.size() - 1 << endl;
    for (ll x : q) {
        cout << x << ' ';
    }
    return 0;
}
