#include <iostream>
#include <vector>
#include <cstring>
#include "element.h"
#include "definitions.h"

// --------------------------------------- Int ------------------------------------------- //
// composition in Z_n is just addition mod n
Int Int::dot(Int const &b) const { return Int((this->v + b.v) % this->n, this-> n); }

// --------------------------------------- Perm ------------------------------------------ //
// constructor for permutation - also generates string name for element, and cycle_lengths
// TODO: huge performance boost via moving computation of string name to printing
//      - have to do something about const in << operator!
Perm::Perm(int n, std::vector<int> p, bool dec) {
    // dec true if 1-indexed
    if (dec) tr(x, p) x--;
    this->n = n; this->p = p;

    // find all cycles
    bool used[n];
    memset(used, false, sizeof used);
    F(i,n) if (!used[i] and p[i] != i) {
        int curr = 1;
        name += "(" + std::to_string(i + 1);
        used[i] = true;
        while (!used[i = p[i]]) name += std::to_string(i + 1), used[i] = true, curr++;
        name += ")";
        cycle_lengths.push_back(curr);
    }

    cycle_lengths.insert(cycle_lengths.begin(), cycle_lengths.size());

    if (name.empty())
        name = "e";
}

Perm Perm::dot(Perm const &b) const {
    std::vector<int> res(n);
    // compose permutation
    F(i,n) res[i] = p[b.p[i]];
    return Perm(n, res, false);
}

// first compare number of cycles; fewer means smaller.
//     if equal, compare lexicographically lengths of cycles
//     if equal, finally compare actual permutaiton
bool Perm::operator<(const Perm &rhs) const {
    return (cycle_lengths == rhs.cycle_lengths) ? p < rhs.p : cycle_lengths < rhs.cycle_lengths;
}

std::ostream &operator<<(std::ostream &os, const Perm &b) {
    return os << b.name;
}
