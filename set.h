#ifndef ALGEBRA_SET_H
#define ALGEBRA_SET_H

#include "definitions.h"

template<class E>
class set : public std::set<E> {
public:
    // largest chain of inclusions ending at this set
    int recursive_depth = 0;
    // prints out all elements in group
    friend std::ostream& operator<<(std::ostream& out, const set<E>& g) {
        out << "[";
        for (auto val : g.s) {
            if (val != *g.s.begin()) out << ", ";
            out << val;
        }
        return out << "]";
    }

    template<class C, class T = typename C::value_type> // this template ensures we have a container of type T
    set(C gen) : std::set<E>(gen) {
        static_assert(std::is_same_v<E, T>, "Wrong type passed to group constructor.");
    }
};


#endif //ALGEBRA_SET_H
