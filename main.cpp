#include <glm/detail/qualifier.hpp>
#include <glm/geometric.hpp>
#include <initializer_list>
#include <iostream>

#include <numeric>
#include <ostream>
#include <stdexcept>

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

#include "./Libs/gaussian.hpp"
#include "./Libs/Frag.hpp"

template<typename T>
void printVec(T v, int l){
    for (int i = 0; i<l;i++) {
        std::cout << v[i] << " : ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {


    std::span<Frag::fraction<int>> vf;
    Frag::fraction<int> f;
    auto xde = Math::multiply(vf,f);


    std::cout  << " eeeeeeeeeee"<< std::endl;
    Math::Matrix<Frag::fraction<int>> matrix(
        std::initializer_list<Frag::fraction<int>>{Frag::fraction(3,1), Frag::fraction(0,1), Frag::fraction(-1,1), Frag::fraction(0,1)},
        std::initializer_list<Frag::fraction<int>>{Frag::fraction(8,1), Frag::fraction(0,1), Frag::fraction(0,1), Frag::fraction(-2,1)},
        std::initializer_list<Frag::fraction<int>>{Frag::fraction(0,1), Frag::fraction(2,1), Frag::fraction(-2,1), Frag::fraction(-1,1)}
    );

    Math::Matrix<float> mat2(
        std::initializer_list<float>{3,0,-1, 0},
        std::initializer_list<float>{8,0,0, -2},
        std::initializer_list<float>{0,2,-2,-1}
    );

    gaussian::Input(mat2, mat2.width, mat2.height); 
    /*
    std::cout << " ---- " << std::endl;
    gaussian::Input(matrix, matrix.width, matrix.height);
    */




    return 0;
}