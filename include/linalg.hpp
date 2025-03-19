#ifndef LINALG_HPP
#define LINALG_HPP

#include "matrix.hpp"
#include "vector.hpp"
#include <cmath>

/**
 * @brief Linear algebra utilities
 * 
 * This namespace contains common linear algebra operations and transformations.
 */
namespace linalg {

/**
 * @brief Creates a 3D rotation matrix around the X axis
 * 
 * @param angle Rotation angle in radians
 * @return Matrix<double> 3x3 rotation matrix
 */
Matrix<double> rotation_x(double angle) {
    Matrix<double> rot(3, 3);
    rot.at(0, 0) = 1;
    rot.at(1, 1) = std::cos(angle);
    rot.at(1, 2) = -std::sin(angle);
    rot.at(2, 1) = std::sin(angle);
    rot.at(2, 2) = std::cos(angle);
    return rot;
}

/**
 * @brief Creates a 3D rotation matrix around the Y axis
 */
Matrix<double> rotation_y(double angle) {
    Matrix<double> rot(3, 3);
    rot.at(0, 0) = std::cos(angle);
    rot.at(0, 2) = std::sin(angle);
    rot.at(1, 1) = 1;
    rot.at(2, 0) = -std::sin(angle);
    rot.at(2, 2) = std::cos(angle);
    return rot;
}

/**
 * @brief Creates a 3D rotation matrix around the Z axis
 */
Matrix<double> rotation_z(double angle) {
    Matrix<double> rot(3, 3);
    rot.at(0, 0) = std::cos(angle);
    rot.at(0, 1) = -std::sin(angle);
    rot.at(1, 0) = std::sin(angle);
    rot.at(1, 1) = std::cos(angle);
    rot.at(2, 2) = 1;
    return rot;
}

/**
 * @brief Solves a system of linear equations using Gaussian elimination
 * 
 * @param A Coefficient matrix
 * @param b Constants vector
 * @return Vector<double> Solution vector
 */
template<typename T>
Vector<T> solve_linear_system(const Matrix<T>& A, const Vector<T>& b) {
    if (A.get_rows() != A.get_cols() || A.get_rows() != b.size()) {
        throw std::invalid_argument("Invalid dimensions for linear system");
    }

    // Augment matrix with vector b
    Matrix<T> augmented(A.get_rows(), A.get_cols() + 1);
    for (size_t i = 0; i < A.get_rows(); ++i) {
        for (size_t j = 0; j < A.get_cols(); ++j) {
            augmented.at(i, j) = A.at(i, j);
        }
        augmented.at(i, A.get_cols()) = b.at(i);
    }

    // Solve using Gaussian elimination
    Matrix<T> reduced = augmented.reduced_row_echelon_form();

    // Extract solution
    Vector<T> solution(b.size());
    for (size_t i = 0; i < b.size(); ++i) {
        solution.at(i) = reduced.at(i, A.get_cols());
    }

    return solution;
}

} // namespace linalg

#endif // LINALG_HPP
