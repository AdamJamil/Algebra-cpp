#ifndef ALGEBRA_ELEMENT_H
#define ALGEBRA_ELEMENT_H

#include "definitions.h"

class Int {
public:
    // [v]_n = equivalence class of v, mod n
    int v, n;
    Int(int v, int n) { this->v = v; this->n = n; };

    [[nodiscard]] Int dot(Int const &b) const;

    bool operator==(const Int& rhs) const { return v == rhs.v; }
    bool operator<(const Int& rhs) const { return v < rhs.v; }
    friend std::ostream& operator <<(std::ostream& os, const Int& b) { return os << b.v; }
};

class Perm {
public:
    // p is a bijection from [n] to [n]
    int n;
    std::vector<int> p;
    // cycle_lengths is lengths of all nonzero cycles; used in sorting sensibly
    // first element is actually number of cycles; rest of vector is as expected
    std::vector<int> cycle_lengths;
    // cycle notation for S_n
    std::string name;
    Perm(std::vector<int> p);

    [[nodiscard]] Perm dot(Perm const &b) const;

    bool operator==(const Perm& rhs) const { return p == rhs.p; }
    bool operator<(const Perm& rhs) const;
    friend std::ostream& operator <<(std::ostream& os, const Perm& b);
};

#endif //ALGEBRA_ELEMENT_H
