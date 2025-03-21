
#ifndef LINALG_HPP
#define LINALG_HPP

#include "matrix.hpp"
#include "vector.hpp"
#include <cmath>

/**
 * @brief Linear algebra utilities namespace
 * 
 * KEY CONCEPTS IN LINEAR ALGEBRA:
 * 
 * 1. Linear Transformations:
 *    - Are functions that preserve vector addition and scalar multiplication
 *    - Can be represented by matrices
 *    - Examples: rotations, reflections, scaling
 * 
 * 2. Matrix Operations:
 *    - Matrix multiplication represents composition of transformations
 *    - Order matters! AB ≠ BA (generally)
 *    - Used in computer graphics, physics simulations, and ML
 * 
 * 3. Systems of Linear Equations:
 *    - Can be solved using Gaussian elimination
 *    - Have geometric interpretations (intersection of planes/lines)
 *    - Critical in optimization problems
 */
namespace linalg {

/**
 * @brief Creates a 3D rotation matrix around the X axis
 * 
 * ROTATION MATRIX THEORY:
 * - Rotates points in 3D space around the X axis
 * - Preserves distances and angles (isometric transformation)
 * - Formula derived from trigonometric relationships:
 *   [1    0        0    ]
 *   [0  cos(θ) -sin(θ)]
 *   [0  sin(θ)  cos(θ)]
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
 * 
 * GEOMETRIC INTERPRETATION:
 * - Rotates around Y axis (vertical axis in most 3D systems)
 * - Used in camera controls and object manipulation
 * - Matrix form:
 *   [ cos(θ)  0  sin(θ)]
 *   [   0     1    0   ]
 *   [-sin(θ)  0  cos(θ)]
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
 * 
 * APPLICATIONS:
 * - Common in 2D graphics (rotation in X-Y plane)
 * - Used in robotics for planar rotation
 * - Matrix form:
 *   [cos(θ) -sin(θ)  0]
 *   [sin(θ)  cos(θ)  0]
 *   [  0       0     1]
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
 * GAUSSIAN ELIMINATION:
 * 1. Forward Elimination:
 *    - Convert matrix to row echelon form
 *    - Create zeros below diagonal
 * 
 * 2. Back Substitution:
 *    - Solve for variables from bottom up
 *    - Results in unique solution if matrix is invertible
 * 
 * Time Complexity: O(n³) where n is matrix dimension
 * 
 * PRACTICAL APPLICATIONS:
 * - Circuit analysis
 * - Economic models
 * - Computer graphics (inverse kinematics)
 */
template<typename T>
Vector<T> solve_linear_system(const Matrix<T>& A, const Vector<T>& b) {
    if (A.get_rows() != A.get_cols() || A.get_rows() != b.size()) {
        throw std::invalid_argument("Invalid dimensions for linear system");
    }

    // Create augmented matrix [A|b]
    Matrix<T> augmented(A.get_rows(), A.get_cols() + 1);
    for (size_t i = 0; i < A.get_rows(); ++i) {
        for (size_t j = 0; j < A.get_cols(); ++j) {
            augmented.at(i, j) = A.at(i, j);
        }
        augmented.at(i, A.get_cols()) = b.at(i);
    }

    // Solve using Gaussian elimination
    Matrix<T> reduced = augmented.reduced_row_echelon_form();

    // Extract solution vector
    Vector<T> solution(b.size());
    for (size_t i = 0; i < b.size(); ++i) {
        solution.at(i) = reduced.at(i, A.get_cols());
    }

    return solution;
}

} // namespace linalg

#endif // LINALG_HPP
