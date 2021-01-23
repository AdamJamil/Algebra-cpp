#include <iostream>
#include "element.h"

// --------------------------------------- Int ------------------------------------------- //
Int::Int(int v, int n) { this->v = v; this->n = n; this->cmp = v; }
Int Int::dot(Int b) const { return Int((this->v + b.v) % this->n, this-> n); }

std::ostream &Int::doprint(std::ostream &os) const {
    return os << this->v;
}
