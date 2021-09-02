//
// Created by Alexey Shik on 15.04.2021.
//

#include <istream>
#include <vector>
#include <cassert>

typedef long long ll;

using namespace std;

#ifndef DM_GF_FRAC_H
#define DM_GF_FRAC_H

struct frac {
    ll nom;
    ll denom;

    frac();

    frac(ll nom, ll denom) : nom(nom), denom(denom) {}

    frac(frac &other) = default;

    frac(const frac &other) = default;

    friend frac operator+(const frac &f1, const frac &f2);

    friend frac operator-(const frac &f1, const frac &f2);

    friend frac operator*(ll a, const frac &f);

    friend frac operator*(const frac &f1, const frac &f2);

    friend frac operator/(const frac &f1, const frac &f2);

    friend std::ostream &operator<<(std::ostream &out, frac &f);

    void simplify();
};

#endif

ll gcd(ll a, ll b) {
    return a == 0 ? b : gcd(b % a, a);
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

frac operator+(const frac &f1, const frac &f2) {
    frac result{};
    ll l = lcm(f1.denom, f2.denom);
    result.nom = f1.nom * (l / f1.denom) + f2.nom * (l / f2.denom);
    result.denom = l;
    return result;
}

frac operator-(const frac &f1, const frac &f2) {
    frac f3 = frac(-f2.nom, f2.denom);
    return f1 + f3;
}

frac operator*(ll a, const frac &f) {
    frac result(f);
    ll d = gcd(a, f.denom);
    result.denom /= d;
    result.nom *= a / d;
    return result;
}

frac operator*(const frac &f1, const frac &f2) {
    frac result{};
    ll d_ad = gcd(f1.nom, f2.denom);
    ll d_bc = gcd(f2.nom, f1.denom);
    result.nom = (f1.nom / d_ad) * (f2.nom / d_bc);
    result.denom = (f2.denom / d_ad) * (f1.denom / d_bc);
    return result;
}

frac operator/(const frac &f1, const frac &f2) {
    frac f3(f2.denom, f2.nom);
    return f1 * f3;
}

std::ostream &operator<<(std::ostream &out, frac &f) {
    return out << f.nom << '/' << f.denom << ' ';
}

std::ostream &operator<<(std::ostream &out, const frac &f) {
    return out << f.nom << '/' << f.denom << ' ';
}

void frac::simplify() {
    ll d = gcd(nom, denom);
    nom /= d;
    denom /= d;
    if (denom < 0) {
        nom *= -1;
        denom *= -1;
    }
}

frac::frac() {
    nom = 0;
    denom = 1;
}

#ifndef DM_GF_POLYNOMIAL_H
#define DM_GF_POLYNOMIAL_H


class polynomial {

public:
    std::vector<frac> digits;

    void shrink_to_fit();

    frac get(size_t i) const;

    polynomial();

    explicit polynomial(size_t size);

    explicit polynomial(std::vector<frac> digits);

    polynomial(polynomial const &other) = default;

    friend std::ostream &operator<<(std::ostream &out, polynomial &p);

    friend std::ostream &operator<<(std::ostream &out, polynomial &&p);

    friend polynomial operator+(const polynomial &p1, const polynomial &p2);

    friend polynomial operator-(const polynomial &p1, const polynomial &p2);

    friend polynomial operator*(const frac &a, const polynomial &p);

    friend polynomial operator*(ll a, const polynomial &p);

    friend polynomial operator*(const polynomial &p1, const polynomial &p2);

    friend polynomial operator/(const polynomial &p1, const polynomial &p2);

    frac &operator[](size_t i);

    frac operator[](size_t i) const;

    polynomial operator-();

    size_t size() const;
};

#endif //DM_GF_POLYNOMIAL_H

#include <iostream>

//
// Created by Alexey Shik on 11.04.2021.
//

polynomial::polynomial() : digits() {}

polynomial::polynomial(size_t size) : digits(size) {}

polynomial::polynomial(std::vector<frac> digits) : digits(std::move(digits)) {}

std::istream &operator>>(std::istream &in, polynomial &p) {
    return in;
}

std::ostream &operator<<(std::ostream &out, polynomial &p) {
    out << p.size() - 1 << std::endl;
    for (frac digit : p.digits) {
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
        result[i] = result[i] + p1[i];
    }
    for (int i = 0; i < p2.size(); ++i) {
        result[i] = result[i] + p2[i];
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
            result[i] = result[i] + (p1.get(j) * p2.get(i - j));
        }
    }
    result.shrink_to_fit();
    return result;
}


polynomial operator/(const polynomial &p1, const polynomial &p2) {
    polynomial result(1000);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = p1.size() > i ? p1[i] : frac(0, 1);
        for (int j = 0; j < i; ++j) {
            result[i] = result[i] - result[j] * p2.get(i - j);
        }
        result[i] = result[i] / p2[0];
    }
    return result;
}


size_t polynomial::size() const {
    return digits.size();
}

frac &polynomial::operator[](size_t i) {
    return digits[i];
}

frac polynomial::operator[](size_t i) const {
    return digits[i];
}

void polynomial::shrink_to_fit() {}

polynomial polynomial::operator-() {
    polynomial result(*this);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = (-1) * result[i];
    }
    return result;
}

polynomial operator*(const ll a, const polynomial &p2) {
    polynomial result(p2);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = a * result[i];
    }
    return result;
}

polynomial operator*(const frac &a, const polynomial &p2) {
    polynomial result(p2);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = a * result[i];
    }
    return result;
}

frac polynomial::get(size_t i) const {
    return size() > i ? (*this)[i] : frac(0, 1);
}

int main() {
    ll r, k;
    cin >> r >> k;
    vector<polynomial> choose(11);
    vector<ll> fact(11, 1);
    for (ll i = 1; i < 11; ++i) {
        fact[i] = fact[i - 1] * i;
    }
    for (ll i = 0; i < 11; ++i) {
        choose[i] = polynomial(vector(1, frac(1, 1)));
        for (ll t = -i + 1; t <= -i + k; ++t) {
            polynomial p(2);
            p[0] = {t, 1};
            p[1] = {1, 1};
            choose[i] = choose[i] * p;
        }
        choose[i] = frac(1, fact[k]) * choose[i];
        while (choose[i].size() > 1 && choose[i].digits.back().nom == 0) {
            choose[i].digits.pop_back();
        }
    }
    vector<ll> pows(11, 1);
    for (ll i = 1; i < 11; ++i) {
        pows[i] = pows[i - 1] * r;
    }
    polynomial f{};
    for (ll i = 0; i <= k; ++i) {
        ll c;
        cin >> c;
        f = f + frac(c, pows[i]) * choose[i];
        while (f.size() > 1 && f.digits.back().nom == 0) {
            f.digits.pop_back();
        }
    }
    for (ll i = 0; i <= k; ++i) {
        f[i].simplify();
        cout << f.get(i);
    }
    return 0;
}