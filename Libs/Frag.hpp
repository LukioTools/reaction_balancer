#pragma once

#include <cstddef>
#include <glm/detail/qualifier.hpp>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <numeric>
#include <ostream>
#include <span>
#include <stdexcept>
#include <string>
#include <glm/glm.hpp>
#include <type_traits>
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

    friend fraction<T> operator/(const T& num, const fraction<T>& m){
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

    /*
    template<typename T>
    class Vector{
        std::vector<T> vector;
        operator std::span<T>(){
            return vector;
        }
        size_t s = 0;

        public:
        Vector(){};
        Vector(size_t s){ vector = std::vector<T>(s, 0); } 
        Vector(std::vector<T> v) : vector(v){};
        Vector(std::vector<T>&& mv) : vector(std::move(mv)){};
        Vector(std::initializer_list<T> values) : s(values.size()), vector(values) {}
        Vector(std::span<T> sp) : s(sp.size()), vector(sp){}

        template<typename... Args>
        Vector(Args&&... args) : vector{std::forward<Args>(args)...}, s(sizeof...(args)) {}


        size_t size(){
            return s;
        }
        
        void push_back(T t){
            t.push_back(t);
            s += 1;
        }

        T& operator[](size_t idx){
            if (idx >= s) {
                throw std::out_of_range("Index out of range");
            }
            return vector[idx];
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
            os << "[";
            for (auto e : vec) {
                os << e << ", ";
            }
            os << "]";
            return os;
        }

    };
    */
    template<typename T>
    using Vector = std::vector<T>;

    

    //koska ei ole += operator, nii ei saa modifyaa niit muit hommeleit (argument a ja b)
    template<typename T>
    Vector<T> operator+(const std::span<const T> a, const std::span<const T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        
        Vector<T> out;
        for (unsigned long i = 0; i<a.size(); i++)
            out.push_back(a[i]+b[i]);

        return out;
    }   


    template<typename T>
    void addeq(const std::span<T> a, const std::span<T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        for (unsigned long i = 0; i<a.size(); i++)
            a[i] += b[i];
    }

    template<typename T>
    void operator+=(const std::span<T> a, const std::span<T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        
        for (unsigned long i = 0; i<a.size(); i++)
            a[i] += b[i];
    }   

    template<typename T>
    Vector<T> operator-(const std::span<const T>& a, const std::span<const T>& b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        Vector<T> out;
        for (unsigned long i = 0; i<a.size(); i++) {
            out.push_back(a[i]+b[i]);
        }
        return out;
    }

    template<typename T>
    void operator-=(const std::span<T> a, const std::span<const T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        
        for (unsigned long i = 0; i<a.size(); i++)
            a[i] -= b[i];
    }   

    template<typename T, typename F>
    Vector<T> operator*(const std::span<const T> a, const F& m){
        Vector<T> out;
        for(T& x : a) // if you want to add 10 to each element
            out.push_back(x * m);
        return out;
    }

    template<class T, class F>
    inline void meq(const std::span<T> a, const F& b){
        for (unsigned long i = 0; i<a.size(); i++)
            a[i] *= b;
    }
    


    template<typename T, typename F>
    std::vector<T> multiply(const std::span<T> a, const F& m){
        Vector<T> out;
        for(T& x : a) // if you want to add 10 to each element
            out.push_back(x * m);
        return out;
    }
    
    template<class T>
    void operator*=(const std::span<T> a, const std::span<const T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        
        for (T i; i<a.size(); i++)
            a[i] *= b[i];
    }   

    template<typename T, typename F>
    Vector<T> operator/(const std::span<const T> a, const F& m){
        Vector<T> out;
        for(T& x : a) // if you want to add 10 to each element
            out.push_back(x / m);
        return out;
    }

    template<class T>
    void operator/=(const std::span<T> a, const std::span<const T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        
        for (unsigned long i = 0; i<a.size(); i++)
            a[i] /= b[i];
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::span<T>& mat){
        os << "[";
        for(size_t y = 0; y < mat.size(); ++y)
            os << mat[y] << (y+1 < mat.size() ? ", " : "");
        return os << "]";
    }

    template<typename T>
    class Matrix{
        std::unique_ptr<T[]> data;

        public:
        std::size_t width;
        std::size_t height;
        
        Matrix(size_t w, size_t h) : width(w), height(h){
            data = std::make_unique<T[]>(w*h);
        }

        std::size_t size(){
            return width*height;
        }

        template<class... va>
        requires(std::is_same_v<va, std::initializer_list<T>> && ...)
        Matrix(std::initializer_list<T> first, va... rest){
            height = sizeof...(va)+1;
            width = first.size();

            std::cout << Frag::fraction(width, height) << std::endl;
            
            data = std::make_unique<T[]>(width*height);
            size_t x = 0;
            for (const auto& e : first)
                data[x++] = e;
            ([&]
            {
                for (const auto& e : rest)
                    data[x++] = e;
            }(), ...);
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat){
            os << "[";
            for(size_t y = 0; y < mat.height; ++y)
                os << mat[y] << (y+1 < mat.height ? "\n" : "");
            return os << "]";
        }

        std::span<T> operator[](std::size_t i) const{
            return std::span<T>{data.get()+(i*width), width};  
        }
    };

    inline static int lcmVector(const std::vector<int>& numbers) {
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

