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
    cout << S(5) << endl;
    TR(F, all_homomorphisms(Z(4), S(5)))
        cout << F << endl;
    return 0;
}
