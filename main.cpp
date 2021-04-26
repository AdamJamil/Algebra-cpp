#include <iomanip>
#include "definitions.h"
#include "set.h"
#include "function.h"
#include "element.h"
#include "group.h"
#include "homomorphism.h"
using namespace generate;
using namespace std;

int main() {
    auto Z10 = Z(10), Z5 = Z(5), Z20 = Z(20);
    unordered_map<ll, ll> m1, m2, m3;
    F(i,10) m1[i] = i % 5;
    F(i,10) m2[i] = 2 * i;
    F(i,10) m3[i] = i;
    epimorphism<decltype(Z10), decltype(Z5)> f(m1, Z10, Z5);
    monomorphism<decltype(Z10), decltype(Z20)> g(m2, Z10, Z20);
    isomorphism<decltype(Z10), decltype(Z10)> h(m3, Z10, Z10);
    D(f.domain)
    D(f.image)
    D(f.range)
    D(g.domain)
    D(g.image)
    D(g.range)
    D(h.domain)
    D(h.image)
    D(h.range)
    isomorphism<decltype(Z10), decltype(Z10)> i(m2, Z10, Z20);
    return 0;
}
