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

private:


public:
    std::vector<ll> digits;
    static const ll MOD = 998244353;

    void shrink_to_fit();
    const frac get(size_t i) const;
    polynomial();
    explicit polynomial(size_t size);
    explicit polynomial(std::vector<ll> digits);
    polynomial(polynomial const &other) = default;
    friend std::istream &operator>>(std::istream &in, polynomial &p);
    friend std::ostream &operator<<(std::ostream &out, polynomial &p);
    friend std::ostream &operator<<(std::ostream &out, polynomial &&p);
    friend polynomial operator+(const polynomial &p1, const polynomial &p2);
    friend polynomial operator-(const polynomial &p1, const polynomial &p2);
    friend polynomial operator*(const ll a, const polynomial &p);
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
        result[i] = mul(result[i], MOD - 1);
    }
    return result;
}

polynomial operator*(const ll a, const polynomial &p2) {
    polynomial result(p2);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = polynomial::mul(result[i], a);
    }
    return result;
}

const frac polynomial::get(size_t i) const {
    return size() > i ? (*this)[i] : 0;
}


ll polynomial::add(ll &a, ll b) {
    return (a + b) % MOD;
}

ll polynomial::add(ll &&a, ll b) {
    return add(a, b);
}

ll polynomial::sub(ll& a, ll b) {
    return (a + MOD - b) % MOD;
}

ll polynomial::sub(ll &&a, ll b) {
    return sub(a, b);
}

ll polynomial::mul(ll &a, ll b) {
    return (a * b) % MOD;
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
    return ((n % 2 == 1 ? a : 1) * ((b * b) % MOD)) % MOD;
}

ll polynomial::binpow(ll &&a, ll n) {
    return binpow(a, n);
}

ll polynomial::div_(ll &a, ll b) {
    return mul(a, binpow(b, MOD - 2));
}

ll polynomial::div_(ll &&a, ll b) {
    return div_(a, b);
}

using namespace std;

void make_sqrt(vector<polynomial> &pols, int m) {
    polynomial result = polynomial(vector(1, 1ll));
    ll c = polynomial::div_(1, 2);
    if (m > 1) {
        result = result + c * pols[1];
    }
    for (int i = 2; i < m; ++i) {
        c = polynomial::mul(c, 2 * i - 3);
        c = polynomial::mul(c, polynomial::MOD - 1);
        c = polynomial::div_(c, 2 * i);
        result = result + c * pols[i];
    }
    for (int i = 0; i < m; ++i) {
        cout << result.get(i) << ' ';
    }
    cout << endl;
}

void make_exp(vector<polynomial> &pols, int m) {
    polynomial result = polynomial(vector(1, 1ll));
    ll c = 1;
    for (int i = 1; i < m; ++i) {
        c = polynomial::div_(c, i);
        result = result + c * pols[i];
    }
    for (int i = 0; i < m; ++i) {
        cout << result.get(i) << ' ';
    }
    cout << endl;
}

void make_ln(vector<polynomial> &pols, int m) {
    polynomial result = polynomial(2);
    result[0] = 0;
    if (m > 1) {
        result = result + pols[1];
    }
    ll c = 1;
    for (int i = 2; i < m; ++i) {
        c = polynomial::mul(c, polynomial::MOD - 1);
        c = polynomial::mul(c, i - 1);
        c = polynomial::div_(c, i);
        result = result + c * pols[i];
    }
    for (int i = 0; i < m; ++i) {
        cout << result.get(i) << ' ';
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> v(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        cin >> v[i];
    }
    vector<polynomial> pols(m);
    pols[0] = polynomial(vector(1, 1ll));
    if (m > 1) {
        pols[1] = polynomial(v);
    }
    for (int i = 2; i < m; ++i) {
        pols[i] = pols[i - 1] * pols[1];
        while (pols[i].size() > m) {
            pols[i].digits.pop_back();
        }
    }
    make_sqrt(pols, m);
    make_exp(pols, m);
    make_ln(pols, m);
    return 0;
}