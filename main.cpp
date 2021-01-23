#include <iostream>
using namespace std;
#include <set>
#include "definitions.h"
#include "group.h"
#include "element.h"

int main() {
    auto g = group<Int>({Int(2,30)});
    cout << g << endl;
    return 0;
}
