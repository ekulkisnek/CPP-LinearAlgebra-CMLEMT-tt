
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"
#include <cmath>

/**
 * @brief Template class for mathematical vectors
 * 
 * EDUCATIONAL NOTES:
 * ==================
 * Vectors are fundamental objects in linear algebra representing:
 * 1. Directions and magnitudes in space
 * 2. Solutions to linear systems
 * 3. Points in n-dimensional space
 * 
 * KEY CONCEPTS:
 * -------------
 * 1. Vector Operations:
 *    - Dot product (inner product)
 *    - Norm (length/magnitude)
 *    - Vector addition/subtraction
 * 
 * 2. Vector Properties:
 *    - Direction
 *    - Magnitude
 *    - Dimensionality
 * 
 * IMPLEMENTATION DETAILS:
 * ----------------------
 * - Inherits matrix functionality
 * - Specializes for 1×n or n×1 matrices
 * - Provides vector-specific operations
 * 
 * @tparam T The data type of vector elements
 */
template<typename T>
class Vector {
private:
    Matrix<T> data;  // Vector is implemented as a special case of matrix
    bool is_column;  // Tracks vector orientation

public:
    /**
     * @brief Construct a column vector
     * 
     * EDUCATIONAL NOTE:
     * Column vectors are standard in linear algebra:
     * 1. Consistent with matrix multiplication
     * 2. Matches mathematical notation
     * 3. Simplifies transformation operations
     */
    explicit Vector(size_t size) : data(size, 1), is_column(true) {}

    /**
     * @brief Convert between row and column vectors
     * 
     * EDUCATIONAL NOTE:
     * Transpose operation:
     * 1. Changes orientation (row ↔ column)
     * 2. Preserves vector elements
     * 3. Useful for certain computations
     */
    Vector<T> transpose() const {
        Vector<T> result(data.get_rows());
        for (size_t i = 0; i < data.get_rows(); ++i) {
            result.data.at(i, 0) = data.at(i, 0);
        }
        result.is_column = !is_column;
        return result;
    }

    /**
     * @brief Vector dot product
     * 
     * EDUCATIONAL NOTE:
     * The dot product (a·b):
     * 1. Results in a scalar
     * 2. Equals sum of element-wise products
     * 3. Geometric interpretation:
     *    - |a||b|cos(θ) where θ is angle between vectors
     *    - 0 for perpendicular vectors
     *    - |a||b| for parallel vectors
     * 
     * Applications:
     * - Work calculation in physics
     * - Projection operations
     * - Angle calculations
     */
    T dot(const Vector<T>& other) const {
        if (data.get_rows() != other.data.get_rows()) {
            throw std::invalid_argument("Vectors must have same dimension for dot product");
        }

        T result = T();
        for (size_t i = 0; i < data.get_rows(); ++i) {
            result += data.at(i, 0) * other.data.at(i, 0);
        }
        return result;
    }

    /**
     * @brief Vector norm (magnitude)
     * 
     * EDUCATIONAL NOTE:
     * The norm ||v||:
     * 1. Represents vector length
     * 2. Calculated as sqrt(v·v)
     * 3. Properties:
     *    - Always non-negative
     *    - Zero only for zero vector
     *    - Homogeneous: ||cv|| = |c|||v||
     * 
     * Applications:
     * - Distance calculations
     * - Vector normalization
     * - Error metrics
     */
    T norm() const {
        return std::sqrt(dot(*this));
    }

    // Element access with bounds checking
    T& at(size_t i) {
        return data.at(i, 0);
    }

    const T& at(size_t i) const {
        return data.at(i, 0);
    }

    /**
     * @brief Get vector dimension
     * 
     * EDUCATIONAL NOTE:
     * Vector dimension:
     * 1. Number of components
     * 2. Determines vector space
     * 3. Must match for operations
     */
    size_t size() const {
        return data.get_rows();
    }
};

#endif // VECTOR_HPP
