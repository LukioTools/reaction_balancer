#include <glm/glm.hpp>
#include <iostream>
#include <ostream>

#include "./Libs/gaussian.hpp"
#include "./Libs/Frag.hpp"

int main(int argc, char const *argv[]) {

    Frag::fraction<int> f1(5,2);
    Frag::fraction<int> f2(2,5);

    std::cout << "f1 : f2: " << f1 << " : " << f2 << std::endl;

    std::cout << "f1+f2: " << f1+f2 << std::endl;
    
    std::cout << "f1-f2: " << f1-f2 << std::endl;
    std::cout << "f2-f1: " << f2-f1 << std::endl;

    std::cout << "f1*f2: " << f1*f2 << std::endl;
    
    std::cout << "f1/f2: " << f1/f2 << std::endl;
    std::cout << "f2/f1: " << f2/f1 << std::endl;

    std::cout << "-f1: " << -f1 << std::endl; 
    std::cout << "-f2: " << -f2 << std::endl; 

}