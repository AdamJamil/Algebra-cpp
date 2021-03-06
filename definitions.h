#ifndef ALGEBRA_DEFINITIONS_H
#define ALGEBRA_DEFINITIONS_H

//#define CHECK_ALL_FLAG // imagine wanting your code to be slow 😹😹😹😹😹

#ifdef CHECK_ALL_FLAG
    constexpr bool CHECK_ALL = true;
#else
    constexpr bool CHECK_ALL = false;
#endif

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

namespace CHECK
{
    struct No {};
    template<typename T, typename Arg> No operator<(const T&, const Arg&);

    template<typename T, typename Arg = T>
    struct LessExists { enum { value = std::is_same<decltype(std::declval<T>() < std::declval<Arg>()), No>::value }; };
}

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
    if constexpr (CHECK::LessExists<T>::value)
        sort(A(c));
    return out << c;
}

// overrides << for unordered_maps
template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::unordered_map<K, V>& v) {
    std::vector<std::pair<K, V>> c(A(v));
    if constexpr (CHECK::LessExists<std::pair<K, V>>::value and CHECK::LessExists<K>::value and CHECK::LessExists<V>::value)
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
