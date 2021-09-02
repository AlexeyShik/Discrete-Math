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
    static const ll MOD = 104857601;

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

class fraction {
public:
    polynomial nom;
    polynomial denom;

    fraction() : nom(vector(1, 0ll)), denom(vector(1,  1ll)) {}
    fraction(const polynomial &nom, const polynomial &denom) : nom(nom), denom(denom) {}

    friend fraction operator+(const fraction &f1, const fraction &f2) {
        return fraction(f1.nom * f2.denom + f2.nom * f1.denom, f1.denom * f2.denom);
    }

    friend ostream &operator<<(ostream &out, fraction &f) {
        return out << f.nom << f.denom;
    }
};

ll calc(polynomial &q, vector<ll> &a, ll k) {
    if (k < a.size()) {
        return a[k];
    }
    for (int i = a.size(); i < 2 * q.size(); ++i) {
        a.push_back(0);
        for (int j = 1; j < q.size(); ++j) {
            a[i] = polynomial::add(a[i], polynomial::mul(a[i - j], polynomial::MOD - q[j]));
        }
    }
    polynomial qt = polynomial(q);
    for (int i = 0; i < qt.size(); ++i) {
        if (i % 2 == 1) {
            qt[i] = polynomial::MOD-qt[i];
        }
    }
    q = q * qt;
    for (int i = 2; i < q.size(); i += 2) {
        q[i / 2] = q[i];
        q[i] = 0;
    }
    q.shrink_to_fit();
    for (int i = 1; i < a.size(); ++i) {
        if (i % 2 == k % 2) {
            a[i / 2] = a[i];
        }
        a[i] = 0;
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return calc(q, a, k / 2);
}

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1), c(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    vector<ll> q(n + 1);
    q[0] = 1;
    for (int i = 1; i <= n; ++i) {
        q[i] = polynomial::MOD-c[i];
    }
    polynomial pq(q);
    cout << calc(pq, a, k);
    return 0;
}