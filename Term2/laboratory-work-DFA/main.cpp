#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <queue>
#include <set>
#pragma GCC optimize("O3")

/// @author Alexey Shik
/// @version 1.0

using namespace std;

const int mod = 1e9 + 7;

/**
 * @struct Finite automaton
 * alphabet: a..z (latin characters)
 * states: 0..n-1, where n = number of states
 * @member start: an initial state
 * @member next - transition function: next[u][c] = v
 *         <=> in automation exists transition from u to v using the c character
 * @member prev - backward transition function: prev[v][c] = u <=> next[u][c] = v
 * @member is_term - access terminal states: is_term[u] = true <=> u is access terminal state
 **/
struct FA {
protected:
    int start = 0;
    vector <unordered_map <char, vector <int> > > next, prev;
    vector <bool> is_term;

public:
    /**
     * reads FA in such format:
     * n - number of states
     * m - number of transitions
     * k - number of access terminal states
     *      then k numbers - values of all access terminal states in 1-indexation
     *      then m triples: (u, v, c) - transition form u to v using symbol c
     * @param need_word_length: = true, if we have mixed input of FA and word length
     *        (specially for word_count format in laboratory work)
     * @return word_length (specially for word_count)
     */
    int read(bool need_word_length = false) {
        int n, m, k;
        cin >> n >> m >> k;
        int word_length = -1;
        if (need_word_length) {
            cin >> word_length;
        }
        next.resize(n);
        is_term.resize(n, false);
        for (int i = 0; i < k; ++i) {
            int x;
            cin >> x;
            is_term[x - 1] = true;
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            next[u - 1][c].push_back(v - 1);
        }
        if (need_word_length) {
            return word_length;
        }
        return 0;
    }

    /**
     * writes FA using format of read()
     */
    void write() {
        int n = is_term.size();
        int m = 0;
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (const auto& elem : next[i]) {
                m += elem.second.size();
            }
            k += is_term[i];
        }
        cout << n << ' ' << m << ' ' << k << endl;
        for (int i = 0; i < n; ++i) {
            if (is_term[i]) {
                cout << i + 1 << ' ';
            }
        }
        cout << endl;
        for (int i = 0; i < n; ++i) {
            for (const auto& elem : next[i]) {
                for (int v : elem.second) {
                    cout << i + 1 << ' ' << v + 1 << ' ' << elem.first << endl;
                }
            }
        }
    }
};

/**
 * @struct Deterministic finite automaton
 */
struct DFA : FA {
    friend struct NFA;
private:
    bool dfs_word_count(int u, vector <int> &used, vector <bool> &reachable, vector <int> &order) {
        used[u] = 1;
        bool loop = false;
        for (const auto& elem : next[u]) {
            for (int v : elem.second) {
                if (used[v] == 0) {
                    loop |= dfs_word_count(v, used, reachable, order);
                } else if (used[v] == 1 && (reachable[v] || reachable[u])) {
                    return true;
                }
            }
        }
        used[u] = 2;
        order.push_back(u);
        return loop;
    }

    bool check_loop(vector <bool> &reachable, vector <int> &order) {
        vector <int> used(is_term.size(), 0);
        if (!reachable[start]) {
            return false;
        }
        return dfs_word_count(start, used, reachable, order);
    }

    bool dfs_isomorphic(int u, int v, DFA& d, vector <bool> &used, vector <int> &dict) {
        used[u] = true;
        if (is_term[u] ^ d.is_term[v]) {
            return false;
        }
        dict[u] = v;
        bool ans = true;
        for (char c = 'a'; c <= 'z'; ++c) {
            if (next[u][c].size() != d.next[v][c].size()) {
                return false;
            }
            for (int i = 0; i < next[u][c].size(); ++i) {
                int _u = next[u][c][i];
                int _v = d.next[v][c][i];
                if (is_term[_u] != d.is_term[_v]) {
                    return false;
                }
                if (used[_u]) {
                    ans &= dict[_u] == _v;
                } else {
                    ans &= dfs_isomorphic(_u, _v, d, used, dict);
                }
            }
        }
        return ans;
    }

public:
    /**
     * initialization of prev[v][c][u] through next[u][c][v]
     */
    void init_prev () {
        prev.resize(next.size());
        for (int i = 0; i < is_term.size(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                for (int v : next[i][c]) {
                    prev[v][c].push_back(i);
                }
            }
        }
    }

    /**
     * initialization or reachable
     * @return reachable: vector of bool, where reachable[u] = true
     *         <=> exists path from u up to some access terminal state
     */
    vector <bool> init_reachable() {
        if (prev.empty()) {
            init_prev();
        }
        int n = is_term.size();
        vector <bool> used(n, false);
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (is_term[i]) {
                q.push(i);
                used[i] = true;
            }
        }
        vector <bool> reachable(n, false);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            reachable[current] = true;
            for (const auto& elem : prev[current]) {
                for (int v : elem.second) {
                    if (!used[v]) {
                        q.push(v);
                        used[v] = true;
                    }
                }
            }
        }
        return reachable;
    }

    /**
     * initialization or startable
     * @return startable: vector of bool, where startable[u] = true
     *         <=> exists path from start to u
     */
    vector <bool> init_startable() {
        int n = is_term.size();
        vector <bool> used(n, false);
        queue<int> q;
        q.push(start);
        vector <bool> startable(n, false);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            startable[current] = true;
            for (const auto& elem : next[current]) {
                for (int v : elem.second) {
                    if (!used[v]) {
                        q.push(v);
                        used[v] = true;
                    }
                }
            }
        }
        return startable;
    }

    /**
     * @param s - string, that need to be checked for access
     * @return true, if exists path from start to access terminal state
     *         consistently using symbols of s,
     *         false otherwise
     */
    bool check_access(string &s) {
        int current = start, i = 0;
        while (i < s.size()) {
            if (next[current][s[i]].empty()) {
                return false;
            }
            current = next[current][s[i]][0];
            ++i;
        }
        return is_term[current];
    }

    /**
     * @return number of words, that have access in this automaton,
     *         or -1, if there are infinitely many of them
     */
    int word_count() {
        if (prev.empty()) {
            init_prev();
        }
        int n = is_term.size();
        auto reachable = init_reachable();

        vector <int> order;
        if (check_loop(reachable, order)) {
            return -1;
        }

        vector <int> cnt(n, 0);
        for (int i = 0; i < n; ++i) {
            if (is_term[i]) {
                cnt[i] = 1;
            }
        }

        for (int i : order) {
            for (const auto& elem : prev[i]) {
                for (int v : elem.second) {
                    cnt[v] += cnt[i];
                    cnt[v] %= mod;
                }
            }
        }
        return cnt[start];
    }

    /**
     * @param l - length of words, that need to be count
     * @return number of words, that have access in this automaton and have length l
     */
    int word_count(int l) {
        if (prev.empty()) {
            init_prev();
        }
        int n = is_term.size();
        vector <vector <int> > cnt(n, vector <int> (l + 1, 0));
        cnt[start][0] = 1;
        for (int j = 1; j <= l; ++j) {
            for (int i = 0; i < n; ++i) {
                for (const auto& elem : prev[i]) {
                    for (int v : elem.second) {
                        cnt[i][j] += cnt[v][j - 1];
                        cnt[i][j] %= mod;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (is_term[i]) {
                ans += cnt[i][l];
                ans %= mod;
            }
        }
        return ans;
    }

    /**
     * @param d - DFA, that we need to check on isomorphism
     * @return true, if this DFA and d are isomorphic,
     *         false otherwise
     */
    bool isomorphic(DFA d) {
        const int n = is_term.size();
        if (n != d.is_term.size()) {
            return false;
        }
        vector <bool> used(n, false);
        vector <int> dict(n);
        return dfs_isomorphic(start, d.start, d, used, dict);
    }

    /**
     * @param d - DFA, that we need to check on equivalence
     * @return true, if this DFA and d are equivalent,
     *         false otherwise
     */
    bool equivalent(DFA d) {
        return d.minimize().isomorphic(this->minimize());
    }

    /**
     * DFA minimization using Hopcroft's algorithm in O(n*log(n))
     * @return automaton with minimal number of states, that is equivalence to this
     */
    DFA minimize() {
        next.push_back({});
        int dst = is_term.size();
        for (int i = 0; i <= dst; ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                if (next[i][c].empty()) {
                    next[i][c] = {dst};
                }
            }
        }
        is_term.push_back(false);
        init_prev();

        int n = is_term.size();
        vector <int> to_class(n, 0);
        vector <unordered_set <int> > get_class(2);

        for (int i = 0; i < n; ++i) {
            to_class[i] = is_term[i];
            get_class[is_term[i]].insert(i);
        }

        queue <int> que;
        if (!get_class[0].empty()) {
            que.push(0);
            if (!get_class[1].empty()) {
                que.push(1);
            }
        } else {
            swap(get_class[0], get_class[1]);
            to_class.assign(n, 0);
            que.push(0);
            get_class.pop_back();
        }

        while (!que.empty()) {
            int curr = que.front();
            que.pop();

            for (char c = 'a'; c <= 'z'; ++c) {
                unordered_map <int, vector <int> > involved;

                for (int q : get_class[curr]) {
                    for (int r : prev[q][c]) {
                        involved[to_class[r]].push_back(r);
                    }
                }

                for (const auto& elem : involved) {
                    int i = elem.first;
                    if (elem.second.size() < get_class[i].size()) {
                        int j = get_class.size();
                        get_class.push_back({});

                        for (int r : elem.second) {
                            get_class[i].erase(r);
                            get_class[j].insert(r);
                        }

                        if (get_class[j].size() > get_class[i].size()) {
                            swap(get_class[j], get_class[i]);
                        }

                        for (int r : get_class[j]) {
                            to_class[r] = j;
                        }
                        que.push(j);
                    }
                }
            }
        }

        int m = get_class.size();
        DFA d;
        d.next.resize(m);
        d.is_term.resize(m, false);
        for (int i = 0; i < m; ++i) {
            for (int q : get_class[i]) {
                if (is_term[q]) {
                    d.is_term[i] = true;
                }
                if (q == start) {
                    d.start = i;
                }
                for (char c = 'a'; c <= 'z'; ++c) {
                    for (int v : next[q][c]) {
                        d.next[i][c].push_back(to_class[v]);
                    }
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                sort(d.next[i][c].begin(), d.next[i][c].end());
                d.next[i][c].erase(unique(d.next[i][c].begin(), d.next[i][c].end()), d.next[i][c].end());
            }
        }

        if (d.start != 0) {
            swap(d.next[0], d.next[to_class[start]]);
            swap(d.is_term[0], d.is_term[to_class[start]]);
            for (int i = 0; i < m; ++i) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    for (int &q : d.next[i][c]) {
                        if (q == 0) {
                            q = to_class[start];
                        } else if (q == to_class[start]) {
                            q = 0;
                        }
                    }
                }
            }
            d.start = 0;
        }

        auto reachable = d.init_reachable();
        auto startable = d.init_startable();
        unordered_map <int, int> compress;
        for (int i = 0; i < m; ++i) {
            if (startable[i] && reachable[i]) {
                compress[i] = compress.size();
            }
        }

        vector <unordered_map <char, vector <int> > > true_next(compress.size());
        vector <bool> true_term(compress.size(), false);

        for (int i = 0; i < m; ++i) {
            if (!startable[i] || !reachable[i]) {
                continue;
            }
            true_term[compress[i]] = d.is_term[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                for (int v : d.next[i][c]) {
                    if (startable[v] && reachable[v]) {
                        true_next[compress[i]][c].push_back(compress[v]);
                    }
                }
            }
        }
        d.next = true_next;
        d.is_term = true_term;
        d.init_prev();
        return d;
    }
};

/**
 * @struct Nondeterministic finite automaton
 */
struct NFA : FA {
    /**
     * @param s - string, that need to be checked for access
     * @return true, if exists path from start to access terminal state
     *         consistently using symbols of s,
     *         false otherwise
     */
    bool check_access(string &s) {
        int n = is_term.size();
        int len = s.size();
        vector <vector <bool> > can(len + 1, vector <bool> (n, false));
        can[0][start] = true;
        for (int i = 0; i < len; ++i) {
            for (int u = 0; u < n; ++u) {
                if (can[i][u]) {
                    for (int v : next[u][s[i]]) {
                        can[i + 1][v] = true;
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (is_term[i] && can[len][i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * Thompson's construction of equivalence DFA
     * @return DFA, that is equivalence to this NFA
     */
    DFA build_DFA() {
        DFA d;
        map <set <int>, bool> used;
        map <set <int>, int> set_to_id;
        d.start = start;
        d.next.resize(101); /// in laboratory work is guaranteed that DFA will not have more states
        d.is_term.resize(101);
        set <int> starts;
        starts.insert(start);
        set_to_id[starts] = 0;
        used[starts] = true;
        queue <set <int> > q;
        q.push(starts);
        while (!q.empty()) {
            set <int> current = q.front();
            q.pop();
            bool term = false;
            for (auto v : current) {
                term |= is_term[v];
            }
            d.is_term[set_to_id[current]] = term;
            for (char c = 'a'; c <= 'z'; ++c) {
                set<int> nodes;
                for (int u : current) {
                    for (const auto &elem : next[u]) {
                        if (elem.first == c) {
                            for (int v : elem.second) {
                                nodes.insert(v);
                            }
                        }
                    }
                }
                if (!used[nodes]) {
                    set_to_id[nodes] = set_to_id.size();
                    used[nodes] = true;
                    q.push(nodes);
                }
                d.next[set_to_id[current]][c].push_back(set_to_id[nodes]);
            }
        }
        return d;
    }
};

int main() {
    //freopen("equivalence.in", "r", stdin);
    //freopen("equivalence.out", "w", stdout);
    NFA d;
    d.read();
    d.build_DFA().minimize().write();
    return 0;
}
