#ifndef ALGEBRA_DEFINITIONS_H
#define ALGEBRA_DEFINITIONS_H

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <numeric>
#include <cstring>
#include <algorithm>
#include <iterator>
#include "assert.h"

#define F(i,n) for (int i = 0; i < n; ++i)
#define TR(x, v) for (auto &x:v)
#define A(x) (x).begin(), (x).end()

// overrides << for vectors
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << '{';
    for (auto ptr = v.begin(); ptr != v.end(); ptr++)
        out << *ptr << ", ";
    out << "\b\b}";
    return out;
}

// overrides << for sets
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& v) {
    out << '{';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b}";
    return out;
}

// overrides << for pairs
template <typename T, typename V>
std::ostream& operator<<(std::ostream& out, const std::pair<T, V>& v) {
    out << '(' << v.first << ", " << v.second << ")";
    return out;
}

#define D(x) do { std::cerr << #x << " = " << x << std::endl; } while (0);


typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<std::pair<ll, ll>> vpl;
typedef std::vector<int> vi;
typedef std::set<ll> sl;

#endif //ALGEBRA_DEFINITIONS_H
