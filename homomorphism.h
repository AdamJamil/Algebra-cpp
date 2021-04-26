#ifndef ALGEBRA_HOMOMORPHISM_H
#define ALGEBRA_HOMOMORPHISM_H

#include "definitions.h"
#include "function.h"
#include "group.h"
#include "element.h"

// G and H are groups - elem_G and elem_H are the group elements
template<class G, class H, class elem_G = typename G::element, class elem_H = typename H::element>
class homomorphism : virtual public function<elem_G, elem_H> { // function will do mapping on group elements
public:
    typedef typename G::label lab_G; // labels in domain
    typedef typename H::label lab_H; // and range
    G domain;
    H range, image;

    homomorphism(function<elem_G, elem_H> f, G domain_, H range_)
        : function<elem_G, elem_H>(f), domain(domain_), range(range_), image(set<lab_H>{}, range_.compose) {
        for (auto &x : domain_) for (auto &y : domain_)
            assert(("Homomorphism property not satisfied.", f[x * y] == f[x] * f[y]));
        for (auto &x : domain_) image.insert(f[x]);
    }

    static function<elem_G, elem_H> wrap_function(function<lab_G, lab_H> f, G domain, H range) {
        std::unordered_map<elem_G, elem_H> wrapped_map;
        for (auto &x : f.domain) wrapped_map.insert({elem_G(x, &domain.compose), elem_H(f[x], &range.compose)});
        return wrapped_map;
    }

    homomorphism(function<lab_G, lab_H> f, G domain_, H range_)
        : homomorphism(wrap_function(f, domain_, range_), domain_, range_) {}
};


template<class G, class H, class elem_G = typename G::element, class elem_H = typename H::element>
class epimorphism : virtual public homomorphism<G, H>, virtual public surjection<elem_G, elem_H> {
public:
    typedef typename G::label lab_G; // labels in domain
    typedef typename H::label lab_H; // and range
    epimorphism(function<elem_G, elem_H> f, G domain_, H range_):
        function<elem_G, elem_H>(f, domain_, range_),
        homomorphism<G, H>(f, domain_, range_),
        surjection<elem_G, elem_H>(function<elem_G, elem_H>(f, domain_, range_)) {
    }

    epimorphism(function<lab_G, lab_H> f, G domain_, H range_)
            : epimorphism(homomorphism<G, H>::wrap_function(f, domain_, range_), domain_, range_) {}
};


template<class G, class H, class elem_G = typename G::element, class elem_H = typename H::element>
class monomorphism : virtual public homomorphism<G, H>, virtual public injection<elem_G, elem_H> {
public:
    typedef typename G::label lab_G; // labels in domain
    typedef typename H::label lab_H; // and range
    monomorphism(function<elem_G, elem_H> f, G domain_, H range_):
            function<elem_G, elem_H>(f, domain_, range_),
            homomorphism<G, H>(f, domain_, range_),
            injection<elem_G, elem_H>(function<elem_G, elem_H>(f, domain_, range_)) {
    }

    monomorphism(function<lab_G, lab_H> f, G domain_, H range_)
            : monomorphism(homomorphism<G, H>::wrap_function(f, domain_, range_), domain_, range_) {}
};


template<class G, class H, class elem_G = typename G::element, class elem_H = typename H::element>
class isomorphism : virtual public homomorphism<G, H>, virtual public injection<elem_G, elem_H>, virtual public surjection<elem_G, elem_H> {
public:
    typedef typename G::label lab_G; // labels in domain
    typedef typename H::label lab_H; // and range
    isomorphism(function<elem_G, elem_H> f, G domain_, H range_):
            function<elem_G, elem_H>(f, domain_, range_),
            homomorphism<G, H>(f, domain_, range_),
            injection<elem_G, elem_H>(function<elem_G, elem_H>(f, domain_, range_)),
            surjection<elem_G, elem_H>(function<elem_G, elem_H>(f, domain_, range_)) {
    }

    isomorphism(function<lab_G, lab_H> f, G domain_, H range_)
            : isomorphism(homomorphism<G, H>::wrap_function(f, domain_, range_), domain_, range_) {}
};

#endif //ALGEBRA_HOMOMORPHISM_H
