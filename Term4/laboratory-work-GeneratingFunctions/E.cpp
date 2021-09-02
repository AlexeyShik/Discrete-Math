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

ll polynomial::binpow(ll &&a, ll n) {
    return binpow(a, n);
}

ll polynomial::div_(ll &a, ll b) {
    return a / b;
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

fraction gen_frac(ll r, const polynomial &pi) {
    size_t k = pi.size() - 1;
    fraction result;
    polynomial tmp(2);
    tmp[0] = 1;
    tmp[1] = -r;
    for (int i = 0; i <= k; ++i) {
        result.denom = result.denom * tmp;
    }
    vector<ll> f(k + 1, 0);
    for (ll i = 0; i <= k; ++i) {
        f[i] = pi[k] * polynomial::binpow(i, (ll) k) * polynomial::binpow(r, i);
    }
    result.nom.digits.resize(k + 1);
    for (int i = 0; i <= k; ++i) {
        result.nom[i] = f[i];
        for (int j = 1; j <= i; ++j) {
            result.nom[i] += result.denom[j] * f[i - j];
        }
    }
    return result;
}

int main() {
    ll r;
    cin >> r;
    polynomial p;
    cin >> p;
    fraction result;
    polynomial tmp(2);
    tmp[0] = 1;
    tmp[1] = -r;
    for (int i = 0; i < p.size(); ++i) {
        polynomial pi(i + 1);
        pi[i] = p[i];
        fraction cur = gen_frac(r, pi);
        result.nom = result.nom * tmp + cur.nom;
        result.denom = cur.denom;
    }
    cout << result;
    return 0;
}
