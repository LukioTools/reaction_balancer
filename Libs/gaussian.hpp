#pragma once

#include "Frag.hpp"
#include <glm/detail/qualifier.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <cppostream/vector.hpp>
#include <ostream>

namespace gaussian {
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

    template<typename V, typename T>
    void row_scale(V row, T ratio)
    {
        Math::meq(row, ratio);
    }

    template<typename V, typename T>
    void row_replace(V base, const V op, T ratio)
    {
        auto v = Math::multiply(op, ratio);
        Math::addeq(base, std::span(v));
    }

    template<typename V>
    void row_exchange(V a, V b)
    {
        V temp = a;
        a = b;
        b = temp;
    }

    template<typename M>
    int is_nonzero_column( M& matrix, int column_id, int rows, int next_row_id)
    {
        for (int row = next_row_id; row < rows; row++)
        {
            if (matrix[row][column_id] != 0)
                return row;
        }
        return -1;
    }

    template <typename M>
    void Input(Math::Matrix<M>& matrix, int m, int n)
    {
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
                    row_replace(matrix[row], matrix[nonzero_row_id], -matrix[row][col] / matrix[nonzero_row_id][col]);
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

        dump_matrix(matrix);
    }
}