#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define fileio freopen("cf.in", "r", stdin), freopen("cf.out", "w", stdout)

typedef long long ll;
using namespace std;

///  element from the right side of the rule
///  non-terminal states are 'A' .. 'Z', terminal states are 'a' .. 'z'
struct item {
    char value;
    bool is_terminal;

    explicit item(char value) : value(value), is_terminal(islower(value)) {}
};

istream &operator>>(istream &in, item &cur) {
    in >> cur.value;
    cur.is_terminal = islower(cur.value);
    return in;
}

ostream &operator<<(ostream &out, item &cur) {
    out << cur.value;
    return out;
}

/**
 * class for processing rules
 * @method toString - static method, converts a rule from the form: pair<left part, vector of elements of right part>
 *                    to the form: left part -> right part
 * @method parse - converts string in format: left part -> right part
 *                 to the form: pair<left part, vector of elements of right part>
 * @mentor kgeorgiy
**/
class ruleParser {
    int pos;
    string str;

    char getChar() {
        if (pos >= str.size()) {
            throw runtime_error("IndexOutOfBoundException");
        }
        return str[pos];
    }

    void nextChar() {
        ++pos;
    }

    bool isWhitespace() {
        return pos < str.size() && isspace(str[pos]);
    }

    void skipWhitespace() {
        while (isWhitespace()) {
            nextChar();
        }
    }

    void expect(char expected) {
        if (str[pos] == expected) {
            nextChar();
        } else {
            string message = "Expected: ";
            message += expected;
            message += ", found";
            message += str[pos];
            throw runtime_error(message);
        }
    }

    void expect(const string &expected) {
        for (const auto c : expected) {
            expect(c);
        }
    }

public:
    explicit ruleParser(string str) : str(move(str)), pos(0) {}

    explicit ruleParser() : str(""), pos(0) {}

    pair<char, vector<item>> parse() {
        pair<char, vector<item>> ans{};
        skipWhitespace();
        ans.first = str[pos];
        expect(ans.first);
        skipWhitespace();
        expect("->");
        skipWhitespace();
        while (pos < str.size() && !isWhitespace()) {
            ans.second.emplace_back(getChar());
            nextChar();
        }
        return ans;
    }

    static string toString(const pair<char, vector<item>> &rule) {
        string ans = " ";
        ans += rule.first;
        ans += " -> ";
        for (const item &i : rule.second) {
            ans += i.value;
        }
        return ans;
    }
};

/**  Context free grammar
 *  @field start - start state
 *  @field produce - grammar rules in format: pair<left part, vector of elements of right part>
 *  @mentor andrewzta
**/
struct CFG {
    char start{};
    unordered_map<char, vector<vector<item>>> produce;

    /**  @Contract(format of input like this:
     *  n - number of rules, S - start state
     *  n rules like A -> BcDeFG
     *  For example:
     *  2 S
     *  S -> aA
     *  A -> b)
    **/
    void read() {
        int size;
        cin >> size >> start;
        for (int i = 0; i < size; ++i) {
            string str;
            while (str.empty()) {
                getline(cin, str);
            }
            ruleParser parser(str);
            auto curr = parser.parse();
            produce[curr.first].push_back(curr.second);
        }
    }

    ///  @Contract(CF grammar is right-linear)
    ///  @returns true, if word w can be deduced in the grammar, false otherwise
    bool right_linear_check(const string &w) {
        struct event {
            int len;
            char state;

            event(int len, char state) : len(len), state(state) {}
        };
        queue<event> q;
        q.push(event(0, start));
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (const auto &rule : produce[cur.state]) {
                if (rule.size() == 1 && cur.len == w.length() - 1 && w[cur.len] == rule[0].value) {
                    return true;
                } else if (rule.size() == 2 && cur.len != w.length() - 1 && w[cur.len] == rule[0].value) {
                    q.push(event(cur.len + 1, rule[1].value));
                }
            }
        }
        return false;
    }

    /// @returns all non-terminal states, that can produce epsilon
    vector<char> get_epsilon_producers() {
        vector<char> producers;
        unordered_map<char, bool> marked;
        for (const auto &elem : produce) {
            for (const auto &rule : elem.second) {
                if (rule.empty()) {
                    producers.emplace_back(elem.first);
                    marked[elem.first] = true;
                    break;
                }
            }
        }
        bool changes = true;
        while (changes) {
            changes = false;
            for (const auto &elem : produce) {
                if (!marked[elem.first]) {
                    for (const auto &rule : elem.second) {
                        bool new_producer = true;
                        for (const item &x : rule) {
                            new_producer &= marked[x.value];
                        }
                        if (new_producer) {
                            producers.emplace_back(elem.first);
                            marked[elem.first] = true;
                            changes = true;
                        }
                    }
                }
            }
        }
        sort(producers.begin(), producers.end());
        return producers;
    }

    ///  @Contract(CF grammar is in Chomsky normal form)
    ///  @returns number of ways to deduce word w in this grammar (mod 1e9+7)
    ll nfc_count(const string &w) {
        const ll MOD = 1e9 + 7;
        unordered_map<char, vector<vector<ll> > > dp;
        for (char c = 'A'; c <= 'Z'; ++c) {
            dp[c].resize(w.size(), vector<ll>(w.size(), 0));
        }
        for (int i = 0; i < w.size(); ++i) {
            for (const auto &elem : produce) {
                for (const auto &rule : elem.second) {
                    if (rule.size() == 1) {
                        dp[elem.first][i][i] += (w[i] == rule[0].value);
                    }
                }
            }
        }
        for (int len = 1; len < w.size(); ++len) {
            for (int l = 0, r = len; r < w.size(); ++l, ++r) {
                for (const auto &elem : produce) {
                    for (const auto &rule : elem.second) {
                        if (rule.size() == 2) {
                            for (int k = l; k < r; ++k) {
                                dp[elem.first][l][r] += dp[rule[0].value][l][k] * dp[rule[1].value][k + 1][r];
                                dp[elem.first][l][r] %= MOD;
                            }
                        }
                    }
                }
            }
        }
        return dp[start][0][w.size() - 1];
    }

    ///  @returns vector of all non-terminal states, that are useless
    vector<char> get_useless_nodes() {
        unordered_map<char, bool> is_producing, is_usable;
        for (const auto &elem : produce) {
            is_usable[elem.first] = true;
            for (const auto &rule : elem.second) {
                for (auto event : rule) {
                    if (!event.is_terminal) {
                        is_usable[event.value] = true;
                    }
                }
            }
        }
        is_usable[start] = true;
        bool changes = true;
        while (changes) {
            changes = false;
            for (const auto &elem : produce) {
                if (!is_producing[elem.first]) {
                    for (const auto &rule : elem.second) {
                        bool new_producer = true;
                        for (const item &x : rule) {
                            if (!x.is_terminal) {
                                new_producer &= is_producing[x.value];
                            }
                        }
                        if (new_producer) {
                            is_producing[elem.first] = true;
                            changes = true;
                            break;
                        }
                    }
                }
            }
        }
        unordered_map<char, bool> useful;
        useful[start] = is_producing[start];
        changes = true;
        while (changes) {
            changes = false;
            for (const auto &elem : produce) {
                if (useful[elem.first]) {
                    for (const auto &rule : elem.second) {
                        bool new_useful = true;
                        for (const item &x : rule) {
                            if (!x.is_terminal) {
                                new_useful &= is_producing[x.value];
                            }
                        }
                        if (new_useful) {
                            for (const item &x : rule) {
                                if (!x.is_terminal && !useful[x.value]) {
                                    useful[x.value] = true;
                                    changes = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        vector<char> useless;
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (!useful[c] && is_usable[c]) {
                useless.emplace_back(c);
            }
        }
        return useless;
    }

    ///  @returns true, if word w can be deduced in the grammar, false otherwise
    bool check(const string &w) {
        unordered_map<char, vector<vector<bool>>> dp;
        unordered_map<string, vector<vector<vector<bool>>>> h;
        unordered_map<int, string> str;
        for (const auto &elem : produce) {
            for (const auto &rule : elem.second) {
                str[rule_hashcode(elem.first, rule)] = ruleParser::toString({elem.first, rule});
            }
        }
        const int n = w.length() + 1;
        for (char c = 'A'; c <= 'Z'; ++c) {
            dp[c].resize(n, vector<bool>(n, false));
        }
        for (const auto &elem : produce) {
            for (const auto &rule : elem.second) {
                string s = str[rule_hashcode(elem.first, rule)];
                h[s].resize(n, vector<vector<bool>>(n, vector<bool>(6, false)));
                for (int i = 0; i < n; ++i) {
                    h[s][i][i][0] = true;
                }
            }
        }
        for (int i = 0; i < w.size(); ++i) {
            for (const auto &elem : produce) {
                for (const auto &rule : elem.second) {
                    if (rule.size() == 1) {
                        dp[elem.first][i][i + 1] = dp[elem.first][i][i + 1] || (w[i] == rule[0].value);
                    } else if (rule.empty()) {
                        dp[elem.first][i][i] = true;
                    }
                }
            }
        }
        for (int len = 0; len < n; ++len) {
            for (int l = 0, r = len; r < n; ++l, ++r) {
                bool changes = true;
                while (changes) {
                    changes = false;
                    for (const auto &elem : produce) {
                        for (const auto &rule : elem.second) {
                            string s = str[rule_hashcode(elem.first, rule)];
                            for (int k = 1; k <= rule.size(); ++k) {
                                bool correct = false;
                                for (int m = l; m <= r; ++m) {
                                    if (rule[k - 1].is_terminal) {
                                        correct |= h[s][l][m][k - 1] && r - m == 1 && w[m] == rule[k - 1].value;
                                    } else if (!rule[k - 1].is_terminal) {
                                        correct |= h[s][l][m][k - 1] && dp[rule[k - 1].value][m][r];
                                    }
                                }
                                if (correct) {
                                    h[s][l][r][k] = true;
                                }
                            }
                        }
                    }
                    for (const auto &elem : produce) {
                        for (const auto &rule : elem.second) {
                            if (!dp[elem.first][l][r] && h[str[rule_hashcode(elem.first, rule)]][l][r][rule.size()]) {
                                dp[elem.first][l][r] = true;
                                changes = true;
                            }
                        }
                    }
                }
            }
        }
        return dp[start][0][w.size()];
    }

private:
    static int rule_hashcode(char c, const vector<item> &v) {
        ll ans = c - 'A';
        for (auto i : v) {
            ans += 71 * (i.is_terminal ?  28 + (i.value - 'a') : (i.value - 'A'));
            ans %= int(1e9+7);
        }
        return ans % int(1e9+7);
    }
};

int main() {
    fastio;
    fileio;

    CFG g;
    g.read();
    string str;
    cin >> str;
    cout << (g.check(str) ? "yes" : "no");
    return 0;
}
