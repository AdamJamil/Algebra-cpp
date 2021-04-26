#ifndef ALGEBRA_SET_H
#define ALGEBRA_SET_H

#include "definitions.h"

template<class E>
class set : virtual public std::unordered_set<E> {
public:
    typedef E value_type;
    // largest chain of inclusions ending at this set
    int recursive_depth = 0;

    set() = default;

    template<class C, class T = typename C::value_type> // this template ensures we have a container of type T
    set(C gen) : std::unordered_set<E>(gen) {
        static_assert(std::is_same_v<E, T>, "Wrong type passed to group constructor.");
    }
};


#endif //ALGEBRA_SET_H
