#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <memory>

/**
 * @brief Template class for matrix operations
 * 
 * This class implements a 2D matrix with dynamic memory allocation.
 * It demonstrates RAII principles and operator overloading in C++.
 * 
 * @tparam T The data type of matrix elements (typically float or double)
 */
template<typename T>
class Matrix {
private:
    std::unique_ptr<T[]> data;  // Raw array for optimal performance
    size_t rows;
    size_t cols;

public:
    // Constructor with size initialization
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        if (r == 0 || c == 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
        data = std::make_unique<T[]>(r * c);
        // Initialize to zero
        for (size_t i = 0; i < r * c; ++i) {
            data[i] = T();
        }
    }

    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = std::make_unique<T[]>(rows * cols);
        std::copy(other.data.get(), other.data.get() + (rows * cols), data.get());
    }

    // Move constructor
    Matrix(Matrix&& other) noexcept 
        : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
        other.rows = 0;
        other.cols = 0;
    }

    // Element access with bounds checking
    T& at(size_t i, size_t j) {
        if (i >= rows || j >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[i * cols + j];
    }

    const T& at(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[i * cols + j];
    }

    // Matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
        }

        Matrix<T> result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T sum = T();
                for (size_t k = 0; k < cols; ++k) {
                    sum += at(i, k) * other.at(k, j);
                }
                result.at(i, j) = sum;
            }
        }
        return result;
    }

    // Gaussian elimination
    Matrix<T> reduced_row_echelon_form() const {
        Matrix<T> temp(*this);
        size_t lead = 0;

        for (size_t r = 0; r < rows; ++r) {
            if (lead >= cols) return temp;

            size_t i = r;
            while (temp.at(i, lead) == 0) {
                ++i;
                if (i == rows) {
                    i = r;
                    ++lead;
                    if (lead == cols) return temp;
                }
            }

            // Swap rows i and r
            if (i != r) {
                for (size_t j = 0; j < cols; ++j) {
                    std::swap(temp.at(i, j), temp.at(r, j));
                }
            }

            // Normalize row r
            T div = temp.at(r, lead);
            for (size_t j = 0; j < cols; ++j) {
                temp.at(r, j) /= div;
            }

            // Eliminate column
            for (size_t i = 0; i < rows; ++i) {
                if (i != r) {
                    T mult = temp.at(i, lead);
                    for (size_t j = 0; j < cols; ++j) {
                        temp.at(i, j) -= temp.at(r, j) * mult;
                    }
                }
            }
            ++lead;
        }

        return temp;
    }

    // Getters for dimensions
    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }

    // Stream output operator
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.cols; ++j) {
                os << std::setw(8) << std::fixed << std::setprecision(4) << m.at(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }
};

#endif // MATRIX_HPP
