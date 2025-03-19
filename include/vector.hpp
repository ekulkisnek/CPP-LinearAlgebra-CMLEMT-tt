#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"
#include <cmath>

/**
 * @brief Template class for mathematical vectors
 * 
 * This class implements a mathematical vector as a special case of a matrix
 * with either one row or one column.
 * 
 * @tparam T The data type of vector elements
 */
template<typename T>
class Vector {
private:
    Matrix<T> data;
    bool is_column;

public:
    // Construct a column vector
    explicit Vector(size_t size) : data(size, 1), is_column(true) {}

    // Convert between row and column vectors
    Vector<T> transpose() const {
        Vector<T> result(data.get_rows());
        for (size_t i = 0; i < data.get_rows(); ++i) {
            result.data.at(i, 0) = data.at(i, 0);
        }
        result.is_column = !is_column;
        return result;
    }

    // Vector dot product
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

    // Vector norm (magnitude)
    T norm() const {
        return std::sqrt(dot(*this));
    }

    // Access elements
    T& at(size_t i) {
        return data.at(i, 0);
    }

    const T& at(size_t i) const {
        return data.at(i, 0);
    }

    // Get dimension
    size_t size() const {
        return data.get_rows();
    }
};

#endif // VECTOR_HPP
