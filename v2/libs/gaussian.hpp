#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <span>
#include <utility>
#include <vector>

#include "../libs/fraction-cpp/fraction.hpp"



namespace Vectors {
    template<typename T>
    void Addition(const std::span<T> a, const std::span<T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        for (unsigned long i = 0; i<a.size(); i++)
            a[i]+=b[i];
    }

    template<typename T>
    void Substraction(const std::span<T> a, const std::span<T> b){
        if (a.size() != b.size()) throw std::invalid_argument("Are not same size");
        for (unsigned long i = 0; i<a.size(); i++)
            a[i]-=b[i];
    }

    template<typename T>
    void MultiplyScalar(const std::span<T> a, T b){
        for (unsigned long i = 0; i<a.size(); i++)
            a[i]*=b;
    }

    template<typename T>
    void Division(const std::span<T> a, T b){
        for (unsigned long i = 0; i<a.size(); i++)
            a[i]/=b;
    }
}

template<class T, size_t F>
std::ostream& operator<<(std::ostream& os, const std::span<T, F>& mat){
    os << "[";
    for(size_t y = 0; y < mat.size(); ++y)
        os << mat[y] << (y+1 < mat.size() ? ", " : "");
    return os << "]";
}

namespace Matrix {

    template<typename T>
    class Matrix{
        std::unique_ptr<T[]> data;
        
        public:
        std::size_t width;
        std::size_t height;

        Matrix(size_t w, size_t h) : width(w), height(h){
            data = std::make_unique<T[]>(w*h);
        }
        
        
        template<class... va>
        requires(std::is_same_v<va, std::initializer_list<T>> && ...)
        Matrix(std::initializer_list<T> first, va... rest){
            height = sizeof...(va)+1;
            width = first.size();

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

        template<class... va>
        requires(std::is_same_v<va, std::vector<T>> && ...)
        Matrix(std::vector<T> first, va... rest){
            height = sizeof...(va)+1;
            width = first.size();

            data = std::make_unique<T[]>(width*height);
            size_t x = 0;
            for (const auto& e : first) {
                data[x++] = e;
            }
            ([&]
                {
                    for (const auto& e : rest) {
                        data[x++] = e;
                    }
                }(), ...);
        }


        std::span<T> operator[](std::size_t i) const{
            return std::span<T>{data.get()+(i*width), width};  
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat){
            os << "[";
            for(size_t y = 0; y < mat.height; ++y)
                os << mat[y] << (y+1 < mat.height ? "\n" : "");
            return os << "]";
        }
    };
}

namespace Gaussian {
    template<typename M>
    void dump_matrix(M& matrix)
    {
        for (int i = 0; i < matrix.height; i++)
        {
            for (int j = 0; j < matrix.width; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    template <typename T>
    void row_scale(std::span<T> row, T ratio){
        Vectors::MultiplyScalar(row, ratio);
    }

    template <typename T>
    void row_replace(std::span<T> base, std::span<T> op, T ratio){
        Vectors::MultiplyScalar(op, ratio);
        Vectors::Addition(base, op);
        }

    template <typename T>
    void row_exchange(std::span<T> a, std::span<T> b){
        std::swap(a,b);
    }

    template <typename T>
    int is_nonzero_column(Matrix::Matrix<T>& matrix, int column_id, int rows, int next_row_id){
        for (int row = next_row_id; row < rows; row++)
        {
            if (matrix[row][column_id] != 0)
                return row;
        }
        return -1;
    }

    template <typename T>
    void Input(Matrix::Matrix<T>& matrix, int m, int n)
    {
        std::cout << matrix << "\n" << std::endl;
        int next_row_id = 0;
        for (int col = 0; col < n; col++)
        {

            int nonzero_row_id = is_nonzero_column(matrix, col, m, next_row_id);
            if (nonzero_row_id >= 0)
            {
                if (nonzero_row_id != next_row_id)
                {
                    row_exchange(matrix[next_row_id], matrix[nonzero_row_id]);
                    nonzero_row_id = next_row_id;
                }
                next_row_id++;

                


                for (int row = next_row_id; row < m; row++)
                {
                    if (matrix[row][col] == 0)
                        continue;
                    auto ratio = -matrix[row][col] / matrix[nonzero_row_id][col];
                    std::cout << ratio << " : " << matrix[row][col] << "/"<< matrix[nonzero_row_id][col] << std::endl;
                    row_replace(matrix[row], matrix[nonzero_row_id], ratio);      
                }
            }
        }

        for (int pos = next_row_id - 1; pos >= 0; pos--)
        {
            if (matrix[pos][pos] != 1)
            {
                row_scale(matrix[pos], 1/matrix[pos][pos]);
            }
            for (int row = 0; row < m; row++)
            {
                if (matrix[row][pos] != 0 && row != pos)
                {
                    row_replace(matrix[row], matrix[pos], -matrix[row][pos]);
                }
            }
        }

        std::cout << matrix << std::endl;
    }
}