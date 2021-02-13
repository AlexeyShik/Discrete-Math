#include <iostream>
#include <queue>
#include <unordered_set>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

int main() {
    fastio;
    int n;
    cin >> n;
    vector<vector<bool>> g(n, vector<bool> (n));
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < i; ++j) {
            g[i][j] = g[j][i] = s[j] == '1';
        }
    }
    deque<int> q(n);
    for (int i = 0; i < n; ++i) {
        q[i] = i;
    }
    int_fast16_t cnt = 0;
    while (true) {
        if (!g[q[0]][q[1]]) {
            cnt = 1;
            int_fast16_t i = 2;
            while (!g[q[0]][q[i]] || !g[q[1]][q[i + 1]]) {
                ++i;
            }
            for (int_fast16_t j = 0; 1 + j < i - j; ++j) {
                swap(q[1 + j], q[i - j]);
            }
        } else {
            ++cnt;
            if (cnt == n) {
                break;
            }
        }
        q.push_back(q.front());
        q.pop_front();
    }
    for (int i = 0; i < n; ++i) {
        cout << q[i] + 1 << ' ';
    }
    return 0;
}
