#ifndef ALGEBRA_GROUP_H
#define ALGEBRA_GROUP_H

#include "definitions.h"
#include "element.h"
#include "function.h"
#include "set.h"


// templated group class
template<class E>
class group : virtual public set<group_element<E>> {
public:
    typedef E label;
    typedef group_element<E> element;
    // composition rule
    std::function<E(E, E)> compose;

    group(const group<E> &g) = default;

    std::vector<E> generating_set() {
        std::vector<E> gen_set;
        set<element> subgroup;
        auto it = this->begin();
        while (subgroup.size() != this->size()) {
            while (subgroup.count(*it) or *it * *it == *it) it++;
            gen_set.push_back(it->label);
            subgroup = group(gen_set, this->compose);
        }
        return gen_set;
    }

    // constructor/algorithm to find group generated by {gen}
    template<class C, class T = typename C::value_type> // this template ensures we have a container of type T
    group(C gen, std::function<E(E, E)> compose_) {
        static_assert(std::is_same_v<E, T>, "Wrong type passed to group constructor.");
        this->compose = compose_;
        if (gen.empty()) return;
        // https://math.stackexchange.com/questions/1758649/an-algorithm-to-find-a-subgroup-generated-by-a-subset-of-a-finite-group
        std::queue<E> q;
        for (auto &x : gen) q.push(x);
        std::unordered_set<E> H;
        while (q.size()) {
            auto x = q.front();
            q.pop();
            if (H.count(x)) continue;
            H.insert(x);
            for (auto &s : gen) q.push(compose(x, s)), q.push(compose(s, x));
        }
        for (auto &label : H) (*this).insert(group_element<E>(label, &this->compose));
    }
};


namespace generate {
    std::unordered_set<ll> generators_Z() { return {1}; }
    std::function<ll(ll, ll)> composition_Z(int n) { return [n](ll a, ll b){ return (a + b) % n; }; }
    group<ll> Z(int n) { return {generators_Z(), composition_Z(n)}; }

    std::unordered_set<perm> generators_S(int n) {
        if (n == 1) {
            std::unordered_map<ll, ll> m;
            m[1] = 1;
            perm p(m);
            std::unordered_set<perm> s = {p};
            return s;
        }
        std::unordered_map<ll, ll> rotation, swap;
        F(i,n) rotation[i + 1] = (i + 1) % n + 1, swap[i + 1] = i + 1;
        swap[1] = 2, swap[2] = 1;
        std::unordered_set<perm> out{perm(rotation), perm(swap)};
        return out;
    }
    std::function<perm(perm, perm)> composition_S() { return [](perm a, perm b){
        std::unordered_map<ll, ll> temp;
        F(i,a.size()) temp[i + 1] = a[b[i+1]];
        return perm(temp);
    }; }
    group<perm> S(int n) { return {generators_S(n), composition_S()}; }
}


#endif //ALGEBRA_GROUP_H
