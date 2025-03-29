#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstring>
#include <iostream>
#include <cstdint>

namespace pim {

// Matrix class to represent 2D matrices with parameterized sizes
class Matrix {
public:
    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows * cols, 0) {}

    // Accessors
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    
    // Element access
    int32_t& at(size_t i, size_t j) { return data_[i * cols_ + j]; }
    const int32_t& at(size_t i, size_t j) const { return data_[i * cols_ + j]; }

    // Matrix multiplication
    Matrix multiply(const Matrix& other) const {
        if (cols_ != other.rows()) {
            throw std::runtime_error("Invalid matrix dimensions for multiplication");
        }

        Matrix result(rows_, other.cols());
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < other.cols(); ++j) {
                int32_t sum = 0;
                for (size_t k = 0; k < cols_; ++k) {
                    sum += at(i, k) * other.at(k, j);
                }
                result.at(i, j) = sum;
            }
        }
        return result;
    }

private:
    size_t rows_;
    size_t cols_;
    std::vector<int32_t> data_;
};

} // namespace pim

#endif // MATRIX_H