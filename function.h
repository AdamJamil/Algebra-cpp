#ifndef ALGEBRA_FUNCTION_H
#define ALGEBRA_FUNCTION_H

#include "definitions.h"
#include "set.h"


template<class D, class R>
class function : public std::unordered_map<D, R> {
public:
    set<D> domain;
    set<R> range, image;

    // print mapping
    friend std::ostream& operator<<(std::ostream& out, const function<D, R>& g) {
        out << "[";
        for (auto val : g) {
            if (val != *g.begin()) out << ", ";
            out << val;
        }
        return out << "]";
    }

    function() = default;

    // if no domain/range given, assume that domain is domain of map, range is image
    function(std::unordered_map<D, R> map) : std::unordered_map<D, R>(map) {
        for (auto &v : map) domain.insert(v.first), image.insert(v.second), range.insert(v.second);
    }

    // if range given, calculate image but not range
    function(std::unordered_map<D, R> map, set<D> range_) {
        this->range = range_;
        for (auto &v : map) {
            assert(("Function takes on value outside of range", range.count(v.second)));
            domain.insert(v.first), image.insert(v.second);
        }
    }

    function(std::unordered_map<D, R> map, set<D> domain_, set<R> range_) : function(map, range_) {
        for (auto &v : domain_) assert(("Function is not defined on entire domain.", domain.count(v)));
        for (auto &v : domain) assert(("Function defined on value outside of domain.", domain_.count(v)));
    }
};

template<class D, class R>
class surjection : virtual public function<D, R> {
public:
    surjection() : function<D, R>() {};
    // must ensure that function is surjective during conversion
    surjection(function<D, R> func) : function<D, R>(func) {
        assert(("Function is not surjective; cannot cast", func.range == func.image));
    };
};

template<class D, class R>
class injection : virtual public function<D, R> {
public:
    injection() : function<D, R>() {};
    // must ensure that function is injective during conversion
    injection(function<D, R> func) : function<D, R>(func) {
        assert(("Function is not injective; cannot cast", func.image.size() == func.domain.size()));
    };
};

template<class D, class R>
class bijection : virtual public surjection<D, R>, virtual public injection<D, R> {
public:
    bijection() : function<D, R>(), surjection<D, R>(), injection<D, R>() {};
    // must ensure that function is surjective and injective during conversion
    bijection(function<D, R> func) : function<D, R>(func), surjection<D, R>(func), injection<D, R>(func) {};
};



#endif //ALGEBRA_FUNCTION_H
