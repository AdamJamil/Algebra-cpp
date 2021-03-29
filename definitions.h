#ifndef ALGEBRA_DEFINITIONS_H
#define ALGEBRA_DEFINITIONS_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <numeric>
#include <cstring>
#include <algorithm>
#include <iterator>

#define F(i,n) for (int i = 0; i < n; ++i)
#define TR(x, v) for (auto &x:v)
#define A(x) (x).begin(), (x).end()

// overrides << for vectors
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << '{';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
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
#define D(x) do { std::cerr << x; } while (0);


typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<int> vi;

#endif //ALGEBRA_DEFINITIONS_H
