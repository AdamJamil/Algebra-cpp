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
    auto S6 = S(6);
    auto Z4 = Z(4);
    auto start = (ld) (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    cout << all_homomorphisms(Z4, S6) << endl;
    cout << ((ld) (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()) - start) / 1000 << endl;
    return 0;
}
