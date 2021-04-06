#ifndef ALGEBRA_ELEMENT_H
#define ALGEBRA_ELEMENT_H


template<typename T>
class group_element {
public:
    T label;
    std::function<T(T, T)> *compose;

    group_element<T>(T label_, std::function<T(T, T)> *compose_) : label(label_), compose(compose_) {}

    group_element<T> operator*(const group_element<T> &o) const { return group_element<T>((*compose)(this->label, o.label), compose); }
    bool operator<(const group_element<T> &o) const { return label < o.label; }
    bool operator==(const group_element<T> &o) const { return label == o.label; }
    bool operator!=(const group_element<T> &o) const { return label != o.label; }
    friend std::ostream& operator <<(std::ostream& os, const group_element<T>& b) { return os << b.label; }
};

template<> struct std::hash<perm> {
    std::size_t operator()(const ::perm& t) const {
        size_t code = 0;
        F(i,t.size()) code += t.injection<ll,ll>::at(i + 1) * PRIMES[i];
        return code;
    }
};

template<typename E> struct std::hash<group_element<E>> {
    std::size_t operator()(const ::group_element<E> &t) const { return hash<E>()(t.label); }
};


//class Perm {
//public:
//    // p is a bijection from [n] to [n]
//    int n;
//    std::vector<int> p;
//    // cycle_lengths is lengths of all nonzero cycles; used in sorting sensibly
//    // first element is actually number of cycles; rest of vector is as expected
//    std::vector<int> cycle_lengths;
//    // cycle notation for S_n
//    std::string name;
//    Perm(std::vector<int> p);
//
//    [[nodiscard]] Perm dot(Perm const &b) const;
//
//    bool operator==(const Perm& rhs) const { return p == rhs.p; }
//    bool operator!=(const Perm& rhs) const { return p != rhs.p; }
//    bool operator<(const Perm& rhs) const;
//    friend std::ostream& operator <<(std::ostream& os, const Perm& b);
//};

#endif //ALGEBRA_ELEMENT_H
