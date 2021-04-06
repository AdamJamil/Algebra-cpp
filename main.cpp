#include <iomanip>
#include "definitions.h"
#include "set.h"
#include "function.h"
#include "element.h"
#include "group.h"
using namespace generate;
using namespace std;

int main() {
    F(i,7) {
        auto start = (ld) (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
        auto S = generate::S(i + 1);
        D(S.size())
        cout.precision(5);
        cout << (i + 1) << ": " <<(((ld) (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()) - start) / 1000) << endl;
    }
    F(i,10) {
        auto start = (ld) (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
        auto Z = generate::Z(pow(10, i + 1));
        D(Z.size())
        cout.precision(5);
        cout << (i + 1) << ": " <<(((ld) (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()) - start) / 1000) << endl;
    }
    return 0;
}
