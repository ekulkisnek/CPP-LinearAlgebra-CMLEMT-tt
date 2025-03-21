
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
 * EDUCATIONAL NOTES:
 * ==================
 * Matrices are fundamental structures in linear algebra representing rectangular arrays of numbers.
 * This implementation uses modern C++ features to ensure:
 * 1. Memory safety through RAII (Resource Acquisition Is Initialization)
 * 2. Exception safety with strong exception guarantee
 * 3. Move semantics for efficient resource transfer
 * 
 * KEY CONCEPTS:
 * -------------
 * 1. Templates: Allow type-generic programming
 * 2. Smart Pointers: Automatic memory management
 * 3. Operator Overloading: Natural mathematical syntax
 * 
 * MATHEMATICAL PROPERTIES:
 * ----------------------
 * - A matrix of size m×n has m rows and n columns
 * - Matrix multiplication (A×B) requires A's columns = B's rows
 * - The identity matrix has 1's on diagonal, 0's elsewhere
 * 
 * IMPLEMENTATION DETAILS:
 * ---------------------
 * - Uses 1D array internally for better cache performance
 * - Row-major storage: element(i,j) = data[i * cols + j]
 * - Bounds checking on all element access
 * 
 * @tparam T The data type of matrix elements (typically float or double)
 */
template<typename T>
class Matrix {
private:
    // Stores matrix elements in contiguous memory for cache efficiency
    std::unique_ptr<T[]> data;  
    size_t rows;
    size_t cols;

public:
    /**
     * @brief Constructor with size initialization
     * 
     * EDUCATIONAL NOTE:
     * Matrix initialization follows these steps:
     * 1. Validate dimensions
     * 2. Allocate memory
     * 3. Initialize elements to zero
     * 
     * This demonstrates RAII principle: resource management tied to object lifetime
     */
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        if (r == 0 || c == 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
        data = std::make_unique<T[]>(r * c);
        // Initialize to zero (numerical stability)
        for (size_t i = 0; i < r * c; ++i) {
            data[i] = T();
        }
    }

    /**
     * @brief Copy constructor
     * 
     * EDUCATIONAL NOTE:
     * Deep copy is essential for:
     * 1. Value semantics
     * 2. Independent object lifetime
     * 3. Thread safety
     */
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = std::make_unique<T[]>(rows * cols);
        std::copy(other.data.get(), other.data.get() + (rows * cols), data.get());
    }

    /**
     * @brief Move constructor
     * 
     * EDUCATIONAL NOTE:
     * Move semantics allow efficient transfer of resources:
     * 1. Avoids unnecessary copying
     * 2. Particularly useful for large matrices
     * 3. Leaves source object in valid but unspecified state
     */
    Matrix(Matrix&& other) noexcept 
        : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
        other.rows = 0;
        other.cols = 0;
    }

    /**
     * @brief Element access with bounds checking
     * 
     * EDUCATIONAL NOTE:
     * Bounds checking is crucial for:
     * 1. Memory safety
     * 2. Debugging
     * 3. Exception safety
     * 
     * Formula: index = i * cols + j (row-major order)
     */
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

    /**
     * @brief Matrix multiplication
     * 
     * EDUCATIONAL NOTE:
     * Matrix multiplication (A×B):
     * 1. Requires A.cols = B.rows
     * 2. Result dimensions: A.rows × B.cols
     * 3. Each element: sum of row×column products
     * 
     * Time complexity: O(n³) for n×n matrices
     * Space complexity: O(n²) for result storage
     */
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

    /**
     * @brief Gaussian elimination implementation
     * 
     * EDUCATIONAL NOTE:
     * Gaussian elimination:
     * 1. Converts matrix to row echelon form
     * 2. Used for solving linear systems
     * 3. Time complexity: O(n³)
     * 
     * Process:
     * 1. Find pivot in current column
     * 2. Swap rows if necessary
     * 3. Eliminate entries below pivot
     */
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

            // Row operations
            if (i != r) {
                for (size_t j = 0; j < cols; ++j) {
                    std::swap(temp.at(i, j), temp.at(r, j));
                }
            }

            // Normalize row
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

    // Dimension accessors
    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }

    /**
     * @brief Stream output operator
     * 
     * EDUCATIONAL NOTE:
     * Operator overloading enables:
     * 1. Natural syntax for matrix operations
     * 2. Integration with C++ streams
     * 3. Formatted output for debugging
     */
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
