#pragma once

#include <cstddef>
#include <glm/detail/qualifier.hpp>
#include <iostream>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <glm/glm.hpp>
#include <utility>
#include <vector>

namespace Frag {

template<typename T>
class fraction
{
    private:
        /* data */
    public:

    fraction(T f = 0) : Frag(f), Deno(1) {}
    fraction(T f, T d) : Frag(f), Deno(d) {}

    bool operator==(const fraction<T>& eq) const{
        fraction<T> tis = *this;
        fraction<T> other = eq;
        matchDeno(tis, other);
        return (tis.Frag == other.Frag);
    }

    bool operator !=(const fraction<T> eq) const{
        return !(*this == eq);
    }

    fraction<T> operator+(const fraction<T>& a) const{
        fraction<T> temp = *this;
        fraction<T> t2 = a;
        matchDeno(temp, t2);
        return fraction<T>(temp.Frag+t2.Frag, temp.Deno).simplify();
    }

    fraction<T> operator-(const fraction<T>& a) const{
        fraction<T> temp = *this;
        fraction<T> t2 = a;
        matchDeno(temp, t2);
        return fraction<T>(temp.Frag-t2.Frag, temp.Deno).simplify();
    }

    friend fraction<T> operator/(const int& num, const fraction<T>& m){
        fraction<T> t = m;
        t.reciprocal();
        return (fraction<T>(num)*t).simplify();
    }

    fraction<T> operator-() const{
        return fraction<T>(-(this->Frag), (this->Deno)).simplify();
    }

    fraction<T> operator*(const fraction<T>& m) const{
        return fraction<T>(Frag*m.Frag, Deno*m.Deno).simplify();
    }

    fraction<T> operator/(const fraction<T>& m) const{
        fraction<T> f = m;
        f.reciprocal();
        return (*this*f).simplify();
    }

    void operator+=(const fraction<T>& a){
        *this = *this+a;
    }

    void operator-=(const fraction<T>& a){
        *this = *this-a;
    }

    void operator*=(const fraction<T>& a){
        *this = *this*a;
    }

    void operator/=(const fraction<T>& a){
        *this = *this/a;
    }

    fraction<T> expand(T& v){
        return fraction<T>(Frag*v, Deno*v);
    }

    void reciprocal(){
        std::swap(Frag, Deno);
    }

    fraction<T> simplify(){
        T gcd = std::gcd(Frag,Deno);
        fraction<T> temp(Frag/gcd, Deno/gcd);
        // (temp.Frag > 0 && temp.Deno > 0) ? (Frag/gcd, Deno/gcd) : -(Frag/gcd, Deno/gcd)
        if (temp.Frag < 0 && temp.Deno < 0) {
            std::cout << "before: " << temp << std::endl;
            temp = fraction<T>(-temp.Frag, -temp.Deno);
            std::cout << "after: "<< temp << std::endl;
        }
        return temp;
    }

    void matchDeno(fraction& f1, fraction& f2) const{
        fraction<T> temp =f1;
        fraction<T> temp2 = f2;
        temp = f1.expand(temp2.Deno);
        temp2 = f2.expand(f1.Deno);
        f1 = temp;
        f2 = temp2;
    }

    T Frag = 0; // osoittaja
    T Deno = 1; // nimittäjä

    friend std::ostream& operator<<(std::ostream& os, const fraction<T>& frac) {
        os << frac.Frag << '/' << frac.Deno;
        return os;
    }
};
} 

// Overload division operator for glm::vec<>
template<typename T, glm::length_t L>
glm::vec<L, T> operator/(const glm::vec<L, T>& vec, const int& scalar) {
    glm::vec<L, T> result; // Initialize with zero
    for (glm::length_t i = 0; i < L; ++i) {
        result[i] = vec[i] / scalar;
    }
    return result;
}

namespace Math {

    template<typename T>
    class Vector{
        std::vector<T> vector;
        size_t s = 0;

        public:
        Vector(){};
        Vector(size_t s){ vector = std::vector<T>(s, 0); } 
        Vector(std::vector<T> v) : vector(v){};
        Vector(std::initializer_list<T> values) : s(values.size()), vector(values) {}

        template<typename... Args>
        Vector(Args&&... args) : vector{std::forward<Args>(args)...}, s(sizeof...(args)) {}

        size_t size(){
            return s;
        }
        
        void push_back(T t){
            t.push_back(t);
            s += 1;
        }

        T operator[](size_t idx){
            if (idx >= s) {
                throw std::out_of_range("Index out of range");
            }
            return vector[idx];
        }

        Vector<T> operator+(Vector<T> ad){
            if (s != ad.size()) throw std::invalid_argument("Are not same size");
            for(int& x : vector) // if you want to add 10 to each element
                x += 10;
        }

        Vector<T> operator-(Vector<T> ad){
            if (s != ad.size()) throw std::invalid_argument("Are not same size");
            for (int i; i<s; i++) {
                
            }
        }

        Vector<T> operator*(T mul){
            for(int& x : vector) // if you want to add 10 to each element
                x *= mul;
        }
        
    };

    int lcmVector(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        // If the vector is empty, return 0 or throw an exception based on requirement
        // Here, returning 0 assuming LCM of empty set is 0
        return 0;
    }

    int result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        // Calculate LCM of result and numbers[i] using std::lcm
        result = std::lcm(result, numbers[i]);
    }

    return result;
}
}

