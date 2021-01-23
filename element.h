#ifndef ALGEBRA_ELEMENT_H
#define ALGEBRA_ELEMENT_H


#include <ostream>

//class Int{
//public:
//    explicit Int(int x, int n) { this->x = x; this->n = n; this->cmp = x; }
//    [[nodiscard]] Int dot(Int y) const { return Int((this->x + y.x) % this->n, this->n); }
//    friend std::ostream& operator <<(std::ostream& os, const Int& b) { return os << b.x; }
//    int x, n, cmp;
//    bool operator<(const Int& rhs) const { return cmp < rhs.cmp; }
//};

template<class E>
class element {
    virtual std::ostream& doprint(std::ostream&) const = 0;
public:
    int cmp{};
    friend std::ostream& operator << (std::ostream& os, const E& b) { return b.doprint(os); }
    [[nodiscard]] virtual E dot(E b) const = 0;
    bool operator<(const element<E>& rhs) const { return cmp < rhs.cmp; }
};

class Int : public element<Int> {
public:
    std::ostream& doprint(std::ostream& os) const override;
    int v, n;
    [[nodiscard]] Int dot(Int b) const override;
    explicit Int(int v, int n);
};


#endif //ALGEBRA_ELEMENT_H
