#include <set>
#include "definitions.h"
#include "iostream"

#ifndef ALGEBRA_GROUP_H
#define ALGEBRA_GROUP_H

// adds all elements from X*Y to s
template<class E>
void direct_product(set<E> &s, set<E> &nxt, set<E> &X, set<E> &Y, E &temp) {
    tr(x, X) tr(y, Y) if (!s.count(temp = x.dot(y))) nxt.insert(temp);
}

// templated group class
template<class E>
class group {
public:
    // elements in group
    set<E> s;

    // prints out all elements in group
    friend ostream& operator<<(ostream& out, const group<E>& g) {
        out << "[";
        for (auto val : g.s) {
            if (!(val == *g.s.begin())) out << ", ";
            out << val;
        }
        return out << "]";
    }

    // constructor/algorithm to find group generated by {gen}
    explicit group(set<E> gen) {
        if (gen.empty()) return;
        s = gen;
        set<E> curr{s}, nxt;
        E temp = *gen.begin();
        while (!curr.empty()) {
            direct_product(s, nxt, curr, curr, temp);
            direct_product(s, nxt, curr, s, temp);
            direct_product(s, nxt, s, curr, temp);
            s.insert(nxt.begin(), nxt.end());
            curr = nxt;
            nxt.clear();
        }
    }
};


#endif //ALGEBRA_GROUP_H
