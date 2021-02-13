#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <unordered_set>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

int main() {
    int n;
    cin >> n;
    vector<unordered_set<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].insert(v);
        g[v].insert(u);
    }
    set<int> st;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() == 1) {
            st.insert(i);
        }
    }
    for (int i = 0; i < n - 2; ++i) {
        int u = *st.begin();
        st.erase(st.begin());
        int v = *g[u].begin();
        cout << v + 1 << ' ';
        g[v].erase(u);
        g[u].erase(v);
        if (g[v].size() == 1) {
            st.insert(v);
        }
    }
    return 0;
}