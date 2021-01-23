#include <set>
#include "definitions.h"
#include "iostream"
using namespace std;

#ifndef ALGEBRA_GROUP_H
#define ALGEBRA_GROUP_H

template<class E>
class group {
public:
    set<E> s;
    friend ostream& operator<<(ostream& out, const group<E>& g) {
        out << "[";
        int i = 0;
        for (auto ptr = g.s.begin(); i < g.s.size() - 1; ++ptr, ++i) out << *ptr << ", ";
        if (g.s.size()) out << *g.s.rbegin();
        return out << "]";
    }

    explicit group(set<E> gen) {
        if (gen.empty()) return;
        s = gen;
        set<E> curr{s}, nxt;
        E temp = *gen.begin();
        while (!curr.empty()) {
            tr(x, s) tr(y, curr) if (!s.count(temp = x.dot(y))) nxt.insert(temp);
            tr(y, s) tr(x, curr) if (!s.count(temp = x.dot(y))) nxt.insert(temp);
            tr(x, nxt) s.insert(x);
            curr = nxt;
            nxt.clear();
        }
    }
};



#endif //ALGEBRA_GROUP_H
