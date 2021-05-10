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
    H range;

    homomorphism(function<elem_G, elem_H> f, G domain_, H range_)
        : function<elem_G, elem_H>(f), domain(domain_), range(range_) {
        if (CHECK_ALL) for (auto &x : domain_) for (auto &y : domain_)
            assert(("Homomorphism property not satisfied.", f[x * y] == f[x] * f[y]));
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

namespace generate {
    template<class G, class H, class lab_G = typename G::label, class lab_H = typename H::label>
    void update_map(function<lab_G, lab_H> &f, lab_G const &x, std::unordered_map<lab_G, std::pair<lab_G, lab_G>> &par,
                    H &range) {
        if (f.count(x)) return;
        if (!f.count(par[x].first)) update_map<G, H>(f, par[x].first, par, range);
        if (!f.count(par[x].second)) update_map<G, H>(f, par[x].second, par, range);
        f.emplace(x, range.compose(f[par[x].first], f[par[x].second]));
        f.domain.insert(x);
    }

    template<class G, class H, class lab_G = typename G::label, class lab_H = typename H::label>
    std::vector<function<lab_G, lab_H>> backtrack_homomorphisms(G &domain, H &range, function<lab_G, lab_H> f,
                                                            std::vector<lab_G> gen,
                                                            std::vector<std::unordered_set<lab_G>> subgroups, ll idx,
                                                            std::unordered_map<lab_G, std::pair<lab_G, lab_G>> par) {
        std::vector<function<lab_G, lab_H>> ans;
        // want to map gen[idx] to something in range, and check if this is OK
        for (auto tar : range) {
            function<lab_G, lab_H> next_f(f); // TODO: (DBG_CHK) deep rather than shallow copy
            next_f.domain.insert(gen[idx]);
            next_f.emplace(gen[idx], tar.label);
            for (auto &x : subgroups[idx]) update_map<G, H>(next_f, x, par, range);
            // check OK
            bool ok = true;
            for (auto x : subgroups[idx]) for (auto y : subgroups[idx]) {
                ok &= next_f[domain.compose(x, y)] == range.compose(next_f[x], next_f[y]);
                if (!ok) goto done;
            }
            done:;
            if (ok and idx == gen.size() - 1) ans.push_back(next_f);
            else if (ok) {
                auto next = backtrack_homomorphisms(domain, range, next_f, gen, subgroups, idx + 1, par);
                ans.insert(ans.end(), A(next));
            }
        }
        return ans;
    }

    template<class G, class H>
    std::vector<homomorphism<G, H>> all_homomorphisms(G domain, H range) {
        typedef typename G::element elem_G;
        typedef typename H::element elem_H;
        typedef typename G::label lab_G;
        typedef typename H::label lab_H;
        auto gen = domain.generating_set();
        // given generating set, we need to have a structure that tells us how to extend homomorphism
        // for each <g_j>_{j <= i}. for each i, the added elements must be a product of two elements, and this
        // structure can be recursed on to solve the value of each f(x). the structure is simply a graph where every
        // x has indegree 0 or 2, and it is 2 precisely when it was computed as a product of two elements
        std::unordered_map<lab_G, std::pair<lab_G, lab_G>> par;
        std::unordered_set<lab_G> subgroup;
        std::vector<std::unordered_set<lab_G>> subgroups;
        for (auto &x : gen) {
            std::queue<lab_G> q;
            q.push(x);
            while (q.size()) {
                auto y = q.front();
                q.pop();
                if (subgroup.count(y)) continue;
                subgroup.insert(y);
                for (auto &s : gen) {
                    auto g1 = domain.compose(y, s), g2 = domain.compose(s, y);
                    if (!subgroup.count(g1) and !par.count(g1)) par.emplace(g1, std::pair<lab_G, lab_G>(y, s));
                    if (!subgroup.count(g2) and !par.count(g2)) par.emplace(g2, std::pair<lab_G, lab_G>(s, y));
                    q.push(g1), q.push(g2);
                    if (s == x) break;
                }
            }
            auto cp = subgroup;
            subgroups.push_back(cp);
        }
        std::vector<homomorphism<G, H>> ans;
        for (auto &f : backtrack_homomorphisms(domain, range, function<lab_G, lab_H>(), gen, subgroups, 0, par))
            ans.push_back(homomorphism<G, H>(f, domain, range));
        return ans;
    }
} // namespace generate

#endif //ALGEBRA_HOMOMORPHISM_H
