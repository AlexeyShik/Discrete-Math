//
// Created by Alexey Shik on 11.04.2021.
//

#ifndef DM_GF_POLYNOMIAL_H
#define DM_GF_POLYNOMIAL_H


#include <istream>
#include <vector>

typedef long long ll;

class polynomial {

private:
    std::vector<ll> digits;

    void shrink_to_fit();
    const frac get(size_t i) const;

public:
    static const ll MOD = 998244353;

    polynomial();
    explicit polynomial(size_t size);
    explicit polynomial(std::vector<ll> digits);
    polynomial(polynomial const &other) = default;
    friend std::istream &operator>>(std::istream &in, polynomial &p);
    friend std::ostream &operator<<(std::ostream &out, polynomial &p);
    friend std::ostream &operator<<(std::ostream &out, polynomial &&p);
    friend polynomial operator+(const polynomial &p1, const polynomial &p2);
    friend polynomial operator-(const polynomial &p1, const polynomial &p2);
    friend polynomial operator*(const polynomial &p1, const polynomial &p2);
    friend polynomial operator*(const ll a, const polynomial &p);
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
