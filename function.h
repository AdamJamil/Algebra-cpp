#ifndef ALGEBRA_FUNCTION_H
#define ALGEBRA_FUNCTION_H

#include "definitions.h"

template<class D, class R>
class function : public std::unordered_map<D, R> {
public:
    set<D> domain;
    set<R> image;

    // print mapping
    friend std::ostream& operator<<(std::ostream& out, const function<D, R>& g) {
        out << "[";
        for (auto val : g) {
            if (val != *g.begin()) out << ", ";
            out << val;
        }
        return out << "]";
    }

    function(std::unordered_map<D, R> m) : std::unordered_map<D, R>(m) {
        for (auto &v : m) domain.insert(v.first), image.insert(v.second);
    }
};

#endif //ALGEBRA_FUNCTION_H
