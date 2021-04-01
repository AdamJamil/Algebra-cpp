#ifndef ALGEBRA_FUNCTION_H
#define ALGEBRA_FUNCTION_H

#include "definitions.h"
#include "set.h"

template<class D, class R>
class function : public std::unordered_map<D, R> {
public:
    set<D> domain;
    set<R> range, image;

    friend std::ostream& operator<<(std::ostream& out, const function<D, R>& g);

    function(std::unordered_map<D, R> map);
    function(std::unordered_map<D, R> map, set<D> range_);
    function(std::unordered_map<D, R> map, set<D> domain_, set<R> range_);
    function() = default;
};

template<class D, class R>
class surjection : virtual public function<D, R> {
public:
    surjection(function<D, R> func);
};

template<class D, class R>
class injection : virtual public function<D, R> {
public:
    injection(function<D, R> func);
};

template<class D, class R>
class bijection : virtual public surjection<D, R>, injection<D, R> {
public:
    bijection(function<D, R> func);
};




#endif //ALGEBRA_FUNCTION_H
