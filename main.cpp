#include "definitions.h"
#include "group.h"
#include "function.cpp"

int main() {
    std::unordered_map<ll, ll> m = {{1, 2}, {2, 1}, {3, 4}};
    auto f = bijection<ll, ll>(m);
    D(f)
    std::cerr << '\n';
    std::vector<std::pair<ll, ll>> x = {{4, 3}};
    auto g = surjection<ll, ll>(m);
    D(g)
    return 0;
}
