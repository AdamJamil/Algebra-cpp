#include <iostream>
using namespace std;
#include <set>
#include "definitions.h"
#include "group.h"
#include "element.h"

int main() {
    // this permutation swaps the first two elements
    auto swap_adj = Perm(5, {2, 1, 3, 4, 5}, true);
    // this permutation shifts all elements up by one
    auto rotate = Perm(7, {2, 3, 4, 5, 1}, true);
    // create S_5
    auto g = group<Perm>({swap_adj, rotate});
    // print all elements of g
    cout << g << endl;
    cout << g.s.size() << " elements." << endl;
    return 0;
}
