//
// Created by Alexey Shik on 11.04.2021.
//

#include "polynomial.h"

#include <utility>

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

polynomial operator*(const ll a, const polynomial &p2) {
    polynomial result(p2);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = polynomial::mul(result[i], a);
    }
    return result;
}
