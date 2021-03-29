#include "definitions.h"
#include "group.h"
#include "function.h"

int main() {
    group<Int> Z4 = generate::Z(4);
    std::cout << Z4 << std::endl;
    std::unordered_map<ll, ll> m = {{1, 2}, {2, 1}, {3, 4}};
    function<ll, ll> f = m;
    D(f)
    D(f.domain)
    return 0;
}
