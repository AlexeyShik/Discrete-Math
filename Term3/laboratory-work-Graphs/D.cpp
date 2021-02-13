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
    vector<vector<bool>> g(n, vector<bool>(n));
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < i; ++j) {
            g[i][j] = s[j] == '1';
            g[j][i] = s[j] == '0';
        }
    }
    vector<int> ans(1, 0);
    for (int i = 1; i < n; ++i) {
        int j = 0;
        for (; j < i && g[ans[j]][i]; ++j) {}
        ans.insert(ans.begin() + j, i);
    }
    int i = n - 1;
    while (g[ans[0]][ans[i]]) {
        --i;
    }
    ++i;
    while (i < n) {
        bool found = false;
        for (int j = i; j < n && !found; ++j) {
            for (int t = 0; t < i; ++t) {
                if (g[ans[j]][ans[t]]) {
                    vector<int> tmp = ans;
                    tmp.erase(tmp.begin() + t, tmp.end());
                    tmp.insert(tmp.end(), ans.begin() + i, ans.begin() + j + 1);
                    tmp.insert(tmp.end(), ans.begin() + t, ans.begin() + i);
                    tmp.insert(tmp.end(), ans.begin() + j + 1, ans.end());
                    ans = tmp;
                    i = j;
                    found = true;
                    break;
                }
            }
        }
        ++i;
    }
    for (int x : ans) {
        cout << x + 1 << ' ';
    }
    return 0;
}
