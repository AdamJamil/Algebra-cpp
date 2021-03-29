#include "definitions.h"
#include "group.h"
using namespace std;

int main() {
    group<Int> Z4 = generate::Z(4);
    cout << Z4 << endl;
//    D(Z4)
//    generate::generators_Z(4);
//    cout << generate::Z(4) << endl;
    return 0;
}
