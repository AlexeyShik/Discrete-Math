#include <iostream>
#include <set>
#include <cmath>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<int> p(n - 2), deg(n, 1);
    for (int i = 0; i < n - 2; ++i) {
        cin >> p[i];
        ++deg[p[i] - 1];
    }
    vector<pair<int, int>> g;
    set<int> leafs;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 1) {
            leafs.insert(i);
        }
    }
    for (int i = 0; i < n - 2; ++i) {
        int u = *leafs.begin();
        leafs.erase(leafs.begin());
        --deg[u];
        int v = p[i] - 1;
        g.emplace_back(u + 1, v + 1);
        if (--deg[v] == 1) {
            leafs.insert(v);
        }
    }
    for (auto e : g) {
        cout << e.first << ' ' << e.second << endl;
    }
    int u = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 1 && u == -1) {
            u = i;
        } else if (deg[i] == 1) {
            cout << u + 1 << ' ' << i + 1 << endl;
            break;
        }
    }
    return 0;
}
