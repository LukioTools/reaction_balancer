#include <glm/detail/qualifier.hpp>
#include <glm/geometric.hpp>
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

    glm::mat<3, 4, Frag::fraction<int>> matrix = {{Frag::fraction(3,1), Frag::fraction(0,1), Frag::fraction(-1,1), Frag::fraction(0,1)},
                                       {Frag::fraction(8,1), Frag::fraction(0,1), Frag::fraction(0,1), Frag::fraction(-2,1)},
                                       {Frag::fraction(0,1), Frag::fraction(2,1), Frag::fraction(-2,1), Frag::fraction(-1,1)},
                                       };

    glm::mat<3,4, float> matrix2 = {{3,0,-1,0},
                                    {8,0,0,-2},
                                    {0,2,-2,-1}};


    gaussian::Input<glm::mat<3,4, Frag::fraction<int>>>(matrix, 3, 4);
    std::cout << " ---- " << std::endl;
    gaussian::Input<glm::mat<3,4, float>>(matrix2, 3, 4);

    return 0;
}