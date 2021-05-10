#ifndef ALGEBRA_FUNCTION_H
#define ALGEBRA_FUNCTION_H

#include "definitions.h"
#include "set.h"


template<class D, class R>
class function : public std::unordered_map<D, R> {
public:
    set<D> domain;
    set<R> range;

    function() = default;

    function(std::unordered_map<D, R> map) : std::unordered_map<D, R>(map) {}

    function(std::unordered_map<D, R> map, set<R> range_) : function(map, range_) {
        if (CHECK_ALL) TR(x, map) assert(("Function output outside of range", range_.count(x.second)));
    }
};

template<class D, class R>
class surjection : virtual public function<D, R> {
public:
    surjection() : function<D, R>() {};

    surjection(function<D, R> func) : function<D, R>(func) {
        if (CHECK_ALL) { // ensure surjectivity during cast
            set<R> image;
            TR(x, this->domain) image.insert(func[x]);
            assert(("Function is not surjective; cannot cast", func.range == image));
        }
    };
};

template<class D, class R>
class injection : virtual public function<D, R> {
public:
    injection() : function<D, R>() {};
    injection(function<D, R> func) : function<D, R>(func) {
        if (CHECK_ALL) { // ensure injectivity during cast
            set<R> image;
            TR(x, this->domain) image.insert(func[x]);
            assert(("Function is not injective; cannot cast", image.size() == func.domain.size()));
        }
    };
};

template<class D, class R>
class bijection : virtual public surjection<D, R>, virtual public injection<D, R> {
public:
    bijection() : function<D, R>(), surjection<D, R>(), injection<D, R>() {};
    bijection(function<D, R> func) : function<D, R>(func), surjection<D, R>(func), injection<D, R>(func) {};
};



#endif //ALGEBRA_FUNCTION_H
