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
    auto Z10 = Z(10), Z5 = Z(5);
    unordered_map<ll, ll> f;
    F(i,10) f[i] = i % 1;
    homomorphism<decltype(Z10), decltype(Z5)> phi(f, Z10, Z5);
    D(phi.domain)
    D(phi.image)
    D(phi.range)
    return 0;
}
