#include "element.h"
#include <vector>
using namespace std;

#ifndef ALGEBRA_GROUP_H
#define ALGEBRA_GROUP_H

class group {
public:
    vector<element> s;
    virtual element dot(element a, element b) = 0;
};


#endif //ALGEBRA_GROUP_H
