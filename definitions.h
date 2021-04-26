#ifndef ALGEBRA_DEFINITIONS_H
#define ALGEBRA_DEFINITIONS_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <numeric>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <functional>
#include "assert.h"
#include <chrono>
#include "math.h"
using namespace std::chrono;


#define F(i,n) for (int i = 0; i < n; ++i)
#define TR(x, v) for (auto &x:v)
#define A(x) (x).begin(), (x).end()

// overrides << for vectors
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << '{';
    for (auto ptr = v.begin(); ptr != v.end(); )
        out << *ptr << (ptr++ == v.end() ? "" : ", ");
    out << "}";
    return out;
}

// overrides << for sets
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& v) {
    std::vector<T> c{v};
    sort(A(c));
    return out << c;
}

// overrides << for unordered_sets
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::unordered_set<T>& v) {
    std::vector<T> c(A(v));
    sort(A(c));
    return out << c;
}

// overrides << for pairs
template <typename T, typename V>
std::ostream& operator<<(std::ostream& out, const std::pair<T, V>& v) {
    out << '(' << v.first << ", " << v.second << ")";
    return out;
}

#define D(x) do { std::cerr << #x << " = " << x << std::endl; } while (0);


typedef int ll;
typedef long double ld;
typedef std::vector<ll> vl;
typedef std::vector<std::pair<ll, ll>> vpl;
typedef std::vector<int> vi;
typedef std::set<ll> sl;

template<typename R, typename D>
class bijection;

typedef bijection<ll, ll> perm;

extern vl PRIMES;

#endif //ALGEBRA_DEFINITIONS_H
