//
// Created by Alexey Shik on 11.04.2021.
//

#ifndef DM_GF_POLYNOMIAL_H
#define DM_GF_POLYNOMIAL_H


#include <istream>
#include <vector>
#include <cassert>

typedef long long ll;

class polynomial {

public:
    std::vector<ll> digits;

    void shrink_to_fit();
    const ll get(size_t i) const;
    polynomial();
    explicit polynomial(size_t size);
    explicit polynomial(std::vector<ll> digits);
    polynomial(polynomial const &other) = default;
    friend std::istream &operator>>(std::istream &in, polynomial &p);
    friend std::ostream &operator<<(std::ostream &out, polynomial &p);
    friend std::ostream &operator<<(std::ostream &out, polynomial &&p);
    friend polynomial operator+(const polynomial &p1, const polynomial &p2);
    friend polynomial operator-(const polynomial &p1, const polynomial &p2);
    friend polynomial operator*(ll a, const polynomial &p);
    friend polynomial operator*(const polynomial &p1, const polynomial &p2);
    friend polynomial operator/(const polynomial &p1, const polynomial &p2);
    ll &operator[](size_t i);
    ll operator[](size_t i) const;
    polynomial operator-();
    size_t size() const;
    static ll add(ll &a, ll b);
    static ll add(ll &&a, ll b);
    static ll sub(ll &a, ll b);
    static ll sub(ll &&a, ll b);
    static ll mul(ll &a, ll b);
    static ll mul(ll &&a, ll b);
    static ll binpow(ll &a, ll n);
    static ll binpow(ll &&a, ll n);
    static ll div_(ll &a, ll b);
    static ll div_(ll &&a, ll b);
};

#endif //DM_GF_POLYNOMIAL_H

#include <iostream>

//
// Created by Alexey Shik on 11.04.2021.
//

polynomial::polynomial() : digits() {}

polynomial::polynomial(size_t size) : digits(size) {}

polynomial::polynomial(std::vector<ll> digits) : digits(std::move(digits)) {}

std::istream &operator>>(std::istream &in, polynomial &p) {
    int n;
    in >> n;
    p.digits.resize(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        in >> p[i];
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, polynomial &p) {
    out << p.size() - 1 << std::endl;
    for (const ll digit : p.digits) {
        out << digit << ' ';
    }
    out << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, polynomial &&p) {
    return out << p;
}

polynomial operator+(const polynomial &p1, const polynomial &p2) {
    polynomial result(std::max(p1.size(), p2.size()));
    for (int i = 0; i < p1.size(); ++i) {
        result[i] = polynomial::add(result[i], p1[i]);
    }
    for (int i = 0; i < p2.size(); ++i) {
        result[i] = polynomial::add(result[i], p2[i]);
    }
    result.shrink_to_fit();
    return result;
}

polynomial operator-(const polynomial &p1, const polynomial &p2) {
    return p1 + (-polynomial(p2));
}

polynomial operator*(const polynomial &p1, const polynomial &p2) {
    polynomial result(p1.size() + p2.size());
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            result[i] = polynomial::add(result[i], polynomial::mul(p1.get(j), p2.get(i - j)));
        }
    }
    while (result.size() > 7) {
        result.digits.pop_back();
    }
    result.shrink_to_fit();
    return result;
}


polynomial operator/(const polynomial &p1, const polynomial &p2) {
    assert(p2[0] != 0);
    polynomial result(1000);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = p1.size() > i ? p1[i] : 0;
        for (int j = 0; j < i; ++j) {
            result[i] = polynomial::sub(result[i], polynomial::mul(result[j], p2.get(i - j)));
        }
        result[i] = polynomial::div_(result[i], p2[0]);
    }
    return result;
}


void polynomial::shrink_to_fit() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

size_t polynomial::size() const {
    return digits.size();
}

ll &polynomial::operator[](size_t i) {
    return digits[i];
}

ll polynomial::operator[](size_t i) const {
    return digits[i];
}

polynomial polynomial::operator-() {
    polynomial result(*this);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = mul(result[i], -1);
    }
    return result;
}

polynomial operator*(const ll a, const polynomial &p2) {
    polynomial result(p2);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = polynomial::mul(result[i], a);
    }
    while (result.size() > 7) {
        result.digits.pop_back();
    }
    return result;
}

const ll polynomial::get(size_t i) const {
    return size() > i ? (*this)[i] : 0;
}


ll polynomial::add(ll &a, ll b) {
    return (a + b);
}

ll polynomial::add(ll &&a, ll b) {
    return add(a, b);
}

ll polynomial::sub(ll& a, ll b) {
    return (a - b);
}

ll polynomial::sub(ll &&a, ll b) {
    return sub(a, b);
}

ll polynomial::mul(ll &a, ll b) {
    return (a * b);
}

ll polynomial::mul(ll &&a, ll b) {
    return mul(a, b);
}

ll polynomial::binpow(ll &a, ll n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return a;
    }
    ll b = binpow(a, n / 2);
    return (n % 2 == 1 ? a : 1) * b * b;
}

polynomial binpowp(polynomial &a, ll n) {
    if (n == 0) {
        return polynomial(std::vector<ll> (1, 1ll));
    }
    if (n == 1) {
        return a;
    }
    polynomial b = binpowp(a, n / 2);
    return (n % 2 == 1 ? a : polynomial(std::vector<ll>(1, 1ll))) * b * b;
}

polynomial binpowp(polynomial &&a, ll n) {
    if (n == 0) {
        return polynomial(std::vector<ll> (1, 1ll));
    }
    if (n == 1) {
        return a;
    }
    polynomial b = binpowp(a, n / 2);
    return (n % 2 == 1 ? a : polynomial(std::vector<ll>(1, 1ll))) * b * b;
}

ll polynomial::binpow(ll &&a, ll n) {
    return binpow(a, n);
}

ll polynomial::div_(ll &a, ll b) {
    return a / b;
}

ll polynomial::div_(ll &&a, ll b) {
    return div_(a, b);
}
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

const int SZ = 7;

struct evaluateable {
    virtual vector<ll> evaluate() {
        throw runtime_error("Unreachable state");
    };

};

struct Element : evaluateable {
    vector<ll> evaluate() override {
        return {0, 1, 0, 0, 0, 0, 0};
    }
};

struct Pair : evaluateable {
    evaluateable *X;
    evaluateable *Y;

    Pair(evaluateable *x, evaluateable *y) : X(x), Y(y) {}

    vector<ll> evaluate() override {
        vector<ll> p(SZ);
        vector<ll> x = X->evaluate();
        vector<ll> y = Y->evaluate();
        for (int i = 0; i < SZ; ++i) {
            for (int j = 0; j <= i; ++j) {
                p[i] += x[j] * y[i - j];
            }
        }
        return p;
    }
};

struct List : evaluateable {
    evaluateable *X;

    explicit List(evaluateable *x) : X(x) {}

    vector<ll> evaluate() override {
        vector<ll> l(SZ);
        vector<ll> x = X->evaluate();
        l[0] = 1;
        for (int i = 1; i < SZ; ++i) {
            for (int j = 1; j <= i; ++j) {
                l[i] += x[j] * l[i - j];
            }
        }
        return l;
    }
};

struct Set : evaluateable {
    evaluateable *X;

    explicit Set(evaluateable *x) : X(x) {}

    vector<ll> evaluate() override {
        vector<ll> s(SZ);
        vector<ll> x = X->evaluate();
        s[0] = 1;
        polynomial denom(vector<ll>(1,1ll));
        for (int i = 1; i < SZ; ++i) {
            polynomial q(SZ);
            q[0] = 1;
            q[i] = -1;
            q = binpowp(q, x[i]);
            denom = denom * q;
        }
        for (int i = 1; i < SZ; ++i) {
            for (int j = 1; j <= i; ++j) {
                s[i] += -denom.get(j) * s[i - j];
            }
        }
        return s;
    }
};

class Parser {
    string s;
    int i = 0;

public:
    explicit Parser(string s) : s(std::move(s)) {}

    evaluateable* get_token() {
        if (s[i] == 'P') {
            i += 2;
            evaluateable *A = get_token();
            ++i;
            evaluateable *B = get_token();
            ++i;
            return new Pair(A, B);
        } else if (s[i] == 'S') {
            i += 2;
            evaluateable *A = get_token();
            ++i;
            return new Set(A);
        } else if (s[i] == 'L') {
            i += 2;
            evaluateable *A = get_token();
            ++i;
            return new List(A);
        } else if (s[i] == 'B') {
            ++i;
            return new Element();
        } else {
            throw runtime_error("Unexpected object");
        }
    }

    evaluateable* parse() {
        return get_token();
    }
};

int main() {
    string s;
    cin >> s;
    vector<ll> ans = Parser(s).parse()->evaluate();
    for (int i = 0; i < SZ; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}