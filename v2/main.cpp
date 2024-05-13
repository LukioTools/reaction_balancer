#include "./libs/fraction-cpp/fraction.hpp"
#include "./libs/gaussian.hpp"

#include <span>
#include <vector>

template<typename T>
void printVector(std::vector<T> v){
    std::cout << "(";
    for (auto i : v) {
        std::cout << i << ",";
    }
    std::cout << ")" << std::endl;
}

int main(){
    std::vector<float> i = {1,2,3};
    std::vector<float> j = {1,2,3};

    Matrix::Matrix<float> matrix(i,j);

    Vectors::Addition(std::span<float>(j), std::span<float>(i));

    Gaussian::Input(matrix, matrix.width, matrix.height);

}